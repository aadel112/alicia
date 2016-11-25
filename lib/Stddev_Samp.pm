package Stddev_Samp;
sub new { bless [], shift; }
sub step { push @{$_[0]}, $_[1] }
sub finalize { main::stddev_sample($_[0]) }
