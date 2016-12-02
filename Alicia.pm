#!/usr/bin/env perl

=head1 NAME

B<Alicia> - SQL As a high speed, all-purpose programming language

=head1 SYNOPSIS

Do you have an unhealthy love of sql and wish you could develop everything in it? Well now you can. Alicia aims to provide ultra high speed data calculations, along with all of the functionality of top-flight databases such as postgresql.

=head1 DESCRIPTION

It runs as a single instance of sqlite in-memory, with all concurrency protections off to provide it even more speed as a single threaded application. Because its sqlite, the data is hyper-compressed. In fact you'll find programs you've written in other high-level languages will take thousands of times the amount of memory. and still run much more slowly. Especially with proper indexing. All of the extended functions are written in C, as is sqlite itself. If you, the user want to add another function, this too is a breeze to do.

When I ran the benchmarks with simple programs, the memory use was about the same. I suspect, though that if you attempt to compare Alicia to anything complicated you'll see a big difference, as I have in the past because sqlite stores its data compressed. The only reason its comparable for simple programs is becuase you're doubling the data, once to read it into a text table, and then inserting it into a staging table.

So, memory is one great reason to use Alicia. Another is the immense speed of SQLite. When all concurrency needs are ignored, and all persistence is removed, what do you have left? A very mature C project that is  basically a drop-in replacement for a data structure. 

Writing some benchmark and example programs really struck a chord with me in just how much easier it was to write, read, and maintain sql-only programs.

Using perl's DBD::SQLite driver is a no-brainer compared to other implementations, at this point. It's compiled with optimizations (-O2). It's got JSON and regex extensions built into it, and it allows function and aggregate creation.

=head1 INSPIRATION

I've spent the last few years in the big data world. Perl is well known in this arena as is python, but there are a few client specific requirements that these languages simply can't address. In the big data world it is best to get all of your data at once, add some programming logic to fit requirements, and report on or load the data. In cases where you need to perform ranged indexing, for example, hashes simply don't cut it. Similarly, in cases where you have to pull back a lot of data, or use the data lake/warehouse like a OLTP system, you're going to hit some walls. OLAP systems cannot be used in this way. One problem attempting to do this can cause is making the database unusable to both yourself and everyone else. With Alicia, this can't happen because the data is local to your instance of Alicia. Any processing you do only affects you. The way Alicia overcomes the problem of too much data is by piggy-backing on sqlite's compression, which, as I've mentioned, consumes less memory than hashes or dictionaries by orders of magnitutde.

I implemented my first in-memory sqlite solution for a max concurrent sessions problem where the obvious, but very slow solution would be to loop through every second of time in a month period, storing the data in a hashes for start and end time, finding the users logged in at each second. The effect was 
amazing. I then implemented it as a replacement to a solution that had data for parent and child records keyed by the foreign key. This solution wasn't bad, and didn't have any performance problems, other than the fact that as time passed it was using more and more system memory, as the client was doing more business. At the time of implementation, it was over 40% of total memory. Another problem was that the proposed change would have made things much worse in both categories.

Another great implementation was for a certain type of summary process that ran thousand's of queries against the data warehouse (treating it like an OLTP system), and was basically one application that made the system unusable for two hours a day. Dumping a full month's worth of fact data into memory was unfeasible, but with sqlite, it worked perfectly, and the OLTP nature of the script was not a problem because it was a single local instance in memory. The run time of the script also dropped to under a minute.

I had realized a couple years back that every one in big data basically loves SQL. Most data people naturally want to do everything in SQL. I had thought even then, before I'd really conceptualized the how, that a better ETL tool than the sort of thing that's currently on the market would be a programming language that all data people speak. What language is that? SQL!

I then came to evangelize sqlite in-memory solutions for big data work. Afterall, what could be better than a super lightweight memory footprint, C speed, and SQL simplicity? 

=head1 SYNTAX

Now let's get into the nuts and bolts. There are really just 6 basic statements Alicia accepts.

=over 12

=item C<LOAD> - extend Alicia with a perl scipt, although, with Inline.pm, you can actually extend it in pretty much any language, as I've done with libAlicia.c. Run this at the beginning, and add custom functions, or run it at the end to do something else with the data. Load it into a table using some other connector, bypassing output file creation, produce an excel report, etc.

If you wish to add functions, just write the functions following the examples in libAlicia.c, create a hash called %AliciaFuncs key = function name, value = number of parameters.

If it's an aggregate function, you will need to package it, and define a hash of the same format, called %AliciaAggs.

ex: LOAD myext.pm

ex: LOAD myext.java

ex: LOAD myext.c

=item C<READ INTO> - read a file or glob of files into a table. Using WITH allows you to overwrite the csv options, eg: separator, quote character, etc. The options use TEXT::CSV_XS. All of the options available are those listed by that module.

ex: READ FILE 'sample.csv' INTO TABLE sampletable;

ex: READ GLOB '/tmp/*.csv' INTO TABLE input;

ex: READ GLOB '/etc/*.conf' INTO atbl WITH ( sep_char => undef, quote_char => undef ); 

=item C<WRITE FROM> - write to a file or STDOUT from a table

ex: WRITE sample.out.csv FROM stage_table;

=item C<SET> - set a variable in _st, the symbol table

ex: SET('rev', reverse('zyx'))

=item C<GET> - get a variable from _st, the symbol table

ex: GET('rev')

=item C<SQL> - Any valid SQL statement

ex: SELECT * FROM _st;

=back

=head2 METHODS

=over 12

=item B<NOTE>

These methods are specifix to Alicia.pm, using Alicia as a perl module instead of a CLI.

=item C<new>

Returns a new Alicia object, initializes the symbol table, called _ST, creates its statements, indexes it; sets up an SQLite database as the memory-store. This is optimal for many reasons.

=item C<main>

Called by the CLI, initializes a new Alicia object, parses, and executes the Alicia script or stdin.

=item C<parse_and_execute_statements>

parses the very limited set of Alicia specific instructions, and executes them as appropriate

=item C<set>

is called by the execution if the instruction "SET('something', 'value'). You can nest these, such as SET('five', GET('three') + 2). This is pretty highly optimized, as it's very limited. These values are all stored in the symbol_table (_ST). 

=item C<get>

is called by the execution if the instruction GET('something') is used. These can be nested, for example, GET(GET('value references something in _ST'))

=item C<drop>

Drops a table

=item C<truncate>

Truncates a table

=item C<exec>

executes any sql that isn't in the limited instruction set

=item C<read>

reads a delimited file into a table, where the fields will be all text, and will be named like f0, f1, f2, etc.

=item C<write>

writes a table to a delimited file.

=back

=head1 FAQ

B<Question>: Can I use Alicia for web development?

You can, but the time to read the first instruction is way too much to make it viable, IMO. About .07 seconds on my machine. This is not something I've optimized for, but certainly, it could be made faster. I could load the database from a file, instead of building it from scratch every time. I could write more of the code in C, that does the parsing of instructions.

B<Question>: Why is speed so important any way?

Oftentimes, even for non-real time solutions, you still have reporting requirements of daily, hourly, etc. If the problem is fairly complex, this can sometimes be difficult to meet using conventional programming languages.

Whatever platform you're writing solutions on has a finite amount of computing power and memory. Developing a much faster solution frees up that macine(s) for more computations.

Alicia is implemented using SQL, which is a high level language, and the language of data people. It's not like your typical argument between C and perl or python.

B<Question>: Alicia seems pretty limited. I'm not sure how I can use it for x, y, or z.

I've implemented Alicia with the full intention of it being geared towards people doing data munging, ETL, ELT, data analytics, business intelligence, etc. I would imagine it could also be useful to others in Engineering, and many other walks of life if I knew the functions they needed. 

However, one of the awesome things about Alicia is that you can extend it in any way you want. By default it's extended in perl. Add the function following DBD::SQLite's instructions, and add the name and number of arguments to the appropriate hash. I've written my extension functions in C. Inline.pm allows you to extend Alicia in many different languages.

B<Question>: I love this! Is there any way I can get enterprise level suppprt?

If this project has a good following, I will do my best to make sure it stays that way. If you need something beyond that, feel free to drop me a line -L<mailto:aadel112@gmail.com>, but keep in mind that I'm one person with a full-time job.

B<Question>: It doesn't suppprt concurrency or threading. Why is that?

Frankly, I dont't really see any reason at this point, but I may attempt to provide automatic paralleliztion later on.

As a single threaded application it is plenty fast, and staying that way allows it to be much faster than it otherwise would be. However, I'm sure there are cases where paralleliztion could demonstrate some speed benefits.

B<Question>: I'd really love to integrate this with Tableau or some other BI tool. How can I do that?

One easy way would be to just output data as csv files being served from a web server, and have the BI tool read from that location. Like I said, though Alicia can be extended in any way.

B<Question>: Is this production ready?

No! Ideally, to start off, I'd like to just get a lot of people interested, and maybe a few of them to help with development. I do think it's relatively close.

The speed and functionality are not where they need to be, though.

=head1 CONTRIBUTING

Everyone is more than welcome to contribute. In fact, I'm grateful to any one that wants to contribute. It could be via spelling corrections (more than possible as I typed this on my phone), algorithm improvements, feature requests, or anything else.

If it's a feature request, please just open it up as an issue.

If it's an algorithm improvement, or new function please note that I'm only accepting C functions. Please submit it along with tests ahowing the improvent over, say 1000 iterations. Please note all the s functions can modify the string in-place.

If it's a spelling correction, please note that all documentation is in the code itself.

=head1 CONTACTING ME

I can be contacted through this project, or by emailing me at -L<mailto:aadel112@gmail.com>.

=head1 FUTURE PLANS 

I really need to implement the set related functions from postresql, which I didn't really touch. Overall, Alicia just needs to support more. It needs a looping-type construct, although you can simulate one.

SSTRTOTIME should be made better.

I'd like to write more functions to cover more things. I'm thinking of starting by implementing the functions in numpy and scipy, and the algorithms in mahout.

I'd like to develop more of the main Alicia interpreter in C to make the load time more speedy, and eventually develop the whole thing in C.  Right now although, you B<can> do anything with Alicia, I wouldn't attempt to build a web site with it because the time just to load the symbol table and everything else, at least on my machine is almost .1 seconds. That's way too much IMO. So, to me that's really the biggest bottleneck. After that, it might be cool to develop some sort of web framework for Alicia.

On the roadmap, but way down the list, is getting automatic parallelization working. 

=head1 LICENSE

MIT License

Copyright (c) 2016 Aaron Adel

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

=head1 AUTHOR

Aaron Adel -L<https://www.paypal.me/aadel112/5>, -L<https://github.com/aadel112>

=cut

# from  https://metacpan.org/pod/DBD::SQLite#dbh-sqlite_create_function-name-argc-code_ref

package Alicia;
# use Memoize;
use strict;
no strict "subs"; 
use File::Glob ':globally'; 
use DBI;
use Text::CSV_XS qw( csv );
use Digest::CRC qw(crc32);
use Data::Dumper;
use File::Basename;
use vars '$VERSION';


my $DEBUG = sub {
    my $self = shift;
    my $msg = shift;
    my $ln = shift;

    if( $self->{debug} ) {
        print STDERR "$msg, ON LINE $ln\n";
    }
};

#TODO handle sep_char, quote_char, etc.
my $parse_read_instr = sub {
    my $self = shift;
    my $word_ref = shift;
    my $stmt_no = shift;
    my %instr = ();

    #expects a specific pattern
    #read file examples/sales.linux.csv into in;
    my $len = scalar @$word_ref;
    my $offset = 0;
    my $started = 0;
    my $syntax_error_token = -1;
    my $is_file = 0;
    die("Syntax Error on statememt $stmt_no, not enough tokens\n") unless( $len >= 5 );
    for( my $i = 0; $i < $len; ++$i ) {
        if( !$started and uc $word_ref->[$i] ne 'READ' ) {
            ++$offset;
            next;
        }
        elsif( !$started ) {
            $started = 1;
        }
        my $e = $word_ref->[$i];
        if( $i - $offset == 1 and ( uc $e ne 'FILE' and uc $e ne 'GLOB') ) {
            die( "Syntax Error on statememt $stmt_no, token $e should be FILE\n" );
        }
        elsif( $i - $offset == 2 ) {
            $is_file = uc $word_ref->[$i-$offset-1] eq 'FILE';
            if( ( ! -e $e or ! -r $e ) and $is_file  ) {
                die("Check file permissions for $e on statememt $stmt_no\n");
            }
        }
        elsif( $i - $offset == 3 and uc $e ne 'INTO' ) {
            die("Syntax Error on statememt $stmt_no, token $e should be INTO\n");
        }
        elsif($i-$offset == 5 and uc $e ne 'WITH') {
            die("Syntax Error on statement $stmt_no, token $e should be WITH\n");
        }
    }
    my $file = $word_ref->[$offset+2];
    $file =~ s/^['"]*//g;
    $file =~ s/['"]*$//g;

    my $in = $word_ref->[$offset+4];

    my @rest = splice @$word_ref, 6, scalar(@$word_ref) - 6;
    my $csv_option_str = join ' ', @rest;
    my %csv_ops = scalar @rest ? eval $csv_option_str : ();

    %instr = (
        INSTR=> 'READ',
        FILE => $is_file ? $file : undef,
        GLOB => !$is_file ? $file : undef,
        TABLE => $in,
        WITH =>\%csv_ops
    );

    return \%instr;
};

my $parse_write_instr = sub {
    #specific handle
    #WRITE FILE out/sales_facts.csv FROM sales_facts;
    my $self = shift;
    my $word_ref = shift;
    my $stmt_no = shift;
    my %instr = ();

    my $len = scalar @$word_ref;
    my $offset = 0;
    my $started = 0;
    my $syntax_error_token = -1;
    die("Syntax Error on statememt $stmt_no, not enough tokens\n") unless( $len >= 5 );
    for( my $i = 0; $i < $len; ++$i ) {
        if( !$started and uc $word_ref->[$i] ne 'WRITE' ) {
            ++$offset;
            next;
        }
        elsif( !$started ) {
            $started = 1;
        }
        my $e = $word_ref->[$i];
        if( $i - $offset == 1 and uc $e ne 'FILE' ) {
            die( "Syntax Error on statememt $stmt_no, token $e should be FILE\n" );
        }
        elsif( $i - $offset == 3 and uc $e ne 'FROM' ) {
            die("Syntax Error on statememt $stmt_no, token $e should be FROM\n");
        }
        elsif($i-$offset == 5 and uc $e ne 'WITH') {
            die("Syntax Error on statement $stmt_no, token $e should be WITH\n");
        }
    }
    my $file = $word_ref->[$offset+2];
    $file =~ s/^['"]*//g;
    $file =~ s/['"]*$//g;   

    my $out = $word_ref->[$offset+4];

    my @rest = splice @$word_ref, 6, scalar(@$word_ref) - 6;
    my $csv_option_str = join ' ', @rest;
    my %csv_ops = scalar @rest ? eval $csv_option_str : ();

    %instr = (
        INSTR => 'WRITE',
        FILE => $file,
        TABLE => $out,
        WITH =>\%csv_ops
    );

    return \%instr;
};

my $parse_load_instr = sub {
    #specific handle
    #WRITE FILE out/sales_facts.csv FROM sales_facts;
    my $self = shift;
    my $word_ref = shift;
    my $stmt_no = shift;
    my %instr = ();

    my $len = scalar @$word_ref;
    my $offset = 0;
    my $started = 0;
    my $syntax_error_token = -1;
    die("Syntax Error on statememt $stmt_no, not enough tokens\n") unless( $len >= 2 );
    for( my $i = 0; $i < $len; ++$i ) {
        if( !$started and uc $word_ref->[$i] ne 'LOAD' ) {
            ++$offset;
            next;
        }
        elsif( !$started ) {
            $started = 1;
        }
        my $e = $word_ref->[$i];
        if( $i - $offset == 1 and ( !-e $e or ! -r $e ) ) {
            die("Check file permissions for $e on statememt $stmt_no\n");
        }
    }
    my $file = $word_ref->[$offset+1];

    %instr = (
        INSTR => 'LOAD',
        FILE => $file
    );
    return \%instr;
};

my $get_set;
$get_set = sub {
    my $self = shift;
    my $str = shift;

    my $i;
    my @it = ('GET', 'SET');
    for my $s (@it) {
        while( my $sidx = index($s, $str) >= 0 ) {
            my @a = split //, $str;

            my $la = scalar @a;

            my $break = 0;
            my @stack = ();
            my $args = '';
            for($i=$sidx+3;$i<$la && !$break;++$i){
                if($a[$i] == '('){
                    push @stack, $a[$i];
                }
                elsif($a[$i] == ')' && scalar @stack) {
                    pop @stack;
                }
                elsif($a[$i] !~ m/\s/io){
                    $break = 1;
                }

                if(scalar @stack) {
                    $args .= $a[$i];
                }
            }
            if( $args =~ m/\s*$s\s*\(/g ) {
                $args = $self->$get_set($args);
            }
            else {
                if($s eq 'GET') {
                    $args = $self->get($args);
                }
                else {
                    $args = $self->set($args);
                }
            }
            $str = substr( $str, 0, $sidx ) . $args . substr($str, $i);
        }
    }
    return $str;
};

my $key_exists = sub {
    my $self = shift;
    my $key = shift;

    my $sth = $self->{hdls}->{fetch};
    $sth->execute($key);
    my $row = $sth->fetch;
    return defined $row->[0];
};

my $mk_key = sub {
    my $self = shift;
    my $txt = shift;
    my $key = crc32($txt);
    return $key;
};

my $is_select = sub {
    my $self = shift;
    my $sql = shift;

    return 1 if( $sql =~ m/SELECT\s+/io);
    return 0;
};

my $fetch = sub {
    my $self = shift;
    my $sql = shift;
    my $print_options = shift;

    #clone csv
    my $csv = bless { %{$self->{csv}} }, ref $self->{csv};
    my $fh;
#     print "$sql\n";
    my $sth = $self->{conn}->prepare($sql);
    $sth->execute;
    
    my @arr = ();
    while( my $rr = $sth->fetch ) {
        my @a = @$rr;
        push @arr, \@a;
    }
    $sth->finish;
#     print Dumper(@arr); die();
    if( defined $print_options ) {
        if( defined $print_options->{file} ) {
            open $fh, ">:encoding(utf8)", $print_options->{file};
        }
#         my $csv = $self->{csv};
        foreach my $k ( keys %$print_options ) {
            $csv->{$k} = $print_options->{$k};
        }
   
#         print Dumper($csv);die();
        $csv->say( defined $print_options->{file} ? $fh : \*STDOUT, 
            $_
        ) for @arr;
       
        close $fh if($fh);
    }

    return \@arr;
};

my $register_lib = sub {
    my $self = shift;
    my $lib = shift;

    our %AliciaAggs;
    our %AliciaFuncs;
    do $lib if( -e $lib );
    foreach my $f ( keys %AliciaFuncs ) {
#         my $sql_name = $f;
#         $sql_name =~ s/^s//g;
        my $s = eval '\&' . $f;
        my $fname = $f;
        $fname =~ s/^[^:]*:://g;
        my ($argc, $not_deterministic) =  split /\|/, $AliciaFuncs{$f};
        
        $self->{conn}->sqlite_create_function(
            $fname, $argc, $s, ($not_deterministic ? '' : SQLITE_DETERMINISTIC)
        );
    }
    undef %AliciaFuncs;

    foreach my $f ( keys %AliciaAggs ) {
        my ($argc, $not_deterministic) =  split /\|/, $AliciaAggs{$f};
        $self->{conn}->sqlite_create_aggregate(
            $f, $argc, $f, ($not_deterministic ? '' : SQLITE_DETERMINISTIC),
        );
    }
    undef %AliciaAggs;


    return $self;
};

__PACKAGE__->main( @ARGV ) unless caller();

sub new {
    my $class = shift;
    my $file = shift;

    my $MAX_ITER = 9007199254740992;
    $file ||= ':memory:';
    my $csv = Text::CSV_XS->new({ binary => 1 });

    my $dbh = DBI->connect("dbi:SQLite:dbname=$file","","");

    $dbh->sqlite_enable_load_extension(1);
    my $series_ext = $ENV{ALICIA_DIR} . '/vendor/libSeries' . ("$^0" eq 'MSWin32' ? '.dll' : '.so'); 
    $dbh->do("SELECT load_extension('$series_ext')");

    my $create_sql = "
    CREATE TABLE IF NOT EXISTS _ST (
    key int,
    var text,
    val text
    )
    ";
    my @dos = (
        $create_sql,
        "PRAGMA synchronous = OFF",
        "PRAGMA page_size = 65536",
        "PRAGMA auto_vacuum = INCREMENTAL",
        "PRAGMA journal_mode = OFF",
        "PRAGMA locking_mode = EXCLUSIVE",
        "PRAGMA read_uncommited = 1",
        "PRAGMA temp_store = MEMORY",
        "CREATE unique index idx01 ON _ST(key)",
        "ANALYZE"
    );
    foreach my $q (@dos) {
        $dbh->do($q);
    }

    my $ins_sql = "INSERT INTO _ST VALUES(?,?,?)";
    my $upd_sql = "UPDATE _ST SET var = ?, val = ? WHERE key = ?";
    my $del_sql = "DELETE FROM _ST WHERE key = ?";
    my $fetch_sql = "SELECT val FROM _ST WHERE key = ?";
    my %handle_hash = (
        ins => $dbh->prepare($ins_sql),
        upd => $dbh->prepare($upd_sql),
        del => $dbh->prepare($del_sql),
        fetch => $dbh->prepare($fetch_sql)
    );

    my $nref = (-$MAX_ITER..$MAX_ITER);

    my $corelib = $ENV{ALICIA_DIR} . "/" . 'libAlicia.c';
    
    my $self = {
        conn => $dbh,
        hdls => \%handle_hash,
        csv => $csv,
        verbose => 1,
        core_lib => $corelib,
        debug => 0,
        test => 0,
        version_major => '0',
        version_minor => '2'
    };
    $self->$register_lib($corelib);
    
    $self->{version} = "$self->{version_major}.$self->{version_minor}";
    $VERSION = $self->{version};

    return bless $self, $class;
}

sub main { #TODO - help and error checking
    my $script_name = basename( $0 );
    my $self = Alicia->new();
    $self->parse_and_execute_statements( $ARGV[0] );
} 

sub parse_and_execute_statements {
    my $self = shift;
    my $file = shift;

    my $code;
    my $ocode;
    if( $file ) {
       open my $h, '<', $file;
       $code = do { local $/; <$h> };
       close $h;
    }
    else { #stdin
        $code = do { local $/; <STDIN> };
    }

    $code =~ s/--.*$//g;
    
    my @cmds = split /;/, $code;

    my $instr_ref;
    my @ins = ();
    for(my $i = 0; $i<scalar @cmds; ++$i) {
        my $line = $cmds[$i];
        $line =~ s/^\s+|\s+$//g;
        next unless( $line );

        my @words = split /\s+/, $line;
        my $fword = uc $words[0];

        #simple set of instructions
        if( $fword eq 'READ' ) {
            $instr_ref = $self->$parse_read_instr(\@words, $i + 1);
        }
        elsif( $fword eq 'WRITE' ) {
            $instr_ref = $self->$parse_write_instr(\@words, $i + 1);
        }
        elsif( $fword eq 'LOAD' ) {
            $instr_ref = $self->$parse_load_instr(\@words, $i + 1);
        }
        else {
            my %h = (
                INSTR => 'STMT',
                STMT => $line
            );
            $instr_ref = \%h;
        }
        push @ins, $instr_ref;
    }

#     print Dumper(@ins); die();

    foreach my $s ( @ins ) {
        my %h = %$s;

        if( $h{INSTR} eq 'READ' ) {
            my $is_file = defined $h{FILE};

            my $a1 = $self->$get_set($is_file?$h{FILE}:$h{GLOB});

            my $a2 = $self->$get_set($h{TABLE});
            my $a3 = $self->$get_set($h{WITH});
            $self->$DEBUG("Read '$a1', '$a2', '$is_file', '$a3'", __LINE__);
            $self->read($a1, $a2, $is_file, $a3);
        }
        elsif( $h{INSTR} eq 'WRITE' ) {
            my $a1 = $self->$get_set($h{FILE});
            my $a2 = $self->$get_set($h{TABLE});
            my $a3 = $h{WITH};
            $self->$DEBUG("Write '$a1', '$a2'", __LINE__);
            $self->write($a1, $a2, $a3);
        }
        elsif( $h{INSTR} eq 'LOAD' ) {
            my $a = $self->$get_set($h{FILE});
            $self->$DEBUG("Do '$a'", __LINE__);
            $self->$register_lib($a);
        }
        else {
            my $a = $self->$get_set($h{STMT});
            $self->$DEBUG("Exec '$a'", __LINE__);
            $self->exec($a, {});
        }
    }

    return $self;
}


sub set {
    my $self = shift;
    my $var = shift;
    my $val = shift;

    my $key = $self->$mk_key($var);
    if( $self->$key_exists($key) ) {
        $self->{hdls}->{upd}->execute($var, $val, $key);
    }
    else {
        $self->{hdls}->{ins}->execute($key,$var,$val);
    }
    return $self;
}

sub get {
    my $self = shift;
    my $var = shift;
    my $val = shift;

    my $key = $self->$mk_key($var);
    if( $self->$key_exists($key) ) {
        my $sth = $self->{hdls}->{fetch};
        $sth->execute($key);
        my $row = $sth->fetch;
        my $ret = $row->[0];
        return $ret;
    }
    else {
        return undef;
    }
}

sub drop {
    my $self = shift;
    my $table = shift;

    $self->{conn}->do("DROP TABLE IF EXISTS $table");

    return $self;
}

sub truncate {
    my $self = shift;
    my $table = shift;

    $self->{conn}->do("DELETE FROM $table");
    $self->{conn}->do('VACUUM');
    return $self;
}

sub del {
    my $self = shift;
    my $var = shift;

    my $key = $self->$mk_key($var);
    if($self->$key_exists($key)) {
        my $sth = $self->{hdls}->{del};

        $sth->execute($key);
    }
    return $self;
}

sub exec {
    my ( $self, $sql, $print_options ) = @_;

    if( $self->$is_select($sql) ) {
        return $self->$fetch($sql, $print_options);
    }
    else {
        $self->{conn}->do($sql);
        return $self;
    }
}

sub read {
    my ( $self, $file, $table, $is_file, $read_options ) = @_;
    my $csql = "CREATE TABLE IF NOT EXISTS $table (";
    my $sql = "INSERT INTO $table VALUES(";

    
    my $sth;
#     my $csv = $self->{csv};

    # clone csv
    my $csv = bless { %{$self->{csv}} }, ref $self->{csv};    
    
    if( defined $read_options ) {
        foreach my $k ( keys %$read_options ) {
            $csv->{$k} = $read_options->{$k};
        }
    }

    my $glob = !$is_file ? $file : undef;
    my $file = !$is_file ? undef : $file;
    my @files = $is_file ? ( $file ) : eval "<$glob>";

    my $i = 0;
    foreach my $file ( @files ) {
        open my $fh, "<:encoding(utf8)", $file;
        while (my $row = $csv->getline ($fh)) {
            if(!$csv->{sep_char}){
                my $rs = join '', @$row;
                my @ra = ( $rs );
                $row = \@ra;
            }
            
            if( not $i ) {
                my $os = '';
                my @params = ();
                my @cols = ();
                for( my $z = 0; $z < scalar @$row; ++$z ) {
                    push @params, '?';
                    push @cols, "f$z text";
                }
                $csql .= (( join ",", @cols ) . ")");
                $self->{conn}->do($csql);
                $sql .= (( join ",", @params ) . ")");
                $sth = $self->{conn}->prepare($sql);
            }
            $sth->execute( @$row );
            ++$i;
        }
        close $fh;
    }
    return $self;
}

sub write {
    my ( $self, $file, $table, $write_options ) = @_;
    my %op = (file => $file);
    foreach my $k ( keys %$write_options ) {
        $op{$k} = $write_options->{$k};
    }
    my $sql = "SELECT * FROM $table";
    return $self->exec($sql, \%op);
}


