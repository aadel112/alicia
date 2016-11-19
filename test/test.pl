#!/usr/bin/env perl

use Alicia;
use Data::Dumper;

$lrc = 0;
$a = new Alicia();
# $a = new Alicia('tmp.db');
# print Dumper( $a );

main();

sub main {
    $rc = 0;
    $rc += $rc + test_basic();
    $rc += $rc + test_file_io();
    $rc += $rc + test_functions();
    $rc += $rc + test_json();
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
    return $lrc;
}

sub test_functions{
    $f = 'examples/func.sql';
    $fun_txt = `$f`;
    chomp $fun_txt;
    $a->create_function( $fun_txt );

    $sql = "SELECT add_one(4)";
    $r = $a->exec($sql);

    assert($r->[0][0] == 5, "io no diff", __LINE__);

    return $lrc;
}

sub test_json{

}
