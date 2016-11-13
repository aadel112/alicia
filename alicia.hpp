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
#include <sqlite3.h>

#define MAX_PREPARE_BYTES -1 //10240
#define INT "int"
#define REAL "real"
#define TEXT "text"
#define JSON "json" //TODO

using namespace std;

class Alicia {
    private:
        sqlite3 *conn;
        stringstream ss;
        sqlite3_stmt* del_h;
        sqlite3_stmt* ins_h;
        sqlite3_stmt* up_h;
        sqlite3_stmt* fetch_h;
        sqlite3_stmt* key_h;

        int sql_exec(string sql, int line);
        int prepare_store();
 
    public:
        Alicia();
        ~Alicia();
        char* get( const char* var );
        void del( const char* var );
        void set( const char* var, const char* val );
        char* exec( const char* sql );
};
