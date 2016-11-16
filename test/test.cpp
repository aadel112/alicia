#include "../alicia.hpp"
// #include <cassert>
#define UNDEFINED "undefined"
static Alicia *a = new Alicia();
static int assert_failure = 0;
static stringstream ss;

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
    string b = a->get( "data" );
    assert( !strcmp(b.c_str(), t.c_str()), "insert scalar", __LINE__ );
    
    string json = "{ a: \"4\", b: \"5\", c: { 0: 1}}";
    a->set( "json_sample", json.c_str() );
    string s = a->get( "json_sample" );
    assert( !strcmp(json.c_str(), s.c_str()), "json insert", __LINE__ );

	a->del("json_sample");
	string s2 = a->get("json_sample");
    assert( !strcmp(s2.c_str(),UNDEFINED), "json delete whole" , __LINE__ );
	
    string sql;
    t = "5";
	sql = "SELECT value + 1 FROM symbol_table WHERE var = 'data'";
	auto v = a->exec( sql.c_str() );
	assert( v.size() > 0 && !strcmp(v[0][0].c_str(), t.c_str()), "simple addition", __LINE__ );
    
    return assert_failure;
}

int test_file_io() {
    string file = "examples/test_csv.csv";
    string table = "input_file";
    
    a->set("INPUT_FILE", file);
    string it = a->get("INPUT_TABLE");


    ss << "select * from " << it << " LIMIT 10";
    string sql = ss.str();
    ss.str("");

    a->read_into();
    auto v = a->exec(sql);
    assert( v.size() > 10 && !strcmp(v[3][3].c_str(), "3, 3"),  "enclosed csv and size", __LINE__ );

    string file2 = "out/test_csv.csv";
    a->set("OUTPUT_FILE", file2);
    a->write_out();
    auto fp =  popen("diff out/test_csv.csv examples/test_csv.csv", "r");
    stringstream ss;
    ss << fp;
    pclose(fp);
    string s = ss.str();
    assert(!s.length(), "io diff", __LINE__ );

    a->truncate(it);
    v = a->exec(sql);
    assert( !v.size(), "drop file", __LINE__ );
    
    return assert_failure;
}

int test_json_ext() {
    string t;
    t = "4";
    string json = "{ a: \"4\", b: \"5\", c: { 0: 1}}";
    a->set( "json_sample", json.c_str() );
    string s = a->get( "json_sample[a]" );
    assert( !strcmp(s.c_str(),t.c_str()), "json get by object key", __LINE__ );

    t = "1";
    string s2 = a->get( "json_sample[c][0]" );
    assert( !strcmp( s.c_str(), t.c_str()), "json get by object key advanced", __LINE__ );

    t = "new";
    a->set("json_sample[c][1]", "new");
    string s3 = a->get("json_sample[c][1]");
    assert( !strcmp(s.c_str(), t.c_str()), "json insert new object key advanced", __LINE__ );
   
	a->del("json_sample[c][1]");
	string s4 = a->get("json_sample[c][1]");
    assert( !strcmp(s.c_str(), UNDEFINED), "json delete advanced", __LINE__ );

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
    rc = !rc && test_file_io();
    rc = !rc && test_json_ext();
    rc = !rc && test_functions();


    return rc;
}

