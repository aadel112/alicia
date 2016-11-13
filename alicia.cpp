#include "alicia.hpp"

using namespace std;

Alicia::Alicia() {
    int rc = 0;
    char *zErrMsg = 0;
    ss << " CREATE TABLE symbol_table( "
        << "       key int, "
        << "       var text, "
        << "       type text,"
        << "       digit_value int,"
        << "       decimal_value real,"
        << "       text_value text"
        << ");";
    string create_sql = ss.str();
    ss  << "CREATE unique index idx01 ON "
        << "symbol_table(key)";
    string idx_sql = ss.str();
    string pthreads = "PRAGMA threads = 50";
    string pdirty = "PRAGMA read_uncomitted = true";
    string pvac = "PRAGMA auto_vaccum = full";

    string stat_sql = "ANALYZE";

    rc = sqlite3_open(":memory:", &conn);
    
    rc = !rc and sql_exec( create_sql, __LINE__ ); 
    rc = !rc and sql_exec( idx_sql, __LINE__ );
    rc = !rc and sql_exec( pthreads, __LINE__ ); 
    rc = !rc and sql_exec( pdirty, __LINE__ );
    rc = !rc and sql_exec( pvac, __LINE__ );
    rc = !rc and sql_exec( stat_sql, __LINE__ );

    rc = !rc and prepare_store();
}

int Alicia::prepare_store() {
    int rc = 0;

    ss << "DELETE FROM symbol_table WHERE key = :key";
    string del_sql = ss.str();
    ss << "INSERT INTO symbol_table VALUES"
        << "(:key, :var, :type, :digit_value"
        << ", :decimal_value, :text_value)";
    string ins_sql = ss.str();
    ss << "UPDATE symbol_table SET var = :var,"
        << "type = :type, digit_value = :digit_value,"
        << "decimal_value = :decimal_value,"
        << "text_value = :text_value "
        << "WHERE key = :key";
    string up_sql = ss.str();
    ss << "SELECT * FROM symbol_table WHERE key = :key";
    string fetch_sql = ss.str();
    ss << "SELECT COUNT(*) FROM symbol_table "
        << "WHERE key = :key";
    string key_sql = ss.str();

    rc = sqlite3_prepare_v2(
        conn, del_sql.c_str(), 
        MAX_PREPARE_BYTES, &del_h, NULL
    );

    rc = !rc and sqlite3_prepare_v2(
        conn, ins_sql.c_str(), 
        MAX_PREPARE_BYTES, &ins_h, NULL
    );

    rc = !rc and sqlite3_prepare_v2(
        conn, up_sql.c_str(), 
        MAX_PREPARE_BYTES, &up_h, NULL
    );

    rc = !rc and sqlite3_prepare_v2(
        conn, fetch_sql.c_str(), 
        MAX_PREPARE_BYTES, &fetch_h, NULL
    );

    rc = !rc and sqlite3_prepare_v2(
        conn, key_sql.c_str(), 
        MAX_PREPARE_BYTES, &key_h, NULL
    );
         

    return rc;
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

char* Alicia::get( const char* var ) {} //STUB
void Alicia::set( const char* var, const char* val ) {} //STuB
void Alicia::del( const char* var ) {} //STUB
char* Alicia::exec( const char* sql ) {} //STUB
