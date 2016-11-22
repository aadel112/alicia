use Data::Dumper;
do 'lib/libAlicia.c';
die();

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
$dt = `date -d@'$ep' +%Y-%m-%s`;
$ts = `date -d@'$ep' +%Y-%m-%d %H:%M:%S`;
$fmt2 = `date -d@'$ep' +%m/%d/%Y %H:%M:%S`;
$yy = `date -d@'$ep' +%Y`;
$mm = `date -d@'$ep' +%m`;
$dd = `date -d@'$ep' +%d`;
$hh = `date -d@'$ep' +%H`;
$mm = `date -d@'$ep' +%M`;

chomp $ep;
chomp $dt;
chomp $ts;
chomp $fmt2;
chomp $yy;
chomp $mm;
chomp $dd;
chomp $hh;
chomp $mm;

a(sstrtotime('') == $ep, 'empty strtotime');
a(sstrtotime($ep) == $ep, 'time strtotime');
a(sstrtotime($fmt2) == $ep, 'fmt2 strtotime');
a(sstrtotime($ts) == $ep, 'ts strtotime');
a(sdate('') eq $dt, 'date');
a(stimestamp('') eq $ts, 'timestamp');
a(sage($dt, $ts) =~ m/^-/, 'negative age');
a(scurrent_date() ge $dt, 'current_date');
a(length(scurrent_time()) == 8, 'current_time' );
a(sstrtotime(scurrent_timestamp()) >= $ep, 'current_timestamp' );
a(sdate_part('day', $ep) eq $dd, 'date_part');
a(sdate_trunc('minute', $ep) eq "$yy-$mm-$dd $hh:$mm:00", 'date_trunc min');
a(sdate_trunc('month', $ep) eq "$yy-$mm-01 00:00:00", 'date_trunc min');


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
