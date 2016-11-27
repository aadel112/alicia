Performance
===========

I ran a few problems through a performance comparison. To be honest, the results were not super impressive.

This makes some sense, as Alicia hasn't really been optimized at all. In both cases, though, I think it's clear Alicia is the winner in logical presentation and readability.

In all tests I ran each 3 times using the linux command (time), and recorded the best time.

#### Test 1
The first test was the conventional peak sessions problem, where you have a list of users, and beginning and end session times, and you have to figure out the exact peak over a time interval, meaning the second, and count where the highesr number of people were using the system concurrently.

Here is the perl code:

```perl
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
```

Here is the Alicia code:

```sql
READ FILE perf_tests/seq.tbl INTO seqtxt;
READ FILE perf_tests/peak.data.small INTO factstxt;

create table secs ( epoch int );
insert into secs select * from seqtxt;
create index idxs01 on secs(epoch);
create table facts ( st int, en int );
insert into facts select f0, f1 from factstxt;
CREATE INDEX idxsf01 on facts(st,en);
ANALYZE;

CREATE TABLE peaks ( ep int, cnt int );

SELECT stimestamp(ep), m
FROM
(
SELECT (ep/3600*3600) || '' as ep, max(c) as m
FROM 
( 
    SELECT s.epoch as ep, count(*) as c
    From secs s, facts f 
    where s.epoch >= f.st and s.epoch <= f.en
    group by 1
) a 
GROUP BY 1 
) b
ORDER BY 1;

```

Here are the timings:

Code|1000 Records|10000 Records|50000 Records
----|------------|-------------|-------------
Perl|11.64|97.347|512.49
Alicia|7.47|57.687|293.26

![Peak Chart](https://raw.githubusercontent.com/aadel112/alicia/master/img/peak.png)

#### Test 2
In this test I wanted to see the timings of some of the extended functions Alicia provides.

Here is the perl code:

```perl
#!/usr/bin/env perl
use Data::Dumper;
use HTTP::Date;

$f = $ARGV[0];
$c = `cat $f`;
chomp $c;
@lines = split /\n/, $c;
@x1 = ();
@y1 = ();
foreach my $l (reverse @lines) {
    next if( $l =~ m/close/i );

    my ( $date, $open, $high, $low, $close ) = split /,/, $l;
    my $epoch = str2time( $date );

    ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime( $epoch );
    push @x1, $close;
    push @y1, ($close - $open);
}


print  join(",", 
    regr_slope(\@y1, \@x1),
    regr_intercept(\@y1, \@x1),
    regr_sxy(\@y1, \@x1)
) . "\n";

sub regr_sxy {
    return scalar @{$_[0]} * covar_pop(@_);
}

sub regr_intercept {
    return mean($_[0]) - regr_slope(@_) * mean($_[1]); 
}

sub regr_slope {
    return covar_pop($_[0], $_[1]) / var_pop($_[0]);
}

sub var_pop {
    my $sig = 0;
    my $mu = mean($_[0]);
    foreach my $v ( @{$_[0]} ) {
        my $tmp = $v - $mu;
        $sig += ($tmp* $tmp);
    }
    return $sig / scalar @{$_[0]};
}

sub covar_pop {
    my ( $r1, $r2 ) = @_;
    my $m1 = mean($r1);
    my $m2 = mean($r2);
    my $sos = 0;
    my $i;
    for( $i = 0; $i < scalar @{$r1}; ++$i) {
        $sos += ($r1->[$i] - $m1) * ($r2->[$i]-$m2);
    }
    return $sos / $i;
}

sub mean {
    my $sum = 0;
    my $i = 0;
    foreach my $v( @{$_[0]} ) {
        $sum += $v;
        ++$i;
    }
    return $sum / $i;
}

sub regr_count {
    return scalar @{$_[0]};
}

```

Here is the Alicia code:

```sql
READ FILE perf_tests/sp500.hlf.csv INTO factstxt;

create table sp(dt text, open real, high real, low real, close real); 
insert into sp select f0, f1, f2, f3, f4 from factstxt;
CREATE INDEX idxsf01 on sp(dt);
ANALYZE;

SELECT
regr_slope( diff, close),
regr_intercept( diff, close ),
regr_sxy( diff, close )
    FROM
    (
        SELECT 
        CLOSE - OPEN AS DIFF, 
        close
        FROM sp
    ) a ;
```

Here are the timings:

Code|1000 Records|8000 Records|16000 Records
----|------------|-------------|-------------
Perl|.048|.248|.470
Alicia|.109|.240|.440

![S&P500 Chart](https://raw.githubusercontent.com/aadel112/alicia/master/img/sp500.png)

Discussion
==========

This is nice to see. Although I have to admit, I expected Alicia to be faster than this based off my past experiences. The good thing about Alicia, though is that it's scalable in terms of adding and removing fields, whereas the perl version requires changes in multiple places. I should also note that I wanted to just do basic tests, so I didn't make these nearly as hard as I could have on the perl code. I basically tried to chose tests I could easily write in perl that
would show something meaningful.

Alicia has lots of room for improvement. I think it would benefit greatly from being completely in C. The startup time would definitely go down. I'm thinking the custom function time would go down a lot compared to perl, too. Certainly, I could try a form of memoization stored in SQLite like the symbol table. That, too may speed it up.

The big thing that really stood out to me, though was that in **both** tests Alicia's clarity really seemed top-notch to me. It's also much easier to make changes to. 
