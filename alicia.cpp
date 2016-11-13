#include "alicia.hpp"

using namespace std;

Alicia::Alicia() {
    int rc = 0;
    char *zErrMsg = 0;

    ss << " CREATE TABLE symbol_table( "
        << "       key int, "
        << "       var text, "
        << "  value text"
        << ");";
    string create_sql = ss.str();
    ss.str("");
    ss  << "CREATE unique index idx01 ON "
        << "symbol_table(key)";
    string idx_sql = ss.str();
    ss.str("");
    string pthreads = "PRAGMA threads = 50";
    string pdirty = "PRAGMA read_uncomitted = true";
    string pvac = "PRAGMA auto_vaccum = full";

    string stat_sql = "ANALYZE";

    rc = sqlite3_open(":memory:", &conn);
    
    rc = !rc and sql_exec( create_sql.c_str(), __LINE__ ); 
    rc = !rc and sql_exec( idx_sql.c_str(), __LINE__ );
    rc = !rc and sql_exec( pthreads.c_str(), __LINE__ ); 
    rc = !rc and sql_exec( pdirty.c_str(), __LINE__ );
    rc = !rc and sql_exec( pvac.c_str(), __LINE__ );
    rc = !rc and sql_exec( stat_sql.c_str(), __LINE__ );

    rc = !rc and prepare_store();
}

Alicia::~Alicia() {
    
    if( del_h )
        sqlite3_finalize(del_h);
    if( ins_h )
        sqlite3_finalize(ins_h);
    if( up_h )
        sqlite3_finalize(up_h);
    if( fetch_h )
        sqlite3_finalize(fetch_h);
    if( key_h )
        sqlite3_finalize(key_h);

    sqlite3_close(conn);
}

int Alicia::prepare_store() {
    int rc = 0;

    ss << "DELETE FROM symbol_table WHERE key = :key";
    string del_sql = ss.str();
    ss.str("");
    ss << "INSERT INTO symbol_table VALUES"
        << "(:key, :var, :value)";
    string ins_sql = ss.str();
    ss.str("");
    ss << "UPDATE symbol_table SET var = :var,"
        << "value = :value "
        << "WHERE key = :key";
    string up_sql = ss.str();
    ss.str("");
    ss << "SELECT value FROM symbol_table WHERE key = :key";
    string fetch_sql = ss.str();
    ss.str("");
    ss << "SELECT COUNT(*) FROM symbol_table "
        << "WHERE key = :key";
    string key_sql = ss.str();
    ss.str("");

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

int Alicia::sql_exec(const char* sql, int line) {
    int rc = 0;
    char *zErrMsg = 0;
    
    rc = sqlite3_exec(conn, sql, NULL, 0, &zErrMsg);
    if( rc != SQLITE_OK )
        printf("SQLITE_ERROR on line %d: %s\n", line, zErrMsg);
    sqlite3_free(zErrMsg);

    return rc;
}

bool Alicia::is_simple_exec( const char* sql ) {
    regex e ("^select ", icase );
    smatch m;
    ss.str("");
    ss << sql;
    string s = ss.str(); 

    return regex_search( s, m, e );
}

bool Alicia::key_exists( long long key ) {
    sqlite3_int64 k = key;
    sqlite3_bind_int64(key_h, 1, k);
    return strncmp(fetch_one_stmt(key_h, __LINE__), "1", 1);
}

//simple, use better versions if there is  a reason
long long Alicia::get_key(const char* var) {
    auto h = 0;
    while (*var)
       h = h << 1 ^ *var++;
    return h > 0 ? h : -h;
}

void Alicia::sql_fetch( const char* sql, int line ) {} //STUB

void Alicia::sql_exec_stmt( sqlite3_stmt* stmt, int line ) {
	int rc = 0;
//     auto rows;
    for(int row = 0; SQLITE_ROW == (rc = sqlite3_step(stmt)); ++row) {
		int col;
//         auto columns;
		for(col=0; col<sqlite3_column_count(stmt); col++) {
            // Note that by using sqlite3_column_text, sqlite will coerce the value into a string
//             string k = sqlite3_column_name(stmt, col);
//             string v = sqlite3_column_text(stmt, col);
                last_result_set[row][col] = (char*)sqlite3_column_text(stmt,col);
//             columns[k] = v;

		}
//         rows.push( columns );
	}
	if(SQLITE_DONE != rc) {
		fprintf(stderr, "Statement didn't finish (%i): '%s', on line %d\n", rc, sqlite3_errmsg(conn), line);
	}
// 	return rows;
}

char* Alicia::fetch_one_stmt( sqlite3_stmt* stmt, int line ) {
	sql_exec_stmt(stmt, line);
    return last_result_set[0][0];
}

char* Alicia::get( const char* var ) {
	sqlite3_int64 key = get_key(var);
    sqlite3_bind_int64(fetch_h, 1, key);
    return fetch_one_stmt(fetch_h, __LINE__);
}

void Alicia::set( const char* var, const char* val ) {
    auto key = get_key(var);
    
    sqlite3_int64 k = key;

    auto h = ins_h;
    if( key_exists(key) ) {
        h = up_h;
    }

    sqlite3_bind_int64(h, 1, k);
    sqlite3_bind_text(h, 2, var, strlen(var), SQLITE_STATIC);
    sqlite3_bind_text(h, 3, val, strlen(val), SQLITE_STATIC);

    sql_exec_stmt(h, __LINE__);
}
void Alicia::del( const char* var ) {
    sqlite3_int64 key = get_key(var);
    sqlite3_bind_int64(del_h, 1, key);
    sql_exec_stmt(del_h, __LINE__);
}

void Alicia::exec( const char* sql ) {
    if( is_simple_exec(sql) ) {
        sql_exec(sql, __LINE__);
    }
    else {
        sql_fetch(sql, __LINE__);
    }
}
