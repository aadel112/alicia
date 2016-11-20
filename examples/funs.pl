PL: sub trim {
    my $ret = $_[0];
    $ret =~ s/^\s+|\s+$//g;
    return $ret;
}
END
#testing only
PL: sub fibonacci {
    sub fibf {
        return 1 if($_[0] <= 2);
        return fibf($_[0] - 1) + fibf($_[0] - 2);
    };
    return fibf($_[0]);
}
END

