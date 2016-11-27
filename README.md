
NAME
====

**Alicia** - SQL As a high speed, all-purpose programming language

SYNOPSIS
========

Do you have an unhealthy love of sql and wish you could develop everything in it? Well now you can. Alicia aims to provide ultra high speed data calculations, along with all of the functionality of top-flight databases such as postgresql.

DESCRIPTION
===========

It runs as a single instance of sqlite in-memory, with all concurrency protections off to provide it even more speed as a single threaded application. Because its sqlite, the data is hyper-compressed. In fact you'll find programs you've written in other high-level languages will take thousands of times the amount of memory. and still run much more slowly. Especially with proper indexing. All of the extended finctions are written in C, as is sqlite itself. If you, the user want to add another function, this too is a breeze to do.

SQLite stores its data in a hyper-compressed format. Of course, it depends on your point-of-reference, but just comparing a perl hash to the same content dumped in SQLite; there's no comparison. I've seen instances where one algorithm was projected to take 62% of system RAM for over two days. The same algorithm re-implemented in SQLite and indexed and analyzed takes 20 minutes, and takes 0.1% of system RAM. In another case, one algorithm took about 2 and a half minutes, and over 40% of system RAM. Reimplenting the same algorithm in SQLite took 0.1% of memory, and ran in under 5 seconds.

So, memory is one great reason to use Alicia. Another is the immense speed of SQLite. When all concurrnency needs are ignored, and all persistence is removed, what do you have left? A very mature C project that is basically a drop-in replacement for a data structure.

Using perl's DBD::SQLite driver is a no-brainer compared to other implementatios, at this point. It's compiled with optimizations (-O2). It's got JSON and regex extensions built into it, and it allows function and aggregate creation.

INSPIRATION
===========

I've spent the last few years in the big data world. Perl is well known in this arena as is python, but there are a few client specific requirements that these languages simply can't address. In the big data world it is best to get all of your data at once, add some programming logic to fit requirements, and report on or load the data. In cases where you need to perform ranged indexing, for example, hashes simply don't cut it. Similarly, in cases where you have to pull back a lot of data, or use the data lake/warehouse like a OLTP system, you're going to hit some walls. OLAP systems cannot be used in this way. One problem attempting to do this can cause is making the database unusable to both yourself and everyone else. With Alicia, this can't happen because the data is local to your instance of Alicia. Any processing you do only affects you. The way Alicia overcomes the problem of too much data is by piggy-backing on sqlite's compression, which, as I've mentioned, consumes less memory than hashes or dictionaries by orders of magnitutde.

I implemented my first in-memory sqlite solution for a max concurrent sessions problem where the obvious, but very slow solution would be to loop through every second of time in a month period, storing the data in a hashes for start and end time, finding the users logged in at each second. The effect was amazing. I then implemented it as a replacement to a solution that had data for parent and child records keyed by the foreign key. This solution wasn't bad, and didn't have any performance problems, other than the fact that as time passed it was using more and more system memory, as the client was doing more business. At the time of implementation, it was over 40% of total memory. Another problem was that the proposed change would have made things much worse in both categories.

Another great implementation was for a certain type of summary process that ran thousand's of queries against the data warehouse (treating it like an OLTP system), and was basically one application that made the system unusable for two hours a day. Dumping a full month's worth of fact data into memory was unfeasible, but with sqlite, it worked perfectly, and the OLTP nature of the script was not a problem because it was a single local instance in memory. The run time of the script also dropped to under a minute.

I had realized a couple years back that every one in big data basically loves SQL. Most data people naturally want to do everything in SQL. I had thought even then, before I'd really conceptualized the how, that a better ETL tool than the sort of thing that's currently on the market would be a programming language that all data people speak. What language is that? SQL!

I then came to evangelize sqlite in-memory solutions for big data work. Afterall, what could be better than a super lightweight memory footprint, C speed, and SQL simplicity? It's superior to a perl hash or python dictionary in every way when you're able to create your table and load it, then add indexes, then analyze it. It uses less memory, and is faster.

SYNTAX
======

Now let's get into the nuts and bolts. There are really just 5 basic statements Alicia accepts.

`LOAD` - extend Alicia with a perl scipt, although, with Inline.pm, you can actually extend it in pretty much any language, as I've done with libAlicia.c. Run this at the beginning, and add custom functions, or run it at the end to do something else with the data. Load it into a table using some other connector, bypassing output file creation, produce an excel report, etc.  
If you wish to add functions, just write the functions following the examples in libAlicia.c, create a hash called %AliciaFuncs key = function name, value = number of parameters.

If it's an aggregate function, you will neen to package it, and define a hash of the same format, called %AliciaAggs.

ex: LOAD myext.pm ex: LOAD myext.java ex: LOAD myext.c

`READ INTO` - read a file or glob of files into a table. Using WITH allows you to overwrite the csv options, eg: separator, quote character, etc. The options use TEXT::CSV\_XS. All of the options available are those listed by that module.  
ex: READ FILE 'sample.csv' INTO TABLE sampletable; ex: READ GLOB '/tmp/\*.csv' INTO TABLE input; ex: READ GLOB '/etc/\*.conf' INTO atbl WITH ( sep\_char =&gt; undef, quote\_char =&gt; undef );

`WRITE FROM` - write to a file or STDOUT from a table  
ex: WRITE sample.out.csv FROM stage\_table;

`SET` - set a variable in \_st, the symbol table  
ex: SET('rev', reverse('zyx'))

`GET` - get a variable from \_st, the symbol table  
ex: GET('rev')

`SQL` - Any valid SQL statement  
ex: SELECT \* FROM \_st;

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

![Peak Chart](../img/peak.png)

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

![S&P500 Chart](../img/sp500.png)

Discussion
==========

This is nice to see. Although I have to admit, I expected Alicia to be faster than this based off my past experiences. The good thing about Alicia, though is that it's scalable in terms of adding and removing fields, whereas the perl version requires changes in multiple places. I should also note that I wanted to just do basic tests, so I didn't make these nearly as hard as I could have on the perl code. I basically tried to chose tests I could easily write in perl that
would show something meaningful.

Alicia has lots of room for improvement. I think it would benefit greatly from being completely in C. The startup time would definitely go down. I'm thinking the custom function time would go down a lot compared to perl, too. Certainly, I could try a form of memoization stored in SQLite like the symbol table. That, too may speed it up.

The big thing that really stood out to me, though was that in **both** tests Alicia's clarity really seemed top-notch to me. It's also much easier to make changes to. 
libAlicia.c
-----------

These methods extend Alicia to provide it with more functions from other databases.

Area|Function|Description|Parameters|Example|Example Return
-----|--------|-----------|-------------|----------|-----------
*S FUNCTIONS*|**slower**|Converts A field to all lower case text|a text field|`slower('HELLO')`|hello
*S FUNCTIONS*|**supper**|Converts A field to all upper case text|a text field|`supper('hello')`|HELLO
*S FUNCTIONS*|**sreverse**|Converts A field to the same text reversed|a text field|`sreverse('hello')`|olleh
*S FUNCTIONS*|**sleft**|returns the left len characters|(str, len)|`sleft('hello', 2)`|he
*S FUNCTIONS*|**sright**|returns the right len characters from the string str|(str, len)|`sright('hello', 2)`|lo
*S FUNCTIONS*|**sindex**|returns the 0 based index if the needle in haystack if it exists, else -1|(haystack, needle)|`sindex('hello', 'll')`|2
*S FUNCTIONS*|**ssubstr**|returns the portion of the string from start for len characters, 0-based.|(str, start, len)|`ssubstr('hello', 0, 3)`|hel
*S FUNCTIONS*|**suc_words**|returns the text field with words beginnings upper cased.|(str)|`suc_words('hello world')`|Hello World
*S FUNCTIONS*|**sascii**|returns the ascii decimal value of the character passed|(c)|`sascii('A')`|65
*S FUNCTIONS*|**schr**|returns the ascii char corresponding to int n|(n)|`schr(65)`|A
*S FUNCTIONS*|**sbtrim**|returns str with all of the characters in chars removed|(str, chars)|`sbtrim('xxaxybcxxy', 'xy')`|abc
*S FUNCTIONS*|**srpad**|returns str right-padded with fill repeatedly until it reaches length len|(str, len, fill)|`srpad('x', 5, 'yz')`|xyzyz
*S FUNCTIONS*|**slpad**|returns str left-padded with fill repeatedly until it reaches length len|(str, len, fill)|`slpad('x', 5, 'yz')`|yzyzx
*S FUNCTIONS*|**sreplace**|returns orig where rep is replaced with with|(orig, rep, with)|`sreplace('hello world', 'world', 'universe')`|hello universe
*S FUNCTIONS*|**srepeat**|returns str repeated n times|(str, n)|`srepeat('abc', 3)`|abcabcabc
*S FUNCTIONS*|**ssplit_part**|returns the 0-based field from  str split on delim|(str, delim, field)|`ssplit_part('hello world', ' ', 1)`|world
*S FUNCTIONS*|**sto_print**|returns the str with all non-printing characters removed|(str)|`sto_print('hello\nworld)`|helloworld
*S FUNCTIONS*|**sto_ascii**|returns the str with all non-ascii characters removed|(str)|`sto_ascii('hello˚, ˳world')`|helloworld
*S FUNCTIONS*|**sstrtotime**|not super functional, needs to be  coded out more. Only accepts 6 formats,  and epoch times|(str)|`sstrtotime('2016-11-05 03:14:59')`|1478315699
*S FUNCTIONS*|**sdate**|returns the date only of  the date-like string|(str)|`sstrtotime('2016-11-05 03:14:59')`|2016-11-05
*S FUNCTIONS*|**stimestamp**|returns the timestamp  the date-like string|(str)|`stimestamp('2016-11-05')`|2016-11-05 00:00:00
*S FUNCTIONS*|**sage**|returns the difference of date-like times e1 and e2|(e1, e2)|`sage('2016-11-05 03:14:59', '2016-11-05')`|0 years 0 days 3 hours 14 minutes 59 seconds
*S FUNCTIONS*|**scurrent_date**|returns the current date|()|`scurrent_date()`|2016-11-25
*S FUNCTIONS*|**scurrent_time**|returns the current time|()|`scurrent_time()`|14:33:32
*S FUNCTIONS*|**scurrent_timestamp**|returns the current timestamp|()|`scurrent_timestamp()`|2016-11-25 14:33:32
*S FUNCTIONS*|**sdate_part**|returns the piece of the timestamp specified as part; options are second, minute, hour, day, month, year, century, millenium, dow, doy|(part, timestamp)|`sdate_part('minute', '2016-11-25 14:33:32')`|33
*S FUNCTIONS*|**sdate_trunc**|returns the timestamp or date truncated at part; options are minute, hour, day, month, year|(part, timestamp)|`sdate_part('minute', '2016-11-25 14:33:32')`|2016-11-25 14:33:00
*A FUNCTIONS*|**covar_samp**|returns the sample covariance of expr1 and expr2|(expr1, expr2) both numeric|`covar_samp(expr1, expr2)`
*A FUNCTIONS*|**covar_pop**|returns the population covariance of expr1 and expr2|(expr1, expr2) both numeric|`covar_samp(expr1, expr2)`
*A FUNCTIONS*|**var_samp**|returns the sample variance of expr1|(expr1) numeric|`var_samp(expr1)`
*A FUNCTIONS*|**var_pop**|returns the population variance of expr1|(expr1) numeric|`var_pop(expr1)`
*A FUNCTIONS*|**regr_slope**|returns the slope of the line produced from expr1 and expr2|(expr1, expr2) numeric|`regr_slope(expr1, expr2)`
*A FUNCTIONS*|**regr_count**|returns the number of pairs in expr1 and expr2|(expr1, expr2) numeric|`regr_count(expr1, expr2)`
*A FUNCTIONS*|**corr**|returns the correlation constant produced from expr1 and expr2|(expr1, expr2) numeric|`corr(expr1, expr2)`
*A FUNCTIONS*|**stddev_pop**|returns the population standard deviation produced from expr1 and expr2|(expr1, expr2) numeric|`stddev_pop(expr1, expr2)`
*A FUNCTIONS*|**stddev_pop**|returns the sample standard deviation produced from expr1 and expr2|(expr1, expr2) numeric|`stddev_pop(expr1, expr2)`
*A FUNCTIONS*|**regr_avgx**|returns the average of the dependent variable x or expr1|(expr1, expr2) numeric|`regr_avgx(expr1, expr2)`
*A FUNCTIONS*|**regr_avgy**|returns the average of the independent variable y or expr2|(expr1, expr2) numeric|`regr_avgy(expr1, expr2)`
*A FUNCTIONS*|**regr_intercept**|returns the y intercept of the equation produced from expr1 and wxpr2|(expr1, expr2) numeric|`regr_intercept(expr1, expr2)`
*A FUNCTIONS*|**regr_sxx**|returns the validates model, like all other implementations|(expr1, expr2) numeric|`regr_sxx(expr1, expr2)`
*A FUNCTIONS*|**regr_syy**|returns the validates model, like all other implementations|(expr1, expr2) numeric|`regr_syy(expr1, expr2)`
*A FUNCTIONS*|**regr_sxy**|returns the validates model, like all other implementations|(expr1, expr2) numeric|`regr_sxy(expr1, expr2)`

To go along with these features there is also built-in regex and json support through the official sqlite extensions.
METHODS

**NOTE**  
These methods are specifix to Alicia.pm, using Alicia as a perl module instead of a CLI.

`new`  
Returns a new Alicia object, initializes the symbol table, called \_ST, creates its statements, indexes it; sets up an SQLite database as the memory-store. This is optimal for many reasons.

`main`  
Called by the CLI, initializes a new Alicia object, parses, and executes the Alicia script or stdin.

`parse_and_execute_statements`  
parses the very limited set of Alicia specific instructions, and executes them as appropriate

`set`  
is called by the execution if the instruction "SET('something', 'value'). You can nest these, such as SET('five', GET('three') + 2). This is pretty highly optimized, as it's very limited. These values are all stored in the symbol\_table (\_ST).

`get`  
is called by the execution if the instruction GET('something') is used. These can be nested, for example, GET(GET('value references something in \_ST'))

`drop`  
Drops a table

`truncate`  
Truncates a table

`exec`  
executes any sql that isn't in the limited instruction set

`read`  
reads a delimited file into a table, where the fields will be all text, and will be named like f0, f1, f2, etc.

`write`  
writes a table to a delimited file.

FAQ
===

**Question**: Can I use Alicia for web development?

You can, but the time to read the first instruction is way too much to make it viable, IMO. About .07 seconds on my machine. This is not something I've optimized for, but certainly, it could be made faster. I could load the database from a file, instead of building it from scratch every time. I could write more of the code in C, that does the parsing of instructions.

**Question**: How can Alicia be faster than C?

Generally, if a C algotithm has the exact same information as an Alicia algorithm, it will be faster, but Alicia which uses SQLite, is running on C as well. Anecdotally, for 99% of real-world data munging solutions properly implemented in both languages, Alicia should be faster.

The nature of a database is such that unless a C algorithm implemented a sorted B-Tree, and basically replicated everything a database does, the database is going to have the speed advantage on everything that's not a full-table scan as long as it's indexed.

With most databases, they have networking overhead. Even with SQLite, by default it's writing to the much slower file system, and using concurrency protection based locking and file syncing. With Alicia, all of this is turned off, and everything is in-memory.

**Question**: Why is speed so important any way?

Oftentimes, even for non-real time solutions, you still have reporting requirements of daily, hourly, etc. If the problem is fairly complex, this can sometimes be difficult to meet using conventional programming languages.

Whatever platform you're writing solutions on has a finite amount of computing power and memory. Developing a much faster solution frees up that macine(s) for more computations.

Alicia is implemented using SQL, which is a high level language, and the language of data people. It's not like your typical argument between C and perl or python.

**Question**: Alicia seems pretty limited. I'm not sure how I can use it for x, y, or z.

I've implemented Alicia with the full intention of it being geared towards people doing data munging, ETL, ELT, data analytics, business intelligence, etc. I would imagine it could also be useful to others in Engineering, and many other walks of life if I knew the functions they needed.

However, one of the awesome things about Alicia is that you can extend it in any way you want. By default it's extended in perl. Add the function following DBD::SQLite's instructions, and add the name and number of arguments to the appropriate hash. I've written my extension functions in C. Inline.pm allows you to extend Alicia in many different languages.

**Question**: I love this! Is there any way I can get enterprise level suppprt?

If this project has a good following, I will do my best to make sure it stays that way. If you need something beyond that, feel free to drop me a line -[mailto:aadel112@gmail.com](mailto:aadel112@gmail.com), but keep in mind that I'm one person with a full-time job.

**Question**: It doesn't suppprt concurrency or threading. Why is that?

Frankly, I dont't really see any reason at this point, but I may attempt to provide automatic paralleliztion later on.

As a single threaded application it is plenty fast, and staying that way allows it to be much faster than it otherwise would be. However, I'm sure there are cases where paralleliztion could demonstrate some speed benefits.

**Question**: I'd really love to integrate this with Tableau or some other BI tool. How can I do that?

One easy way would be to just output data as csv files being served from a web server, and have the BI tool read from that location. Like I said, though Alicia can be extended in any way.

CONTRIBUTING
============

Everyone is more than welcome to contribute. In fact, I'm grateful to any one that wants to contribute. It could be via spelling corrections (more than possible as I typed this on my phone), algorithm improvements, feature requests, or anything else.

If it's a feature request, please just open it up as an issue.

If it's an algorithm improvement, or new function please note that I'm only accepting C functions. Please submit it along with tests ahowing the improvent over, say 1000 iterations. Please note all the s functions can modify the string in-place.

If it's a spelling correction, please note that all documentation is in the code itself.

CONTACTING ME
=============

I can be contacted through this project, or by emailing me at -[mailto:aadel112@gmail.com](mailto:aadel112@gmail.com).

FUTURE PLANS
============

I really need to implement the set related functions from postresql, which I didn't really touch.

SSTRTOTIME should be made better.

I'd like to write more functions to cover more things. I'm thinking of starting by implementing the functions in numpy and scipy, and the algorithms in mahout.

I'd like to develop more of the main Alicia interpreter in C to make the load time more speedy, Right now although, you \*\*can\*\* do anything with Alicia, I wouldn't attempt to build a web site with it because the time just to load the symbol table and everything else, at least on my machine is almost .1 seconds. That's way too much IMO. So, to me that's really the biggest bottleneck. After that, it might be cool to develop some sort of web framework for Alicia.

On the roadmap, but way down the list, is getting automatic parallelization working.

LICENSE
=======

MIT License

Copyright (c) 2016 Aaron Adel

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

AUTHOR
======

Aaron Adel -<https://www.paypal.me/aadel112/5>, -<https://github.com/aadel112>
