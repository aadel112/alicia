PL: sub trim {
    my $ret = $_[0];
    $ret =~ s/^\s+|\s+$//g;
    return $ret;
}
END
#testing only
PL: sub fibonacci {
    my %h = ();
    sub fibf {
        return 1 if($_[0] <= 2);
        if( defined $h{$_[0]} ) {
            return $h{$_[0]};
        }
        my $ret = fibf($_[0] - 1) + fibf($_[0] - 2);
        $h{$_[0]} = $ret;
        return $ret;
    };
    return fibf($_[0]);
}
END
PL: sub ls {
    my $out = `ls $_[0]`;
    chomp $out;
    return $out;
#     return split /\n/, $out;
}
END
