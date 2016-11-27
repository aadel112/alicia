#!/usr/bin/env perl

# do 'Alicia';
use Alicia;
use Data::Dumper;

$lrc = 0;
$a = new Alicia();
# $a = new Alicia('tmp.db');
# print Dumper( $a );
# $a->{debug} = 1;

main();

sub main {
    $rc = 0;
    $rc += $rc + test_basic();
    $rc += $rc + test_file_io();
    $rc += $rc + test_functions();
    $rc += $rc + test_json(); # using base json
    $rc += $rc + test_script1();
    $rc += $rc + test_globbing_and_csv_delims();
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


    return $lrc;
}

sub test_functions{

    $sql = "SELECT LOWER('AAA')";
    $r = $a->exec($sql);
    assert($r->[0][0] eq 'aaa', "C functions work", __LINE__);

    $sql = "SELECT SLEFT( 'aaccc', 2 )";
    $r = $a->exec($sql);
    $a->drop('it');
   
    $f = 'examples/peak_nos.csv';
    $out = `cat $f`;
    chomp $out;
    my @lines = split /\n/, $out;

#     foreach my $l ( @lines ) {
#         my @a = split /,/, $l;
# #         print "$a[0]\n";
#         my $s = "Select stimestamp($a[0])";
#         $r = $a->exec($s);
# #         print Dumper($r);
#     }

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

sub test_globbing_and_csv_delims {
    my $gfile = 'examples/glob.asql';
    my $o = $a->parse_and_execute_statements($gfile);
    my $wc = `cat out/etcout | grep '/var/' | wc -l`;
    chomp $wc;

    assert($wc > 0, "globbing and delims", __LINE__);
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
    $r = $a->exec($sql);
    return $r->[0][0];
}

sub test_json{
    $r = o('select json_object(\'ex\',\'[52,3.14159]\')');
    assert($r eq '{"ex":"[52,3.14159]"}', 
        "json loaded", __LINE__);

    return $lrc;
}

sub test_extended_agg {

    return $lrc;
}
