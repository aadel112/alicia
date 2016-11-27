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
