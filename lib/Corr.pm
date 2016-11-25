package Corr;
use Data::Dumper;
sub new { bless [], shift; }
sub step { 
    my $self = shift; 
    push @$self, ($_[0]?$_[0]:0); 
    push @$self, ($_[1]?$_[1]:0);
}
sub finalize {
    return main::corr($_[0]);
}
