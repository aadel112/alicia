#!/usr/bin/env perl
use Data::Dumper;

$b=1480118400;
$e=1480204799;
$diff = $e - $b;

$f = $ARGV[0];
my $c = `cat $f`;
chomp $c;
my @lines = split /\n/, $c;
%h = ();
foreach my $l (@lines) {
    my ( $st, $en, $name, $id ) = split /,/, $l;

    for(my $i=0;$i<$en-$st;++$i){
        my $k = $st + $i;
        $h{$k}=defined $h{$k} ? ($h{$k}+1) : 1;
    }
}
# print Dumper(%h);
%m=();
for(my $i=$b; $i<$e; $i+=3600){
    my $max = 0;
    for(my $x=$i; $x<$i+3600; ++$x){
        $max = $h{$x} if($h{$x} > $max);
    }
    $m{$i} = $max;
}
foreach my $k ( sort keys %m ) {
    print "\"$k\", $m{$k}\n";
}
