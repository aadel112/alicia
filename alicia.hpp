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

#define MAX_PREPARE_BYTES -1 //10240
#define INT "int"
#define REAL "real"
#define TEXT "text"
#define JSON "json" //TODO

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

        int sql_exec(const char* sql, int line);
        int prepare_store();
        bool is_simple_exec( const char* sql );
        bool key_exists( long long key );
        long long get_key(const char* var);
        void sql_fetch( const char* sql, int line );
        void sql_exec_stmt( sqlite3_stmt* stmt, int line );
        char* fetch_one_stmt( sqlite3_stmt* stmt, int line );
    
    public:
        char* last_result_set[1000][3];
        
        Alicia();
        ~Alicia();
        char* get( const char* var );
        void del( const char* var );
        void set( const char* var, const char* val );
        void exec( const char* sql );
};
