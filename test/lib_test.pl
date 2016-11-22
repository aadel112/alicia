use Data::Dumper;
do 'lib/libAlicia.c';

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
