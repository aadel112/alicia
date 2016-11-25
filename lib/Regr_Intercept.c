package Regr_Intercept;
sub new { bless [], shift; }
sub step { 
    my $self = shift; 
    push @$self, ($_[0]?$_[0]:0); 
    push @$self, ($_[1]?$_[1]:0);
}
use Inline C => << '...';
double finalize(SV* self) {
    AV* a = (AV*)SvRV(self);
    int i;
    ssize_t n = av_tindex(a) + 1;
    if( n < 2 )
        return 0;
    int size = n / 2;
    int div = 0;

    double A[size];

    for(i=0;i<n;++i) {
        div = i/2;
        if(i%2 == 0) {
            A[div] = SvNV(*av_fetch(a, i, 0));
        }
    }


    return mean(A, size) / regr_slope(self);
}
...

