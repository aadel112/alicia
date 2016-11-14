#include "alicia.hpp"

using namespace std;

Alicia::Alicia() {
    int rc = 0;
    char *zErrMsg = 0;

    ss << " CREATE TABLE symbol_table( "
        << "       key int, "
        << "       var text, "
        << "       value text"
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

    rc = sqlite3_open(DB_FILE, &conn);
    
    rc = !rc and sql_exec( create_sql.c_str(), __LINE__ ); 
    rc = !rc and sql_exec( idx_sql.c_str(), __LINE__ );
    rc = !rc and sql_exec( pthreads.c_str(), __LINE__ ); 
    rc = !rc and sql_exec( pdirty.c_str(), __LINE__ );
    rc = !rc and sql_exec( pvac.c_str(), __LINE__ );
    rc = !rc and sql_exec( stat_sql.c_str(), __LINE__ );

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

bool Alicia::key_exists( int key ) {
    prepare( KEY, key_sql );

    if( sqlite3_bind_int(key_h, 1, key) 
            != SQLITE_OK ) {
        fprintf(stderr, "Couldn't bind parameter 1 on line %d, %s\n", __LINE__, sqlite3_errmsg(conn));
    }
    return !strncmp(fetch_one_stmt(KEY, __LINE__), "1", 1);
}

//simple, use better versions if there is  a reason
int Alicia::get_key(const char* var) {
    int h = 0;
    while (*var)
       h = h << 1 ^ *var++;
    h = h > 0 ? h : -h;
    return h;
}

void Alicia::sql_fetch( const char* sql, int line ) {} //STUB

void Alicia::sql_exec_stmt( int stmt_type, int line ) {
	int rc = 0;
//     auto rows;
    for(int row = 0; SQLITE_ROW == (rc = sqlite3_step(STMT)); ++row) {
		int col;
//         auto columns;
		for(col=0; col<sqlite3_column_count(STMT); col++) {
            // Note that by using sqlite3_column_text, sqlite will coerce the value into a string
//             string k = sqlite3_column_name(stmt, col);
//             string v = sqlite3_column_text(stmt, col);
            last_result_set[row][col] = (char*)sqlite3_column_text(STMT,col);
//                 printf("%d, %d, %s\n", row, col, 
//                         last_result_set[row][col]);
//             columns[k] = v;

		}
//         rows.push( columns );
	}
	if(SQLITE_DONE != rc) {
		fprintf(stderr, "Statement didn't finish (%i): '%s', on line %d\n", rc, sqlite3_errmsg(conn), line);
	}
// 	return rows;
}

char* Alicia::fetch_one_stmt( int stmt_type, int line ) {
	sql_exec_stmt(stmt_type, line);
    return last_result_set[0][0];
}

int Alicia::prepare( int stmt_type, const char *sql ) {
    int rc = 0;
    const char *pzTest; 
    sqlite3_reset(STMT);
    if( !STMT ) {
        if ( rc = sqlite3_prepare_v2(
            conn, sql, 
            MAX_PREPARE_BYTES, &STMT, &pzTest
        ) != SQLITE_OK ) {
            fprintf(stderr, "Couldn't prepare %s on line %d, %s\n", sql, __LINE__, sqlite3_errmsg(conn));
        }
    }
    return rc;
}

char* Alicia::get( const char* var ) {
	int key = get_key(var);
    if(key_exists(key)) {
        prepare( FETCH, fetch_sql );
        sqlite3_bind_int(fetch_h, 1, key);
        return fetch_one_stmt(FETCH, __LINE__);
    }
    return NULL;
}

void Alicia::set( const char* var, const char* val ) {
    if( !conn ) 
        return;

    prepare( INSERT, ins_sql );
    prepare( UPDATE, up_sql );

    int key = get_key(var);
    if( !key_exists(key) ) {
        if( sqlite3_bind_int(ins_h, 1, key) 
                != SQLITE_OK ) {
            fprintf(stderr, "Couldn't bind parameter 1 on line %d, %s\n", __LINE__, sqlite3_errmsg(conn));
        }
        if( sqlite3_bind_text(ins_h, 2, var, 
                strlen(var), 0) 
                != SQLITE_OK ) {
            fprintf(stderr, "Couldn't bind parameter 2 on line %d, %s\n", __LINE__, sqlite3_errmsg(conn));
        }
        if( sqlite3_bind_text(ins_h, 3, val, 
                strlen(val), 0) 
                != SQLITE_OK ) {
            fprintf(stderr, "Couldn't bind parameter 3 on line %d, %s\n", __LINE__, sqlite3_errmsg(conn));
        }
        sql_exec_stmt(INSERT,__LINE__);
//         sqlite3_step(ins_h);
    } else {
        
        if( sqlite3_bind_text(up_h, 1, var, 
                strlen(var), 0) 
                != SQLITE_OK ) {
            fprintf(stderr, "Couldn't bind parameter 1 on line %d, %s\n", __LINE__, sqlite3_errmsg(conn));
        }
        if( sqlite3_bind_text(up_h, 2, val, 
                strlen(val), 0) 
                != SQLITE_OK ) {
            fprintf(stderr, "Couldn't bind parameter 2 on line %d, %s\n", __LINE__, sqlite3_errmsg(conn));
        }
        if( sqlite3_bind_int(up_h, 3, key) 
                != SQLITE_OK ) {
            fprintf(stderr, "Couldn't bind parameter 3 on line %d, %s\n", __LINE__, sqlite3_errmsg(conn));
        }
        sql_exec_stmt(UPDATE,__LINE__);
//         sqlite3_step(up_h);
    }
//     sql_exec_stmt(h, __LINE__);
}
void Alicia::del( const char* var ) {
    int key = get_key(var);
    prepare( DELETE, del_sql );

    if( sqlite3_bind_int(del_h, 1, key) 
            != SQLITE_OK ) {
        fprintf(stderr, "Couldn't bind parameter 1 on line %d, %s\n", __LINE__, sqlite3_errmsg(conn));
    }

    sql_exec_stmt(DELETE, __LINE__);
//     sqlite3_step(del_h); 
}

void Alicia::exec( const char* sql ) {
    if( is_simple_exec(sql) ) {
        sql_exec(sql, __LINE__);
    }
    else {
        sql_fetch(sql, __LINE__);
    }
}
