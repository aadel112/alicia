PL: sub trim {
    my $ret = $_[0];
    $ret =~ s/^\s+|\s+$//g;
    return $ret;
}
END
