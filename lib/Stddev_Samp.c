package Stddev_Samp;
sub new { bless [], shift; }
sub step { push @{$_[0]}, $_[1] }
use Inline C => << '...';
double finalize(SV* self) {
    double m, standardDeviation = 0.0;
    AV* a = (AV*)SvRV(self);
    int i;
    int n = (int)av_tindex(a) + 1;
    if( n < 2 )
        return 0;

    double data[n];
    for(i=0;i<n;++i){
        data[i] = SvNV(*av_fetch(a, i, 0));
    }
    m = mean(data, n);

    for(i=0; i<n; ++i)
        standardDeviation += pow(data[i] - m, 2);

    return sqrt(standardDeviation/(n-1));
}

...

