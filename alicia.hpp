#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <regex>
#include <sqlite3.h>

#define DB_FILE ":memory:"
// #define DB_FILE "/tmp/tmp.db"
#define MAX_PREPARE_BYTES -1 //10240
#define INT "int"
#define REAL "real"
#define TEXT "text"
#define JSON "json" //TODO

#define INSERT 1
#define DELETE 2
#define UPDATE 3
#define FETCH 4
#define KEY 5

#define STMT (stmt_type == KEY ? key_h \
            : (stmt_type == FETCH ? fetch_h \
            : (stmt_type == UPDATE ? up_h \
            : (stmt_type == DELETE ? del_h \
            : (ins_h))))\
        )

using namespace std;
using namespace std::regex_constants;

class Alicia {
    private:
        sqlite3 *conn;
        stringstream ss;
        sqlite3_stmt* del_h;
        sqlite3_stmt* ins_h;
        sqlite3_stmt* up_h;
        sqlite3_stmt* fetch_h;
        sqlite3_stmt* key_h;

        const char* del_sql = "DELETE FROM symbol_table WHERE key = ?";
        const char* ins_sql ="INSERT INTO symbol_table VALUES(?,?,?)";
        const char* up_sql = "UPDATE symbol_table SET var = ?,value = ? WHERE key = ?";
        const char* fetch_sql = "SELECT value FROM symbol_table WHERE key = ?";
        const char* key_sql = "SELECT COUNT(*) FROM symbol_table WHERE key = ?";

        int sql_exec(const char* sql, int line);
        bool is_simple_exec( const char* sql );
        bool key_exists( int key );
        int prepare( int stmt_type, const char *sql );
        int get_key(const char* var);
        void sql_fetch( const char* sql, int line );
        void sql_exec_stmt( int stmt_type, int line );
        char* fetch_one_stmt( int stmt_type, int line );
    
    public:
        char* last_result_set[1000][3];
        
        Alicia();
        ~Alicia();
        char* get( const char* var );
        void del( const char* var );
        void set( const char* var, const char* val );
        void exec( const char* sql );
};
