package Covar_Samp;
sub new { bless [], shift; }
sub step { 
    my $self = shift; 
    push @$self, ($_[0]?$_[0]:0); 
    push @$self, ($_[1]?$_[1]:0);
}
sub finalize{ main::covar_sample($_[0]) }
