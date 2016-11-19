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
    string pfsync = "PRAGMA synchronous = off";
//     string pthreads = "PRAGMA threads = 50";
    string pdirty = "PRAGMA read_uncomitted = true";
    string pvac = "PRAGMA auto_vaccum = full";

    string stat_sql = "ANALYZE";

    rc = sqlite3_open(DB_FILE, &conn);
    
    rc = !rc and sql_exec( create_sql, __LINE__ ); 
    rc = !rc and sql_exec( idx_sql, __LINE__ );
//     rc = !rc and sql_exec( pthreads.c_str(), __LINE__ ); 
    rc = !rc and sql_exec( pfsync, __LINE__ );
    rc = !rc and sql_exec( pdirty, __LINE__ );
    rc = !rc and sql_exec( pvac, __LINE__ );
    rc = !rc and sql_exec( stat_sql, __LINE__ );

    set("OUTPUT_FILE",DEFAULT_OUTPUT_FILE);
    set("INPUT_FILE",DEFAULT_INPUT_FILE);
    set("INPUT_TABLE", DEFAULT_INPUT_TABLE);
    set("DELIMITER",DEFAULT_DELIMITER);
    set("ESCAPE",DEFAULT_ESCAPE);
    set("RECORD_DELIMITER",DEFAULT_RECORD_DELIMITER);
    set("FILE_HEADER", DEFAULT_FILE_HEADER);

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

int Alicia::sql_exec(string sql, int line) {
    return sql_exec(sql.c_str(), line);
}

bool Alicia::is_simple_exec( const char* sql ) {
    regex e ("^(select) ", icase );
    smatch m;
    ss.str("");
    ss << sql;
    string s = ss.str(); 
   
    return !regex_search( s, m, e );
}

bool Alicia::is_simple_exec( string sql ) {
    return is_simple_exec(sql.c_str());
}

bool Alicia::key_exists( int key ) {
    prepare( KEY, key_sql );

    if( sqlite3_bind_int(key_h, 1, key) 
            != SQLITE_OK ) {
        fprintf(stderr, "Couldn't bind parameter 1 on line %d, %s\n", __LINE__, sqlite3_errmsg(conn));
    }
    string count = fetch_one_stmt(KEY, __LINE__);
    return !strncmp(count.c_str(), "1", 1);
}

//simple, use better versions if there is  a reason
int Alicia::get_key(const char* var) {
    int h = 0;
    while (*var)
       h = h << 1 ^ *var++;
    h = h > 0 ? h : -h;
    return h;
}

int Alicia::get_key(string var) {
    return get_key(var.c_str());
}

string Alicia::parameterize_exec(const char* sql) {
	regex e ("where([^]\\b]\\s*=\\s*[^\\b])+", icase);
    smatch m;
    
    ss.str("");
    ss << sql;
    string s = ss.str();
    ss.str("");

    string rep = regex_replace(s, e, "WHERE $1 = ?");
    return rep;
} 

string Alicia::parameterize_exec(string sql) {
    return parameterize_exec(sql.c_str());
}

vector<tuple<string,string>> Alicia::get_exec_parameters( const char* sql ) {
	vector<tuple<string,string>> v;
	regex e ("where([^\\b]\\s*=\\s*[^\\b])+", icase);
    smatch m;
    
    ss.str("");
    ss << sql;
    string s = ss.str();
    ss.str("");

	tuple<string,string> t;
	string s1;
	string s2;
	if (regex_search(s, m, e)) {
		for (int i=1; i<m.size(); ++i) { 
			ss << m[i];
			if(i % 2) {
				s1 = ss.str();
			}
			else {
				s2 = ss.str();
				t = make_tuple(s1, s2);
				v.push_back(t);
		   	}	
			ss.str("");
		}
	}
	ss.str("");

	return v;
}

vector<tuple<string,string>> Alicia::get_exec_parameters( string sql ) {
    return get_exec_parameters(sql.c_str());
}

bool Alicia::compiled_user_stmt(int stmt_key) {
	map<int,sqlite3_stmt*>::const_iterator it = stmt_map.find(stmt_key);
	return it!=stmt_map.end();
}

vector<vector<string>> Alicia::sql_fetch( const char* sql, int line ) {
    int rc = 0;
	const char *pzTest;    
	
	vector<vector<string>> v1;
   
    string parameterized_sql = parameterize_exec( sql );
    int stmt_key = get_key(parameterized_sql);
	sqlite3_stmt* stmt = compiled_user_stmt(stmt_key) ? stmt_map[stmt_key] : NULL;
    vector<tuple<string,string>> param_list = get_exec_parameters( sql );
	
	sqlite3_reset(stmt);
	if(!stmt or !compiled_user_stmt(stmt_key)) {
	   if ( rc = sqlite3_prepare_v2(
            conn, parameterized_sql.c_str(), 
            MAX_PREPARE_BYTES, &stmt, &pzTest
        ) != SQLITE_OK ) {
            fprintf(stderr, "Couldn't prepare %s on line %d, %s\n", parameterized_sql.c_str(), __LINE__, sqlite3_errmsg(conn));
        }
    }
    else {
    	stmt = stmt_map[stmt_key];
    }
    int i = 1;
    for (std::vector<tuple<string, string>>::iterator it = param_list.begin() ; !rc && it != param_list.end(); ++it) {
        tuple<string, string> t = *it;
        string col_name = std::get<0>(t);
        string col_value = std::get<1>(t);
        
        if( !strcmp(col_name.c_str(), "key") ) {
            string::size_type sz;
            if( sqlite3_bind_int(stmt, i,
                stoi(col_value, &sz)) != SQLITE_OK ) {
                fprintf(stderr, "Couldn't bind parameter %d on line %d, %s\n", i, __LINE__, sqlite3_errmsg(conn));
            }
        }
        else {
            if( sqlite3_bind_text(stmt, i, 
                col_value.c_str(), strlen(col_value.c_str()), 0) 
                    != SQLITE_OK ) {
                fprintf(stderr, "Couldn't bind parameter %d on line %d, %s\n", i, __LINE__, sqlite3_errmsg(conn));
            }
        }

        ++i;
    }

    int col_count = sqlite3_column_count(stmt);
    for(int row = 0; SQLITE_ROW == (rc = sqlite3_step(stmt)); ++row) {
		vector<string> v2;
        for(int col=0; col < col_count; ++col) {
            string v ( (const char*)sqlite3_column_text(stmt, col) );
//             DEBUG("FETCHED: '%s'\n", v.c_str());
            v2.push_back(v);
		}
        v1.push_back(v2);
	}
	if(SQLITE_DONE != rc) {
		fprintf(stderr, "Statement didn't finish (%i): '%s', on line %d\n", rc, sqlite3_errmsg(conn), line);
	}
    return v1;
}

vector<vector<string>> Alicia::sql_fetch( string sql, int line ) {
    return sql_fetch(sql, line);
}

vector<vector<string>> Alicia::sql_exec_stmt( int stmt_type, int line ) {
	int rc = 0;
    int resize_no = 0;
    vector<vector<string>> v1;
    int col_count = sqlite3_column_count(STMT);
    for(int row = 0; SQLITE_ROW == (rc = sqlite3_step(STMT)); ++row) {
		vector<string> v2;
        for(int col=0; col < col_count; ++col) {
            // Note that by using sqlite3_column_text, sqlite will coerce the value into a string
//             string k ( (const char*)sqlite3_column_name(STMT, col) );
            string v ( (const char*)sqlite3_column_text(STMT, col) );
            v2.push_back(v);
		}
        v1.push_back(v2);
//         if( row + 1 == ARRAY_STEP * (resize_no + 1) ) {
//             ++resize_no;
//             v1.resize( ARRAY_STEP * (resize_no + 1) );
//         }
	}
	if(SQLITE_DONE != rc) {
		fprintf(stderr, "Statement didn't finish (%i): '%s', on line %d\n", rc, sqlite3_errmsg(conn), line);
	}
    return v1;
}

string Alicia::fetch_one_stmt( int stmt_type, int line ) {
	vector<vector<string>> a = sql_exec_stmt(stmt_type, line);
    return a.size() > 0 ? a[0][0] : UNDEFINED;
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

int Alicia::prepare( int stmt_type, string sql ) {
    return prepare(stmt_type, sql.c_str());
}

string Alicia::get_file_contents( const char* ifile ) {
	// http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
	std::ifstream t(ifile);
	t.seekg(0, std::ios::end);
	size_t size = t.tellg();
	string buffer(size, ' ');
	t.seekg(0);
	t.read(&buffer[0], size);
	return buffer;
}

// http://stackoverflow.com/questions/3418231/replace-part-of-a-string-with-another-string
bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

string Alicia::get_file_contents(string s) {
	return get_file_contents(s.c_str());
}

//TODO - this is very rudimentary, esp the csv parse
//write tests to make sure this is sound
//possibly try to analyze col types and indexes
//as this is the tnl mosy of the etl will likely happen
int Alicia::read_into() {
    int rc = 0;
	const char *pzTest;   
    string strr = ",\\)$";
    regex r (strr, icase | ECMAScript );
    
    string ifile = get("INPUT_FILE");
    string itbl = get("INPUT_TABLE");
    string delim = get("DELIMITER");
    string esc = get("ESCAPE");
    string rec_delim = get("RECORD_DELIMITER");
    bool header = !strncmp(get("HEADER").c_str(), "1", 1);
    string close_paren = ")";

    string contents = get_file_contents(ifile);

    ss << "([^" << delim << "|" << rec_delim << "])+([" << rec_delim << "])*";
    string stre = ss.str();
    ss.str("");

   	regex e (stre, icase | ECMAScript);
    smatch m;

    vector<string> h;
    vector<vector<string>> v;
    vector<string> v1;
    string s, s2;
    int i = 0;
    int z = 0;
	int nl  = 0;
    while (regex_search(contents, m, e)) {
        s = m.str();
        
        ss << m[2];
        s2 = ss.str();
        ss.str("");

        nl = strlen( s2.c_str() ) > 0 and !s2.compare(rec_delim);
//         printf("%s-%s\n", s.c_str(), s2.c_str());
        if(nl) {
            s.pop_back();
        }
        if(!i and header) {
            h.push_back(s);
        }
        else {
            v1.push_back(s);
        }
        if(nl) {
            if(!header or i) {
                v.push_back(v1);
                v1.clear();
            }
            ++i;
        }

        if(!i) {
            ++z;
        }
        contents = m.suffix();
	}
    z = z ? z + 1 : z;
    if(!header) {
        for(int i = 0; i < z; ++i) {
            ss << "f" << i + 1;
            s = ss.str();
            h.push_back(s);
            ss.str("");
        }
    }
    ss << "CREATE TABLE IF NOT EXISTS " << itbl << "(";
    for (vector<string>::iterator it = h.begin() ; it != h.end(); ++it) {
        ss << *it << " text,";
    }
    ss << ")";
    string create_sql = ss.str();
    ss.str("");
    create_sql = regex_replace(create_sql, r, close_paren);
    DEBUG("Alicia::read_into: %s ON line %d\n", create_sql.c_str(), __LINE__);
    rc = !rc and sql_exec(create_sql, __LINE__);

    ss << "INSERT INTO " << itbl << " VALUES(";
    for (vector<string>::iterator it = h.begin() ; it != h.end(); ++it) {
        ss << "?,";
    }
    ss << ")";
    string insert_sql = ss.str();
    ss.str("");
    insert_sql = regex_replace(insert_sql, r, close_paren);
    DEBUG("Alicia::read_into: %s ON line %d\n", insert_sql.c_str(), __LINE__);

    sqlite3_stmt* stmt;
    
    if ( rc = sqlite3_prepare_v2(
        conn, insert_sql.c_str(), 
        MAX_PREPARE_BYTES, &stmt, &pzTest
    ) != SQLITE_OK ) {
        fprintf(stderr, "Couldn't prepare %s on line %d, %s\n", insert_sql.c_str(), __LINE__, sqlite3_errmsg(conn));
    }
    
    if(rc)
        return rc;
    else
        rc = SQLITE_DONE;

    for (vector<vector<string>>::iterator it = v.begin() ; SQLITE_DONE == rc and it != v.end(); ++it) {
        vector<string> tmp = *it;

        for( int i = 1; i <= tmp.size(); ++i ) {
            auto c = tmp[i-1].c_str();
            DEBUG("Alicia::read_into: Binding Param %d as %s ON line %d\n", i, c, __LINE__);
            if( sqlite3_bind_text(stmt, i, c, strlen(c), 0) 
                    != SQLITE_OK ) {
                fprintf(stderr, "Couldn't bind parameter %d on line %d, %s\n", i, __LINE__, sqlite3_errmsg(conn));
            }
        }
        rc = sqlite3_step(stmt);
        sqlite3_reset(stmt);
    }
	if(SQLITE_DONE != rc) {
		fprintf(stderr, "Statement didn't finish (%i): '%s', on line %d\n", rc, sqlite3_errmsg(conn), __LINE__);
	}
    else {
        rc = 0;
    }

    return rc;
}

int Alicia::write_out( const char* sql ) {
    int rc = 0;
    if(is_simple_exec(sql)) { 
        fprintf(stderr, "SQL is not output valid on line %d\n", __LINE__);
        return -1;
    }

    string outfile = get("OUTPUT_FILE");
    string delim = get("DELIMITER");
    string esc = get("ESCAPE");
    string rec_delim = get("RECORD_DELIMITER");
    bool header = !strncmp(get("HEADER").c_str(), "1", 1);
    string out = "stdout";
    auto results = sql_fetch(sql, __LINE__);

    if(outfile.compare(out)) {
        ofstream f (outfile);
        if (!f.is_open()) {
            fprintf(stderr, "Couldn't open %s on line %d\n", outfile.c_str(), __LINE__);
            return -2;
        }

        for (vector<vector<string>>::iterator it = results.begin() ; it != results.end(); ++it) {
            vector<string> tmp = *it;
            string joined = boost::algorithm::join(tmp, delim.c_str());
            f << joined << rec_delim;
        }
        f.close();
    }
    else {
        for (vector<vector<string>>::iterator it = results.begin() ; it != results.end(); ++it) {
            vector<string> tmp = *it;
            string joined = boost::algorithm::join(tmp, delim.c_str());
            cout << joined << rec_delim;
        }
    }
    return rc;
}

int Alicia::write_out( string sql ) {
    return write_out(sql.c_str());
}

void Alicia::truncate(const char* table) {
    ss << "DELETE FROM " <<  table;
    string sql = ss.str();
    sql_exec(sql, __LINE__);
    ss.str("");
}

void Alicia::truncate(string table) {
    truncate(table.c_str()); 
}

void Alicia::drop(const char* table) {
    ss << "DROP TABLE IF EXISTS " <<  table;
    string sql = ss.str();
    sql_exec(sql, __LINE__);
    ss.str("");
}

void Alicia::drop(string table) {
    drop(table.c_str());
}

string Alicia::get( const char* var ) {
	int key = get_key(var);
    if(key_exists(key)) {
        prepare( FETCH, fetch_sql );
        sqlite3_bind_int(fetch_h, 1, key);
        return fetch_one_stmt(FETCH, __LINE__);
    }
    return UNDEFINED;
}

string Alicia::get( string var ) {
    return var.c_str();
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
    }
}

void Alicia::set( string var, const char* val ) {
    set(var.c_str(), val);
}

void Alicia::set( string var, string val ) {
    set(var.c_str(), val.c_str());
}

void Alicia::set( const char* var, string val ) {
    set(var, val.c_str());
}

void Alicia::del( const char* var ) {
    int key = get_key(var);
    prepare( DELETE, del_sql );

    if( sqlite3_bind_int(del_h, 1, key) 
           != SQLITE_OK ) {
        fprintf(stderr, "Couldn't bind parameter 1 on line %d, %s\n", __LINE__, sqlite3_errmsg(conn));
    }

    sql_exec_stmt(DELETE, __LINE__);
}

void Alicia::del( string var ) {
    del(var.c_str());
}

vector<vector<string>> Alicia::exec( const char* sql ) {
    if( is_simple_exec(sql) ) {
        sql_exec(sql, __LINE__);
    }
    else {
        return sql_fetch(sql, __LINE__);
    }
}

vector<vector<string>> Alicia::exec( string sql ) {
    return exec(sql.c_str());
}
