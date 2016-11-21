#!/usr/bin/env perl

use Alicia;
use Data::Dumper;

$lrc = 0;
# $a = new Alicia();
$a = new Alicia('tmp.db');
# print Dumper( $a );

main();

sub main {
    $rc = 0;
    $rc += $rc + test_basic();
    $rc += $rc + test_file_io();
    $rc += $rc + test_functions();
    $rc += $rc + test_json(); # using base json
    $rc += $rc + test_script1();
#     $rc += $rc + test_os();
#     $rc += $rc + test_extended_agg();
    if( not $rc ) {
        print "All Tests Passed!\n";
    }
}

sub assert {
    my ( $c, $test, $line ) = @_;
    if( !$c ) {
        print STDERR "WARNING! '$test' test failed on line $line\n";
        $lrc += 1;
    }
    return $lrc;
}

sub test_basic{
    $a->set('a', 4);
    assert($a->get('a') == 4, "set get", __LINE__);

    $a->set('a', 5);
    assert($a->get('a') == 5, "update", __LINE__);

    $a->del('a');
    assert($a->get('a') == undef, "del", __LINE__);
    return $lrc;
}

sub test_file_io{
    $fi = 'examples/test_csv.csv';
    $fo = 'out/test_csv.csv';
    $a->read($fi, 'it');
    $res = $a->exec('SELECT * FROM it LIMIT 10');
    assert($res->[3][3] == ' 3 3', "read into", __LINE__);

    unlink $fo;
    $a->write($fo, 'it');
    $res = `cat $fi $fo | sed -r 's/"//g' | sort -u | wc -l`;
    chomp $res;
    $wc = `cat $fi | wc -l`;
    chomp $wc;
    assert($res == $wc, "io no diff", __LINE__);

    $a->drop('it');

    return $lrc;
}

sub test_functions{
    $f = 'examples/func.sql';
    create_funfile($f);

    $sql = "SELECT add_one(4)";
    $r = $a->exec($sql);
#     print Dumper($r);
    assert($r->[0][0] == 5, "add_one func", __LINE__);

#     $f = 'examples/fibonacci.sql';
#     create_funfile($f);
# 
#     $sql = "SELECT fibonacci(10)";
#     $r = $a->exec($sql);
#     print Dumper($r);
#     assert($r->[0][0] == 55, "fibonacci func", __LINE__);

    $f = 'examples/funs.pl';
    create_funfile_pl($f);

    $sql = "SELECT trim(f1) from it";
    $r = $a->exec($sql);
    assert($r->[0][0] eq "0 1", "pl func 1", __LINE__);

    $sql = "SELECT fibonacci(10)";
    $r = $a->exec($sql);
#     print Dumper($r);
    assert($r->[0][0] == 55, "fibonacci func", __LINE__);
#     $sql = "SELECT fibonacci(30)";
#     $r = $a->exec($sql);
#     print $r->[0][0] ."\n";

#     $sql = "SELECT ls()";
#     $r = $a->exec($sql);
#     print Dumper($r);
#     print $r->[0][0] ."\n";

#     $sql = "SELECT t()";
#     $r = $a->exec($sql);
#     print $r->[0][0] ."\n";
    return $lrc;
}

sub test_script1 {


    $script = 'examples/sales_etl.asql';
    $a->parse_and_execute_statements($script);

    @ofs = (
        'out/sales_facts.csv',
        'out/product_dim.csv',
        'out/payment_dim.csv'
    );
    $c = 0;
    foreach my $f(@ofs) {
        $c += 1 if( -s $f );
    }
    assert($c == scalar @ofs, "All output", __LINE__);


    return $lrc;
}

sub test_os {


    return $lrc;
}

sub create_funfile_pl {
    $f = $_[0];
    $fun_txt = `cat $f | grep -v ^#`;
    chomp $fun_txt;
    @arr = $fun_txt =~ /PL:([^END]+)END/og;
    foreach my $f (@arr) {
        $a->create_function( $f, 1 );
    }
}

sub create_funfile {
    $f = $_[0];
    $fun_txt = `cat $f`;
    chomp $fun_txt;
    $a->create_function( $fun_txt );
}

sub o {
    my ( $sql ) = @_;

#     print "$sql\n";
    $r = $a->exec($sql);
   
#     print Dumper($r);

    return $r->[0][0];
}

sub test_json{
    # https://www.postgresql.org/docs/9.3/static/functions-json.html
    # this is where I'm going ti try to pick up inspiration

    #going with leffer's version 
    #https://www.sqlite.org/src/artifact/e0797ef1bfa63742

    #pointless w/o arrays
#     $r = o("SELECT array_to_json('{{1,5},{99,100}}')");
#     assert($r eq '[[1,5],[99,100]]', "array_to_json", __LINE__);
#     
    
#     $r = o("SELECT row_to_json(row(1,'foo'))");
#     assert($r eq '{"f1":1,"f2":"foo"}', 'row_to_json', __LINE__);
# 
#     $r = o('SELECT to_json(\'Fred said "Hi."\'::text)');
#     assert($r eq "Fred said \"Hi.\"",'to_json',__LINE__);
# 
#     $r = o('SELECT json_array_length(\'[1,2,3,{"f1":1,"f2":[5,6]},4]\')');
#     assert($r == 5, 'json_array_length', __LINE__);

#     $r = o('select key from json_each(\'{"a":"foo", "b":"bar"}\')'); 
#     assert($r eq 'a', 'json_each', __LINE__);
# 
#     $r = o('SELECT json_extract_path(\'{"f2":{"f3":1},"f4":{"f5":99,"f6":"foo"}}\',\'f4\', \'f6\'');
#     assert($r eq '{"f5":99,"f6":"foo"}', 'json_extract_path_text', __LINE__);
# 
#     $r = o('json_object_keys(\'{"f1":"abc","f2":{"f3":"a", "f4":"b"}}\')');
#     assert($r eq 'f1', 'json_object_keys', __LINE__);
# 
#     $r = o('select a from json_populate_record(null::x, \'{"a":1,"b":2}\')');
#     assert($r == 1, 'json_populate_record', __LINE__);
# 
#     $r = o('select a from json_populate_recordset(null::x, \'[{"a":1,"b":2},{"a":3,"b":4}]\')');
#     assert($r == 1, 'json_populate_recordset', __LINE__);
# 
#     $r = o('select * from json_array_elements(\'[1,true, [2,false]]\')');
#     assert($r, 'json_array_elements', __LINE__);
# 
#     $r = o('select JSON(\'[1,2,3]\', 2)');
#     assert($r == 3, 'json array element', __LINE__);
# 
#     $r = o('select JSON(\'{"a":1,"b":2}\', b)');
#     assert($r == 2, 'json object field', __LINE__);
# 
#     $r = o('select JSON(\'{"a":[1,2,3],"b":[4,5,6]}\', \'{a, 2}\'');
#     assert($r == 3, 'json object path', __LINE__);

    $r = o('select json_object(\'ex\',\'[52,3.14159]\')');
    assert($r eq '{"ex":"[52,3.14159]"}', 
        "json loaded", __LINE__);

    return $lrc;
}

sub test_extended_agg {

    return $lrc;
}
