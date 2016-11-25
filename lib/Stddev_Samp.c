package Stddev_Samp;
sub new { bless [], shift; }
sub step { push @{$_[0]}, $_[1] }
use Inline C => << '...';
double finalize(SV* self) {
	double sum = 0.0, mean, standardDeviation = 0.0;
    AV* a = (AV*)SvRV(self);
    int i;
    ssize_t n = av_tindex(a) + 1;
    if( n < 2 )
        return 0;
 	}

	for(i=0; i<n; ++i) {
		sum += data[i];
	}
	mean = sum/n;

    for(i=0; i<n; ++i)
        standardDeviation += pow(data[i] - mean, 2);

    return sqrt(standardDeviation/(n-1));
}

...

