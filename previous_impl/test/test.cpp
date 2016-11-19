#include "../alicia.hpp"
// #include <ctest>
#define UNDEFINED "undefined"
static Alicia *a = new Alicia();
static int test_failure = 0;
static stringstream ss;

//implementing custom test to get msg
void test( bool cond, const char* msg, int line ) {
    if( !cond ) {
        cerr << "Warning!!: test '" << msg << "' failed on line " << line << endl;
        test_failure = 1;
    }
}

string run_cmd(const char* cmd) {
	FILE *in;
    char buff[512];
	string ret;

	if(!(in = popen(cmd, "r"))){
        ret = "NULL";
		return ret;
    }
	ss.str("");
    while(fgets(buff, sizeof(buff), in)!=NULL){
        ss << buff;
    }
    pclose(in);
	ret = ss.str();
	ss.str("");
	return ret;
}


int test_basics() {
    string t;

    test(a != NULL, "object creation", __LINE__);
    
    t = "4";

    a->set( "data", "4" );
    string b = a->get( "data" );
    test( !strcmp(b.c_str(), t.c_str()), "insert scalar", __LINE__ );
    
    string json = "{ a: \"4\", b: \"5\", c: { 0: 1}}";
    a->set( "json_sample", json.c_str() );
    string s = a->get( "json_sample" );
    test( !strcmp(json.c_str(), s.c_str()), "json insert", __LINE__ );

	a->del("json_sample");
	string s2 = a->get("json_sample");
    test( !strcmp(s2.c_str(),UNDEFINED), "json delete whole" , __LINE__ );
	
    string sql;
    t = "5";
	sql = "SELECT value + 1 FROM symbol_table WHERE var = 'data'";
	auto v = a->exec( sql.c_str() );
	test( v.size() > 0 && !strcmp(v[0][0].c_str(), t.c_str()), "simple addition", __LINE__ );
    
    return test_failure;
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
    test( !strcmp(v[3][3].c_str(), " 3 3"),  "enclosed csv and size", __LINE__ );

    string file2 = "out/test_csv.csv";
    a->set("OUTPUT_FILE", file2);
    a->write_out("select * from " + it);
    auto diff =  run_cmd("diff out/test_csv.csv examples/test_csv.csv");
    test(!diff.length(), "io diff", __LINE__ );

    a->truncate(it);
    v = a->exec(sql);
    test( !v.size(), "drop file", __LINE__ );
    
    return test_failure;
}

int test_json_ext() {
    string t;
    t = "4";
    string json = "{ a: \"4\", b: \"5\", c: { 0: 1}}";
    a->set( "json_sample", json.c_str() );
    string s = a->get( "json_sample[a]" );
    test( !strcmp(s.c_str(),t.c_str()), "json get by object key", __LINE__ );

    t = "1";
    string s2 = a->get( "json_sample[c][0]" );
    test( !strcmp( s.c_str(), t.c_str()), "json get by object key advanced", __LINE__ );

    t = "new";
    a->set("json_sample[c][1]", "new");
    string s3 = a->get("json_sample[c][1]");
    test( !strcmp(s.c_str(), t.c_str()), "json insert new object key advanced", __LINE__ );
   
	a->del("json_sample[c][1]");
	string s4 = a->get("json_sample[c][1]");
    test( !strcmp(s.c_str(), UNDEFINED), "json delete advanced", __LINE__ );

	return test_failure;
}

int test_functions() {
	//TODO	

    return test_failure;
}

int main(int argc, char** argv) {
    int rc = 0;
   
    // unit tests
    rc = !rc && test_basics();
    rc = !rc && test_file_io();
    rc = !rc && test_functions();
    rc = !rc && test_json_ext();


    return rc;
}

