package Variance;
sub new { bless [], shift; }
sub step { push @{$_[0]}, $_[1] }
use Inline C => << '...';
double finalize(SV* self) {
    AV* a = (AV*)SvRV(self);
    int i;
    ssize_t n = av_tindex(a) + 1;
    if( n < 2 )
        return 0;
    
    double mu = 0;
    for(i=0;i<n;++i) {
        mu += SvNV(*av_fetch(a, i, 0));
    }
    mu /= (double)n;

    double sigma = 0;
    for(i=0;i<n;++i) {
        sigma += pow(SvNV(*av_fetch(a, i, 0)) - mu, 2);
    }
    sigma = sigma / (double)(n - 1);
    return sigma;

}
...

