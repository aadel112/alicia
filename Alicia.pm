#/usr/bin/env perl

# from  https://metacpan.org/pod/DBD::SQLite#dbh-sqlite_create_function-name-argc-code_ref



package Alicia;
# use strict;
# use warnings;
# use Memoize;
use DBI;
use Text::CSV_XS qw( csv );
use Digest::CRC qw(crc32);
use JSON;
use Data::Dumper;
use File::Basename;
use vars '$VERSION';

__PACKAGE__->main( @ARGV ) unless caller();

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
    my $self = {
        conn => $dbh,
        hdls => \%handle_hash,
        csv => $csv,
        verbose => 1,
        version_major => '0',
        version_minor => '1'
    };
    $self->{version} = "$self->{version_major}.$self->{version_minor}";
    $VERSION = $self->{version};

    return bless $self, $class;
}

sub main { #TODO - help and error checking
    my $script_name = basename( $0 );
    my $self = Alicia->new( $ARGV[0] );
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
                push @cols, "_$z text";
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
