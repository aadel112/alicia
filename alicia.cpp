#include "alicia.hpp"

using namespace std;

Alicia::Alicia() {
    int rc = 0;
    char *zErrMsg = 0;
    ss << " CREATE TABLE symbol_table( "
        << "       int key, "
        << "       text var, "
        << "       text type,"
        << "       int digit_value,"
        << "       real decimal_value,"
        << "       text text_value "
        << ");";
    string create_sql = ss.str();
    ss  << "CREATE unique index idx01 ON "
        << "symbol_table(key)";
    string idx_sql = ss.str();
    string pthreads = "PRAGMA threads = 50";
    string pdirty = "PRAGMA read_uncomitted = true";
    string pvac = "PRAGMA auto_vaccum = full";

    string stat_sql = "ANALYZE";

    rc = sqlite3_open(NULL, &conn);
    rc = rc and sql_exec( create_sql, __LINE__ ); 
    rc = rc and sql_exec( idx_sql, __LINE__ );
    rc = rc and sql_exec( pthreads, __LINE__ ); 
    rc = rc and sql_exec( pdirty, __LINE__ );
    rc = rc and sql_exec( pvac, __LINE__ );
    rc = rc and sql_exec( stat_sql, __LINE__ );

}

int Alicia::sql_exec(string sql, int line) {
    int rc = 0;
    char *zErrMsg = 0;
    
    rc = sqlite3_exec(conn, sql.c_str(), NULL, 0, &zErrMsg);
    if( rc != SQLITE_OK )
        printf("SQLITE_ERROR on line %d: %s\n", line, zErrMsg);
    sqlite3_free(zErrMsg);

    return rc;
}
