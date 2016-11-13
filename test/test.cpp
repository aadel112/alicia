#include "../alicia.hpp"
// #include <cassert>



static Alicia *a = new Alicia();
static int assert_failure = 0;

//implementing custom assert to get msg
void assert( bool cond, const char* msg, int line ) {
    if( !cond ) {
        cerr << "Warning!!: test '" << msg << "' failed on line " << line << endl;
        assert_failure = 1;
    }
}

int test_basics() {
    string t;

    assert(a != NULL, "object creation", __LINE__);
    
    t = "4";
    a->set( "data", "4" );
    char* b = a->get( "data" );
    assert( !strcmp(b, t.c_str()), "insert scalar", __LINE__ );

    string json = "{ a: \"4\", b: \"5\", c: { 0: 1}}";
    a->set( "json_sample", json.c_str() );
    char* s = a->get( "json_sample" );
    assert( !strcmp(json.c_str(), s), "json insert", __LINE__ );

	a->del("json_sample");
	char* s2 = a->get("json_sample");
	assert( s2 == NULL, "json delete whole" , __LINE__ );

	string sql;

    t = "5";
//     string x = "0";
	sql = "SELECT var + 1 FROM symbol_table WHERE var = 'data'";
	a->exec( sql.c_str() );
	assert( !strcmp(a->last_result_set[0][0], t.c_str()), "simple addition", __LINE__ );

    
    return assert_failure;
}

int test_json_ext() {
    string t;
    t = "4";
    string json = "{ a: \"4\", b: \"5\", c: { 0: 1}}";
    a->set( "json_sample", json.c_str() );
    char* s = a->get( "json_sample[a]" );
    assert( !strcmp(s,t.c_str()), "json get by object key", __LINE__ );

    t = "1";
    char* s2 = a->get( "json_sample[c][0]" );
    assert( !strcmp( s, t.c_str()), "json get by object key advanced", __LINE__ );

    t = "new";
    a->set("json_sample[c][1]", "new");
    char* s3 = a->get("json_sample[c][1]");
    assert( !strcmp(s, t.c_str()), "json insert new object key advanced", __LINE__ );
   
	a->del("json_sample[c][1]");
	char* s4 = a->get("json_sample[c][1]");
    assert( s == NULL, "json delete advanced", __LINE__ );

	return assert_failure;
}

int test_functions() {
	//TODO	

    return assert_failure;
}

int main(int argc, char** argv) {
    int rc = 0;
   
    // unit tests
    rc = !rc && test_basics();
    rc = !rc && test_json_ext();
    rc = !rc && test_functions();

    return rc;
}

