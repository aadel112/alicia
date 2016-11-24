package Corr;
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

    double xx[size];
    double yy[size];
    double v, xsum = 0, ysum = 0, xysum = 0, 
           xsqsum = 0, ysqsum = 0, num, deno, coeff;

    for(i=0;i<n;++i) {
        div = i/2;
        v = SvNV(*av_fetch(a, i, 0));
        if(i%2) {
            yy[div] = v;
            xsum += xx[div];
            ysum += yy[div];
            xysum += (xx[div] * yy[div]);
            xsqsum += (xx[div] * xx[div]);
            ysqsum += (yy[div] * yy[div]);
        }
        else {
            xx[div] = v;
        }
    }
    ++div;

	num = ((div * xysum) - (xsum * ysum));
	deno = ((div * xsqsum - xsum * xsum)* (div * ysqsum - ysum * ysum));

	coeff = num / sqrt(deno);

    return coeff;
}
...

