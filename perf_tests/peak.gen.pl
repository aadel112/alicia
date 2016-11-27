#!/usr/bin/env perl

$b=1480118400;
$e=1480204799;
$diff = $e - $b;

$n = $ARGV[0];

@fnames = ('Aaron', 'Fred', 'Barney', 'Betty', 'Wilma' );
@lnames = ( 'Adel', 'Flintstone', 'Rubble', 'Public', 'Doe');

for(my $i =0; $i < $n; ++$i) {
    $r = rand($diff) % $diff;
    $r2 = rand($diff) % $diff;
    $r2 = $r > $r2 ? $r + 100 : $r2; 
    $ep = $b + $r;
    $ep2 = $b + $r2;
    $f = $fnames[($r % scalar @fnames)];
    $l = $lnames[($r % scalar @lnames)];
    $x = $i + 1;
    print "$ep,$ep2,$f $l,$x\n";
}
