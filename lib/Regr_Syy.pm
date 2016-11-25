package Regr_Syy;
sub new { bless [], shift; }
sub step { 
    my $self = shift; 
    push @$self, ($_[0]?$_[0]:0); 
    push @$self, ($_[1]?$_[1]:0);
}
sub finalize { main::regr_syy($_[0]) }
