package Regr_Avgx;
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
    int n = regr_count(self);
    if( n < 1 )
        return 0;
    int div = 0;

    double B[size];

    for(i=0;i<n*2;++i) {
        div = i/2;
        if(i%2 != 0) {
            B[div] = SvNV(*av_fetch(a, i, 0));
        }
    }

    return mean(B, n);
}
...

