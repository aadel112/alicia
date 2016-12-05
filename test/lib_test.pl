use Data::Dumper;
use Alicia;
do 'libAlicia.c';
use DBI;
# die();

sub a {
    my ($cond, $msg ) = @_;
    if( $cond ) {
        return 0;
    }
    else {
        print "Test '$msg' failed\n";
        return 1;
    }
}

sub setup_date_vars {
    my $setonly = shift;
    my @arr = ( 'ep','ep2', 'dt','ts','fmt2','yy','mm','dd','hh','min' );
    if($setonly) {
        foreach my $v ( @arr) {
            eval "\$o$v = \$$v;";
        }
    }
    if(!$setonly) {
        foreach my $v ( @arr) {
            eval "\$$v = \$o$v;";
        }
    }
}

#STRING FUNCTIONS
#====================
a(libAlicia::_lower('AAA') eq 'aaa', 'lower');
a(libAlicia::_upper('aaa') eq 'AAA', 'upper');
a(libAlicia::_reverse('zyx') eq 'xyz', 'reverse');
a(libAlicia::_leftstr('abc', 2) eq 'ab', 'left');
a(libAlicia::_rightstr('abc', 2) eq 'bc', 'right');
a(libAlicia::_repeat('aa', 3) eq 'aaaaaa', 'repeat');
a(libAlicia::_index('abcdefg', 'cd') == 2, 'index');
a(libAlicia::_substr('aabsbsn', 2, 2) eq 'bs', 'substr');
a(libAlicia::_ascii('A') == 65, 'ascii');
a(libAlicia::_chr(65) eq 'A', 'chr');
a(libAlicia::_btrim('zzzxxxyyyyzzxxzz', 'zx') eq 'yyyy', 'btrim');
a(libAlicia::_rpad('aa', 9, 'bc') eq 'aabcbcbcb', 'rpad');
a(libAlicia::_lpad('aa', 5, 'bc') eq 'bcbaa', 'lpad');
a(libAlicia::_replace('hello world', 'hello', 'hi') eq 'hi world', 'replace');
a(libAlicia::_repeat('ac', 3) eq 'acacac', 'repeat');
a(libAlicia::_split_part('hello world', ' ', 0) eq 'hello', 'split_part');
a(libAlicia::_to_print("a\nba") eq 'aba', 'to_print');
a(libAlicia::_to_ascii('a') eq 'a', 'to_ascii');
a(libAlicia::_uc_words('a bc') eq 'A Bc', 'uc_words');

#DATE FUNCTIONS
#==============
$ep = `date +%s`;
$e = `date +%s`;
$ep2 = `date -d '2016-11-25' +%s`;
$ep2 = `date -d '2016-11-25' +%s`;
$dt = `date -d\@'$ep' +%Y-%m-%d`;
$ts = `date -d\@'$ep' '+%Y-%m-%d %H:%M:%S'`;
$fmt2 = `date -d\@'$ep' '+%m/%d/%Y %H:%M:%S'`;
$yy = `date -d\@'$ep' +%Y`;
$mm = `date -d\@'$ep' +%m`;
$dd = `date -d\@'$ep' +%d`;
$hh = `date -d\@'$ep' +%H`;
$min = `date -d\@'$ep' +%M`;

chomp $ep;
chomp $e;
chomp $ep2;
chomp $dt;
chomp $ts;
chomp $fmt2;
chomp $yy;
chomp $mm;
chomp $dd;
chomp $hh;
chomp $min;

setup_date_vars(1);
a(libAlicia::_strtotime('') >= $ep, 'empty strtotime');
setup_date_vars();
a(libAlicia::_strtotime($ep) == $ep, 'time strtotime');
setup_date_vars();
a(libAlicia::_strtotime($fmt2) == $ep, 'fmt2 strtotime');
setup_date_vars();
# print sstrtotime('11/25/16');
a(libAlicia::_strtotime($ep2) == libAlicia::_strtotime('11/25/16'), 'ep2 sstrtotime');
setup_date_vars();
a(libAlicia::_strtotime($ts) == $ep, 'ts strtotime');
setup_date_vars();
a(libAlicia::_date('') eq $dt, 'date');
setup_date_vars();
a(libAlicia::_date('1480118400') eq '2016-11-26', 'date2');
setup_date_vars();
a(libAlicia::_timestamp('') eq $ts, 'timestamp');
setup_date_vars();
a(libAlicia::_timestamp('1480118400') eq '2016-11-26 00:00:00', 'timeatamp2');
setup_date_vars();
a(libAlicia::_age($dt, $ts) =~ m/^-/, 'negative age');
setup_date_vars();
a(libAlicia::_current_date() ge $dt, 'current_date');
setup_date_vars();
a(length(libAlicia::_current_time()) == 8, 'current_time' );
setup_date_vars();
a(libAlicia::_strtotime(libAlicia::_current_timestamp()) >= $ep, 'current_timestamp' );
setup_date_vars();
a(libAlicia::_date_part('day', $ep) eq $dd, 'date_part');
setup_date_vars();
$ep = $e;
a(libAlicia::_date_trunc('minute', $ep) eq "$yy-$mm-$dd $hh:$min:00", 'date_trunc min');
setup_date_vars();
$ep = $e;
a(libAlicia::_date_trunc('month', $ep) eq "$yy-$mm-01", 'date_trunc mon');
setup_date_vars();


#AGGREGATES
#==========
$v = Var_Samp->new();
my @values = (10, 9, 2, 3, 5, 7);
foreach my $val ( @values ) {$v->step($val);}
$variance = $v->finalize();
a($variance == 10.4, 'variance samp');

$c = Corr->new();
my @v1 = (43, 21, 25, 42, 57, 59);
my @v2 = (99, 65, 79,  75, 87, 81);
for(my $i = 0; $i < scalar @values; ++$i ) {
    $c->step($v1[$i], $v2[$i]) if($v1[$i]);
}
$corr = $c->finalize();
a(sprintf("%.04f", $corr) eq "0.5298", 'corr');

$s = Stddev_Samp->new();
for(my $i = 0; $i < scalar @values; ++$i ) {
    $s->step($v1[$i]);
}
$stddev = $s->finalize();
a(sprintf("%.04f", $stddev) == 15.7533, 'stddev sample');

$s = Stddev_Pop->new();
for(my $i = 0; $i < scalar @values; ++$i ) {
    $s->step($v1[$i]);
}
$stddev = $s->finalize();
a(sprintf("%.04f", $stddev) == 14.3807, 'stddev pop');

$c = Covar_Samp->new();
my @v1 = (43, 21, 25, 42, 57, 59);
my @v2 = (99, 65, 79,  75, 87, 81);
for(my $i = 0; $i < scalar @values; ++$i ) {
    $c->step($v1[$i], $v2[$i]) if($v1[$i]);
}
$v = $c->finalize();
a(sprintf("%.01f", $v) eq "95.6", 'covar_samp');

$c = Covar_Pop->new();
my @v1 = (43, 21, 25, 42, 57, 59);
my @v2 = (99, 65, 79,  75, 87, 81);
for(my $i = 0; $i < scalar @values; ++$i ) {
    $c->step($v1[$i], $v2[$i]) if($v1[$i]);
}
$v = $c->finalize();
a(sprintf("%.01f", $v) eq "79.7", 'covar_samp');

$c = Regr_Count->new();
my @v1 = (43, 21, 25, 42, 57, 59);
my @v2 = (99, 65, 79,  75, 87, 81);
for(my $i = 0; $i < scalar @values; ++$i ) {
    $c->step($v1[$i], $v2[$i]) if($v1[$i]);
}
$v = $c->finalize();
a( $v == 6, 'regr_count');

$c = Regr_Avgx->new();
my @v1 = (43, 21, 25, 42, 57, 59);
my @v2 = (99, 65, 79,  75, 87, 81);
for(my $i = 0; $i < scalar @values; ++$i ) {
    $c->step($v1[$i], $v2[$i]) if($v1[$i]);
}
$v = $c->finalize();
a(sprintf("%.03f", $v) eq "41.167", 'regr_avgx');

$c = Regr_Avgy->new();
my @v1 = (43, 21, 25, 42, 57, 59);
my @v2 = (99, 65, 79,  75, 87, 81);
for(my $i = 0; $i < scalar @values; ++$i ) {
    $c->step($v1[$i], $v2[$i]) if($v1[$i]);
}
$v = $c->finalize();
a(sprintf("%d", $v) eq "81", 'regr_avgy');

$c = Regr_Intercept->new();
my @v1 = (43, 21, 25, 42, 57, 59);
my @v2 = (99, 65, 79,  75, 87, 81);
for(my $i = 0; $i < scalar @values; ++$i ) {
    $c->step($v1[$i], $v2[$i]) if($v1[$i]);
}
$v = $c->finalize();
a(sprintf("%.3f", $v) eq "65.142", 'regr_intercept');

$c = Regr_Slope->new();
my @v1 = (43, 21, 25, 42, 57, 59);
my @v2 = (99, 65, 79,  75, 87, 81);
for(my $i = 0; $i < scalar @values; ++$i ) {
    $c->step($v1[$i], $v2[$i]) if($v1[$i]);
}
$v = $c->finalize();
a(sprintf("%.3f", $v) eq "0.385", 'regr_slope');


# # series tests
# 
# my $dbh = DBI->connect("dbi:SQLite:dbname=:memory:","","");
# $rc = libAlicia::create_series( $dbh ) ;
# a( !$rc , 'create_seies' );
#

# scipy tests
# ===========
#
a(libAlicia::_hypot(3, 4) == 5, 'hypot');
a(sprintf("%.3f", libAlicia::_deg2rad(360)) eq "6.283", 'deg2rad');
a(libAlicia::_rad2deg(libAlicia::_deg2rad(360)), 'rad2deg');
a(sprintf("%.3f", libAlicia::_sin(180)) eq "-0.801", 'sin');
a(sprintf("%.3f", libAlicia::_cos(180)) eq "-0.598", 'cos');
a(sprintf("%.3f", libAlicia::_tan(180)) eq "1.339", 'tan');
a(sprintf("%.3f", libAlicia::_arcsin(180)) eq "-1.248", 'arcsin');
a(sprintf("%.3f", libAlicia::_arccos(180)) eq "-1.671", 'arccos');
a(sprintf("%.3f", libAlicia::_arctan(180)) eq "0.747", 'arctan');
a(sprintf("%.3f", libAlicia::_arctan2(180, 360)) eq "0.464", 'arctan2');
a(sprintf("%.3f", libAlicia::_sinh(180)) =~ m/^7/, 'sinh');
a(sprintf("%.3f", libAlicia::_cosh(180)) =~ m/^7/, 'cosh');
a(sprintf("%.3f", libAlicia::_tanh(180)) eq '1.000', 'tanh');
a(sprintf("%.3f", libAlicia::_arcsinh(180)) eq '0.000', 'arcsinh');
a(sprintf("%.3f", libAlicia::_arccosh(180)) eq '0.000', 'arccosh');
a(sprintf("%.3f", libAlicia::_arctanh(180)) eq '1.000', 'arctanh');
a(sprintf("%.3f", libAlicia::_unwrap(8)) eq '1.717', 'unwrap');
a(sprintf("%.3f", libAlicia::_fix(-.9)) eq '0.000', 'fix');
a(sprintf("%.3f", libAlicia::_floor(-.9)) eq '-1.000', 'floor');
a(sprintf("%.3f", libAlicia::_ceil(-.9)) eq '0.000', 'ceil');
a(sprintf("%.3f", libAlicia::_trunc(-.9)) eq '0.000', 'trunc');
a(sprintf("%.3f", libAlicia::_logaddexp(-.9, 4)) eq '4.007', 'logaddexp');
a(sprintf("%.3f", libAlicia::_logaddexp2(-.9, 4)) eq '4.048', 'logaddexp2');
a(libAlicia::_signbit(-1) == 0, 'signbitn');
a(libAlicia::_signbit(1) == 1, 'signbitp');
a(libAlicia::_copysign(-1, -1) == -1, 'copysignn');
a(libAlicia::_copysign(-1, 1) == 1, 'copysignp');
a(libAlicia::_clip(-1, 0, 1) == 0, 'clipmin');
a(libAlicia::_clip(-1, -10, -2) == -2, 'clipmax');

$l = libAlicia::_log(10);
$e = libAlicia::_exp($l);
a($e eq '10', 'ln and e');
$l = libAlicia::_log2(10);
$e = libAlicia::_exp2($l);
print "$l, $e\n";
a($e eq '10', 'log2 and exp2');


# 
# print sprintf("%.3f", libAlicia::_logaddexp(-0.9, 4))."\n";
# print sprintf("%.3f", libAlicia::_logaddexp2(-0.9, 4))."\n";
# print sprintf("%.3f", libAlicia::_ceil(-0.9))."\n";
# print sprintf("%.3f", libAlicia::_trunc(-0.9))."\n";
# print sprintf("%.3f", libAlicia::_arccosh(180))."\n";
# print sprintf("%.3f", libAlicia::_arctanh(180))."\n";
# 

