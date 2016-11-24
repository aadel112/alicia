#!/usr/bin/env perl

=head1 NAME

B<Alicia> - SQL As a high speed, all-purpose programming language

=head1 SYNOPSIS

=head1 DESCRIPTION

=head2 METHODS

=over 12

=item C<new>

Returns a new Alicia object, initializes the symbol table, called _ST, creates its statements, indexes it; sets up an SQLite database as the memory-store. This is optimal for many reasons.

=over 4

SQLite stores its data in a hyper-compressed format. Of course, it dependa on your point-of-reference, but just comparing a perl hash to the same content dumped in SQLite; there's no comparison. I've seen instances where one algorithm was projected to take 62% of system RAM for over two days. The same algorithm re-implemented in SQLite and indexed and analyzed takes 20 minutes, and takes 0.1% of system RAM. In another case, one algorithm took about 2 and a half minutes, and over 40% of system RAM. Reimplenting the same algorithm in SQLite took 0.1% of memory, and ran in under 5 seconds.

So, memory is one great reason to use Alicia. Another is the immense speed of SQLite. When all concurrnency needs are ignored, and all persistence is removed, what do you have left? A very mature C project that is  basically a drop-in replacement for a data structure. 

Using perl's DBD::SQLite driver is a no-brainer compared to other implementatios, at this point. It's compiled with optimizations (-O2). It's got JSON, regex extensions built into it, and it allows function and aggregate creation.

=back

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

Aaron Adel -L<http://aadel112.com>, -L<https://github.com/aadel112>

=cut

# from  https://metacpan.org/pod/DBD::SQLite#dbh-sqlite_create_function-name-argc-code_ref

package Alicia;
# use strict;
# use warnings;
# use Memoize;
use DBI;
use Text::CSV_XS qw( csv );
use Digest::CRC qw(crc32);
# use JSON::XS;
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
        if( $i - $offset == 1 and uc $e ne 'FILE' ) {
            die( "Syntax Error on statememt $stmt_no, token $e should be FILE\n" );
        }
        elsif( $i - $offset == 2 and ( ! -e $e or ! -r $e ) ) {
            die("Check file permissions for $e on statememt $stmt_no\n");
        }
        elsif( $i - $offset == 3 and uc $e ne 'INTO' ) {
            die("Syntax Error on statememt $stmt_no, token $e should be INTO\n");
        }
        elsif($i-$offset == 5 and uc $e ne 'WITH') {
            die("Syntax Error on statement $stmt_no, token $e should be WITH\n");
        }
    }
    my $file = $word_ref->[$offset+2];
    my $in = $word_ref->[$offset+4];

    my @rest = splice @$word_ref, 6, scalar(@$word_ref) - 6;
    my $csv_option_str = join ' ', @rest;
    my %csv_ops = scalar @rest ? eval $csv_option_str : ();

    %instr = (
        INSTR=> 'READ',
        FILE => $file,
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

my $get_set = sub {
    my $self = shift;
    my $str = shift;

    my @it = ('GET', 'SET');
    for my $s (@it) {
        while( my $sidx = index($s, $str) >= 0 ) {
            my @a = split //, $str;

            my $la = scalar @a;

            my $break = 0;
            my @stack = ();
            my $args = '';
            for(my $i=$sidx+3;$i<$la && !$break;++$i){
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

#     print "$sql\n";
    my $sth = $self->{conn}->prepare($sql);
    $sth->execute;
    
    my @arr = ();
    while( my $rr = $sth->fetch ) {
        my @a = @$rr;
        push @arr, \@a;
    }
    $sth->finish;
    if( defined $print_options ) {
        if( defined $print_options->{file} ) {
            open $fh, ">:encoding(utf8)", $print_options->{file};
        }
        my $csv = $self->{csv};
        foreach my $k ( keys %$print_options ) {
            $csv->{$k} = $print_options->{$k};
        }
       
        $csv->say( defined $print_options->{file} ? $fh : \*STDOUT, 
            $_
        ) for @arr;
        
        close $fh;
    }

    return \@arr;
};

my $register_lib = sub {
    my $self = shift;
    my $lib = shift;

    do $lib if( -e $lib );
    foreach my $f ( keys %AliciaFuncs ) {
        my $s = eval '\&' . $f;
        my ($argc, $not_deterministic) =  split /\|/, $AliciaFuncs{$f};
        $self->{conn}->sqlite_create_function(
            $f, $argc, $s, ($not_deterministic ? '' : SQLITE_DETERMINISTIC)
        );
    }
    undef %AliciaFuncs;

    foreach my $f ( keys %AliciaAggs ) {
#         my $s = eval '\&' . $f;
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

    $file ||= ':memory:';
    my $csv = Text::CSV_XS->new({ binary => 1 });

    my $dbh = DBI->connect("dbi:SQLite:dbname=$file","","");
    my $create_sql = "
    CREATE TABLE IF NOT EXISTS _ST (
    key int,
    var text,
    val text
    )
    ";
    my @dos = (
        $create_sql,
        "CREATE unique index idx01 ON _ST(key)",
        "ANALYZE",
        "PRAGMA synchronous = OFF",
        "PRAGMA auto_vacuum = INCREMENTAL",
        "PRAGMA journal_mode = OFF",
        "PRAGMA locking_mode = EXCLUSIVE",
        "PRAGMA read_uncommited = 1",
        "PRAGMA temp_store = MEMORY"
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

    my $corelib = 'lib/libAlicia.c';

    my $self = {
        conn => $dbh,
        hdls => \%handle_hash,
        csv => $csv,
        verbose => 1,
        core_lib => $corelib,
        debug => 0,
        test => 0,
        version_major => '0',
        version_minor => '1'
    };
    $self->$register_lib($corelib);
    
    $self->{version} = "$self->{version_major}.$self->{version_minor}";
    $VERSION = $self->{version};

    return bless $self, $class;
}

sub main { #TODO - help and error checking
    my $script_name = basename( $0 );
    our $self = Alicia->new();
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


    foreach my $s ( @ins ) {
        my %h = %$s;

        if( $h{INSTR} eq 'READ' ) {
            my $a1 = $self->$get_set($h{FILE});
            my $a2 = $self->$get_set($h{TABLE});
            my $a3 = $h->{WITH};
            $self->$DEBUG("Read '$a1', '$a2'", __LINE__);
            $self->read($a1, $a2, $a3);        
        }
        elsif( $h{INSTR} eq 'WRITE' ) {
            my $a1 = $self->$get_set($h{FILE});
            my $a2 = $self->$get_set($h{TABLE});
            my $a3 = $h->{WITH};
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
    my ( $self, $file, $table, $read_options ) = @_;
    my $csql = "CREATE TABLE IF NOT EXISTS $table (";
    my $sql = "INSERT INTO $table VALUES(";

    return $self if( not -s $file );
    
    my $sth;
    my $csv = $self->{csv};
    if( defined $read_options ) {
        foreach my $k ( keys %$read_options ) {
            $csv->{$k} = $read_options->{$k};
        }
    }

    open my $fh, "<:encoding(utf8)", $file;
    my $i = 0;
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

