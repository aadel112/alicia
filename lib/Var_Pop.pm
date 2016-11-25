package Var_Pop;
sub new { bless [], shift; }
sub step { push @{$_[0]}, $_[1] }
sub finalize { main::var_population($_[0]) }
