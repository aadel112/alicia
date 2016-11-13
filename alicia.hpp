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

#define INT "int"
#define REAL "real"
#define TEXT "text"
#define JSON "json" //TODO

using namespace std;

class Alicia {
    private:
        sqlite3 *conn;
        stringstream ss;
    public:
        Alicia();
        int sql_exec(string sql, int line);
        char* get( const char* var );
        void del( const char* var );
        void set( const char* var, const char* val );
        char* exec( const char* sql );
};
