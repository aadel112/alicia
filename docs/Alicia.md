    -   [METHODS](#METHODS)

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
