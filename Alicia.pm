#/usr/bin/env perl

# from  https://metacpan.org/pod/DBD::SQLite#dbh-sqlite_create_function-name-argc-code_ref



package Alicia;
# use strict;
# use warnings;
# use Memoize;
use DBI;
use Text::CSV_XS qw( csv );
use Digest::CRC qw(crc32);
use JSON::XS;
use Data::Dumper;
use File::Basename;
use vars '$VERSION';

__PACKAGE__->main( @ARGV ) unless caller();

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
    my $self - shift;
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
        if( $i - $offset == 1 and uc $e ne 'file' ) {
            die( "Syntax Error on statememt $stmt_no, token $e should be FILE\n" );
        }
        elsif( $i - $offset == 2 and ( ! -e $e or ! -r $e ) ) {
            die("Check file permissions on statememt $stmt_no\n");
        }
        elsif( $i - $offset == 3 and uc $e ne 'into' ) {
            die("Syntax Error on statememt $stmt_no, token $e should be INTO\n");
        }

    }
    my $file = $word_ref->[$offset+2];
    my $in = $word_ref->[$offset+4];

    %instr = (
        INSTR=> 'READ',
        FILE => $file,
        TABLE => $in
    );

    return \%instr;
};

my $parse_write_instr = sub {
    #specific handle
    #WRITE FILE out/sales_facts.csv FROM sales_facts;
    my $self - shift;
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
        elsif( $i - $offset == 2 and ( ! -w $e ) ) {
            die("Check file permissions on statememt $stmt_no\n");
        }
        elsif( $i - $offset == 3 and uc $e ne 'FROM' ) {
            die("Syntax Error on statememt $stmt_no, token $e should be FROM\n");
        }

    }
    my $file = $word_ref->[$offset+2];
    my $out = $word_ref->[$offset+4];

    %instr = (
        INSTR => 'WRITE',
        FILE => $file,
        TABLE => $out
    );

    return \%instr;
};

my $parse_load_instr = sub {
    #specific handle
    #WRITE FILE out/sales_facts.csv FROM sales_facts;
    my $self - shift;
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
            die("Check file permissions on statememt $stmt_no\n");
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

    my $sth = $self->{conn}->prepare($sql);
    $sth->execute;
    
    my @arr = ();
    while( my $rr = $sth->fetch ) {
        my @a = @$rr;
        push @arr, \@a;
    }
    $sth->finish;
    if( defined $print_options ) {
        open $fh, ">:encoding(utf8)", $print_options->{file};
        my $csv = $self->{csv};
        foreach my $k ( keys %$print_options ) {
            $csv->{$k} = $print_options->{$k};
        }
       
        $csv->say ($fh, $_) for @arr;
        close $fh;
    }

    return $print ? $self : \@arr;
};

my $get_sql_fun_name = sub {
    my $self = shift;
    my $code = shift;

    if( $code =~ m/create\s+function\s+([^\(\s]+)\s*/io ){
        return $1;
    }
    return undef;
};

my $get_sql_fun_params = sub {
    my $self = shift;
    my $code = shift;

    my @params = ();
    my $fn = $self->$get_sql_fun_name($code);
#     print "'$fn'\n";
    my @a = $code =~ /$fn\s*\(([^\)]*)\)/id;
#     if($code =~ m/$fn\(([^\)]*)\)/iod) {
#     print Dumper(@a);
    foreach $a (@a) {
#         print "HERE";
        my $list = $1;
#         print $list."\n";
        my @p = split /,/, $list;
        foreach my $p ( @p ) {
            $p =~ s/^\s+|\s+$//;
            push @params, $p;
        }
    }
    return @params;
};

my $get_sql_fun_body = sub {
    my $self = shift;
    my $code = shift;

    my $ocode = $code;
    my @params = $self->$get_sql_fun_params($code);

    for(my $i = 0; $i < scalar @params; ++$i) {
        $code =~ s/$params[$i]/\$_[$i]/ig;
    }
    $code =~ s/.*\s+function\s+.*\)[\r\n]*//iog;
    $code =~ s/.*as\s+begin\s+//imo;
    $code =~ s/(\s+)end$/$1/io;

    $code =~ s/\s*SET\s+//iog;
    $code =~ s/@/\$/gio;
    $code =~ s/([\r\n]+)/;$1/g;
    $code =~ s/case\s*//iog;
    $code =~ s/when(.+)then/if\($1\) {/gio;
    $code =~ s/end/}/gio;
    $code =~ s/else/} else {/iog;
    $code =~ s/({|});/$1/go;
    $code = lc $code;

    return $code;
};

sub new {
    my $class = shift;
    my $file = shift;

    $file ||= ':memory:';
    my $csv = Text::CSV_XS->new({ binary => 1 });

    my $dbh = DBI->connect("dbi:SQLite:dbname=$file","","");
#     my $o = DBD::SQLite::compile_options();
#     print Dumper($o);
#     $dbh->sqlite_enable_load_extension(1);
# 	$sth = $dbh->prepare("select load_extension('vendor/libjson1')");
# 	$sth->execute(); 

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
    my $self = {
        conn => $dbh,
        hdls => \%handle_hash,
        csv => $csv,
        object => '$__ALICIA__',
        verbose => 1,
        debug => 1,
        version_major => '0',
        version_minor => '1'
    };
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

    $code =~ s/\-\-.*$//g;
    
    my @cmds = split /;/, $code;

    my $instr_ref;
    my @ins = ();
    for(my $i = 0; $i<scalar @cmds; ++$i) {
        my $line = $cmds[$i];
        $line =~ s/^\s+|\s+$//g;
        next unless( $line );

        my @words = split /\s+/, $line;
        my $fword = uc $words[0];

        $print = 0;
        if( $fword eq 'PRINT' ) {
            $print = 1;
            @words = reverse @words;
            @words = pop @words;
            next unless( scalar @words );

            @words = reverse @words;
            $fword = uc $words[0];
        }

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
            $self->$DEBUG("Read '$a1', '$a2'", __LINE__);
            $self->read($a1, $a2);        
        }
        elsif( $h{INSTR} eq 'WRITE' ) {
            my $a1 = $self->$get_set($h{FILE});
            my $a2 = $self->$get_set($h{TABLE});
            $self->$DEBUG("Write '$a1', '$a2'", __LINE__);
            $self->write($a1, $a2);
        }
        elsif( $h{INSTR} eq 'LOAD' ) {
            my $a = $self->$get_set($h{FILE});
            $self->$DEBUG("Do '$a'", __LINE__);
            do $a if( -e $a );
        }
        else {
            my $a = $self->$get_set($h{STMT});
            $self->$DEBUG("Exec '$a'", __LINE__);
            $self->exec($a);
        }
    }

    return $self;
}

sub get_statements {
    my $self = shift;
    return $self->{statements};
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

    $self->{conn}->do("DROP TABLE OF EXISTS $table");

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

sub create_function {
    my $self = shift;
    my $code = shift;
    my $is_perl = shift;

    if( !$is_perl ) {
        my $fnm = $self->$get_sql_fun_name($code);
        my $fnb = $self->$get_sql_fun_body($code);
#         $self->$DEBUG("FN: $fnm : $fnb\n", __LINE__);
        my $body = sub { 
            eval $fnb;
        };
#         print Dumper($body);
        $self->{conn}->sqlite_create_function(
            $fnm, -1, $body
        );
    }
    else {
        if( $code =~ m/sub\s+([^{\s]+)\s*{/o ) {
            my $fnm = $1;
            $code =~ s/sub\s+[^{]+{/sub {/o;
            my $fnb = $code;
            my $body = eval $fnb;
#             $self->$DEBUG("PLFN: $fnm : $fnb\n", __LINE__);
            $self->{conn}->sqlite_create_function(
                $fnm, -1, $body
            );
        }
    }
    return $self;
}
