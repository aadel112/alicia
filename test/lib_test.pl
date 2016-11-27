use Data::Dumper;
use Alicia;
do 'libAlicia.c';
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
a(slower('AAA') eq 'aaa', 'lower');
a(supper('aaa') eq 'AAA', 'upper');
a(sreverse('zyx') eq 'xyz', 'reverse');
a(sleft('abc', 2) eq 'ab', 'left');
a(sright('abc', 2) eq 'bc', 'right');
a(srepeat('aa', 3) eq 'aaaaaa', 'repeat');
a(sindex('abcdefg', 'cd') == 2, 'index');
a(ssubstr('aabsbsn', 2, 2) eq 'bs', 'substr');
a(sascii('A') == 65, 'ascii');
a(schr(65) eq 'A', 'chr');
a(sbtrim('zzzxxxyyyyzzxxzz', 'zx') eq 'yyyy', 'btrim');
a(srpad('aa', 9, 'bc') eq 'aabcbcbcb', 'rpad');
a(slpad('aa', 5, 'bc') eq 'bcbaa', 'lpad');
a(sreplace('hello world', 'hello', 'hi') eq 'hi world', 'replace');
a(srepeat('ac', 3) eq 'acacac', 'repeat');
a(ssplit_part('hello world', ' ', 0) eq 'hello', 'split_part');
a(sto_print("a\nba") eq 'aba', 'to_print');
a(sto_ascii('a') eq 'a', 'to_ascii');
a(suc_words('a bc') eq 'A Bc', 'uc_words');

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
a(sstrtotime('') >= $ep, 'empty strtotime');
setup_date_vars();
a(sstrtotime($ep) == $ep, 'time strtotime');
setup_date_vars();
a(sstrtotime($fmt2) == $ep, 'fmt2 strtotime');
setup_date_vars();
# print sstrtotime('11/25/16');
a(sstrtotime($ep2) == sstrtotime('11/25/16'), 'ep2 sstrtotime');
setup_date_vars();
a(sstrtotime($ts) == $ep, 'ts strtotime');
setup_date_vars();
a(sdate('') eq $dt, 'date');
setup_date_vars();
a(sdate('1480118400') eq '2016-11-26', 'date2');
setup_date_vars();
a(stimestamp('') eq $ts, 'timestamp');
setup_date_vars();
a(stimestamp('1480118400') eq '2016-11-26 00:00:00', 'timeatamp2');
setup_date_vars();
a(sage($dt, $ts) =~ m/^-/, 'negative age');
setup_date_vars();
a(scurrent_date() ge $dt, 'current_date');
setup_date_vars();
a(length(scurrent_time()) == 8, 'current_time' );
setup_date_vars();
a(sstrtotime(scurrent_timestamp()) >= $ep, 'current_timestamp' );
setup_date_vars();
a(sdate_part('day', $ep) eq $dd, 'date_part');
setup_date_vars();
$ep = $e;
a(sdate_trunc('minute', $ep) eq "$yy-$mm-$dd $hh:$min:00", 'date_trunc min');
setup_date_vars();
$ep = $e;
a(sdate_trunc('month', $ep) eq "$yy-$mm-01", 'date_trunc mon');
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



