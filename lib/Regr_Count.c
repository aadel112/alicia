package Regr_Count;
sub new { bless [], shift; }
sub step { 
    my $self = shift; 
    push @$self, ($_[0]?$_[0]:0); 
    push @$self, ($_[1]?$_[1]:0);
}
use Inline C => << '...';
double finalize(SV* self) {
    return regr_count(self);
}
...

