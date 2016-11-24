use Data::Dumper;
do 'lib/libAlicia.c';
# do 'lib/Variance.c';
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
    my @arr = ( 'ep','dt','ts','fmt2','yy','mm','dd','hh','min' );
    foreach my $v ( @arr) {
        eval "\$o$v = \$$v if( !\$o$v );";
    }
    
    foreach my $v ( @arr) {
        eval "\$$v = \$o$v;";
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
$dt = `date -d\@'$ep' +%Y-%m-%d`;
$ts = `date -d\@'$ep' '+%Y-%m-%d %H:%M:%S'`;
$fmt2 = `date -d\@'$ep' '+%m/%d/%Y %H:%M:%S'`;
$yy = `date -d\@'$ep' +%Y`;
$mm = `date -d\@'$ep' +%m`;
$dd = `date -d\@'$ep' +%d`;
$hh = `date -d\@'$ep' +%H`;
$min = `date -d\@'$ep' +%M`;

chomp $ep;
chomp $dt;
chomp $ts;
chomp $fmt2;
chomp $yy;
chomp $mm;
chomp $dd;
chomp $hh;
chomp $min;
setup_date_vars();

a(sstrtotime('') >= $ep, 'empty strtotime');
setup_date_vars();
a(sstrtotime($ep) == $ep, 'time strtotime');
setup_date_vars();
a(sstrtotime($fmt2) == $ep, 'fmt2 strtotime');
setup_date_vars();
a(sstrtotime($ts) == $ep, 'ts strtotime');
setup_date_vars();
a(sdate('') eq $dt, 'date');
setup_date_vars();
a(stimestamp('') eq $ts, 'timestamp');
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
a(sdate_trunc('minute', $ep) eq "$yy-$mm-$dd $hh:$min:00", 'date_trunc min');
setup_date_vars();
a(sdate_trunc('month', $ep) eq "$yy-$mm-01", 'date_trunc mon');
setup_date_vars();


#AGGREGATES
#==========
# print Dumper(%Variance::);
$v = Variance->new();
# print Dumper($v); die();
my @values = (10, 9, 2, 3, 5, 7);
foreach my $val ( @values ) {
    $v->step($val);
}
# die();
$variance = $v->finalize();

print $variance . "\n";



# variance_new();
# my @values = (10, 9, 2, 3, 5, 7);
# foreach my $val ( @values ) {
#     variance_step($val);
# }
# $variance = variance_finalize();
# 
# print $variance . "\n";

 
