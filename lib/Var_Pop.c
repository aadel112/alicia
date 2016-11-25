package Var_Pop;
sub new { bless [], shift; }
sub step { push @{$_[0]}, $_[1] }
use Inline C => << '...';
double finalize(SV* self) {
    return var_population(self);
}
...

