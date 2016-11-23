use Data::Dumper;
do 'lib/libAlicia.c';
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

# die();
a(sstrtotime('') >= $ep, 'empty strtotime');
setup_date_vars();
# die();
a(sstrtotime($ep) == $ep, 'time strtotime');
setup_date_vars();
# die();
a(sstrtotime($fmt2) == $ep, 'fmt2 strtotime');
setup_date_vars();
# die();
a(sstrtotime($ts) == $ep, 'ts strtotime');
setup_date_vars();
# die();
# print sdate('');
a(sdate('') eq $dt, 'date');
setup_date_vars();
# die();
# print stimestamp('');
a(stimestamp('') eq $ts, 'timestamp');
setup_date_vars();
# die();
a(sage($dt, $ts) =~ m/^-/, 'negative age');
setup_date_vars();
# die();
a(scurrent_date() ge $dt, 'current_date');
setup_date_vars();
# die();
a(length(scurrent_time()) == 8, 'current_time' );
setup_date_vars();
# die();
a(sstrtotime(scurrent_timestamp()) >= $ep, 'current_timestamp' );
setup_date_vars();
# die();
a(sdate_part('day', $ep) eq $dd, 'date_part');
setup_date_vars();
# die();
a(sdate_trunc('minute', $ep) eq "$yy-$mm-$dd $hh:$min:00", 'date_trunc min');
setup_date_vars();
# print sdate_trunc('minute', $ep) . "\n";
# print "$yy-$mm-$dd $hh:$min:00\n";
# print sdate_trunc('month', $ep) ."\n";
# die();
a(sdate_trunc('month', $ep) eq "$yy-$mm-01", 'date_trunc mon');
setup_date_vars();

# 		sstrtotime => 1,
# 		sdate => 1,
# 		stimestamp => 1,
#         sage => 2,
#         scurrent_date => 0,
#         scurrent_time => 0,
#         scurrent_timestamp => 0,
#         sdate_part => 2,
#         sdate_trunc => 2

# 
# 		lower => 1,
# 		upper => 1,
#         reverse => 1,
#         left => 2,
#         right => 2,
#         index => 2,
#         substr => 3,
#         ascii => 1,
#         chr => 1,
#         btrim => 2,
#         rpad => 3,
#         lpad => 3,
#         replace => 3,
#         repeat => 2,
#         split_part => 3,
#         to_print => 1,
#         to_ascii => 1
# 
