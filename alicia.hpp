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
#include <tuple>
#include <sqlite3.h>

#define die() exit(1)

#define DB_FILE ":memory:"
// #define DB_FILE "/tmp/tmp.db"
#define ARRAY_STEP 10240
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
#define TRUNCATE 6
#define DROP 7

#define DEFAULT_OUTPUT_FILE "stdout"
#define DEFAULT_INPUT_FILE "stdin"
#define DEFAULT_INPUT_TABLE "input_table"
#define DEFAULT_DELIMITER ","
#define DEFAULT_ESCAPE "\\"
#define DEFAULT_RECORD_DELIMITER "\r\n"
#define DEFAULT_FILE_HEADER "0"

#define STMT (stmt_type == KEY ? key_h \
            : (stmt_type == FETCH ? fetch_h \
            : (stmt_type == UPDATE ? up_h \
            : (stmt_type == DELETE ? del_h \
            : (stmt_type == TRUNCATE ? trnc_h) \
            : (stmt_type == DROP ? drop_h) \
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
        sqlite3_stmt* trnc_h;
        sqlite3_stmt* drop_h;


        map<int, sqlite3_stmt*> stmt_map;

        const char* del_sql = "DELETE FROM symbol_table WHERE key = ?";
        const char* ins_sql ="INSERT INTO symbol_table VALUES(?,?,?)";
        const char* up_sql = "UPDATE symbol_table SET var = ?,value = ? WHERE key = ?";
        const char* fetch_sql = "SELECT value FROM symbol_table WHERE key = ?";
        const char* key_sql = "SELECT COUNT(*) FROM symbol_table WHERE key = ?";
        const char* truncate_sql = "TRUNCATE ?";
        const char* drop_sql = "DROP TABLE IF EXISTS ?";

        int sql_exec(const char* sql, int line);
        int sql_exec(string sql, int line);
        
        bool is_simple_exec( const char* sql );
        bool is_simple_exec( string sql );

        bool key_exists( int key );
        
        int prepare( int stmt_type, const char *sql );
        int prepare( int stmt_type, string sql );

        int get_key(const char* var);
        int get_key(string var);
        
        vector<vector<string>> sql_fetch( const char* sql, int line );
        vector<vector<string>> sql_fetch( string sql, int line );


        vector<vector<string>> sql_exec_stmt( int stmt_type, int line );
        string fetch_one_stmt( int stmt_type, int line );
        bool compiled_user_stmt(int stmt_key);

        string get_file_contents(const char* ifile);
        string get_file_contents(string s);

    public:
        Alicia();
        ~Alicia();

        string UNDEFINED = "undefined";

        string parameterize_exec(const char* sql);
        string parameterize_exec(string sql);

        vector<tuple<string,string>> get_exec_parameters( const char* sql );
        vector<tuple<string,string>> get_exec_parameters( string sql );
        
        int write_out();
        int read_into();

        string get( const char* var );
        string get( string var );
         
        void del( const char* var );
        void del( string var );

        void truncate( const char* var );
        void truncate( string var );

        void drop( const char* var );
        void drop( string var );

        void set( const char* var, const char* val );
        void set( const char* var, string val );
        void set( string var, const char* val );
        void set( string var, string val );

        vector<vector<string>> exec( const char* sql );
        vector<vector<string>> exec( string sql );
};
