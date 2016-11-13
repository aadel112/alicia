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
        template<typename T>  string get( T var );
        template<typename T>  void del( T var );
        template<typename T, typename K>  void set( T var, K val );
        string exec( string sql );
};
