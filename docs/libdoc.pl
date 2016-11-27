#!/usr/bin/env perl
use Data::Dumper;

my @stack = ();
print "libAlicia.c\n";
print "-----------\n";
print "\n";

print "These methods extend Alicia to provide it with more functions from other databases.\n\n";

my %so = (
    area => 0,
    description => 2,
    example => 4,
    function => 1,
    parameters => 3,
    'example return' => 5
);
print "Area|Function|Description|Parameters|Example|Example Return\n";
print "-----|--------|-----------|-------------|----------|-----------";

my %h = ();
my $i = 0;
while ( my $line = <> ) {
    chomp $line;
#         print "$line\n";
    if( $line =~ m/\/\*/ ) {
        push @stack, $line;
    }
    elsif( $line =~ m/\*\// ) {
        ++$i;

        pop @stack;
        if( scalar @stack == 0 ) {
            my @row = ();
            foreach my $k ( sort keys %h ) {
                my ( $o, $tag ) = split /,/, $k;
                if( $tag eq 'area' ) {
                    push @row, "*$h{$k}*";
                }
                elsif( $tag eq 'function' ) {
                    push @row, "**$h{$k}**";
                }
                elsif( $tag eq 'example' ) {
                    push @row, "`$h{$k}`";
                }
                else {
                    push @row, $h{$k};
                }
            }
            print ((join "|", @row) . "\n");
            %h = ();
        }
    }
    else {
        my ( $l, @rest ) = split /:/, $line;
        my $r = join ':', @rest;
        $l =~ s/\@//g;
        $l =~ s/\*//g;
        $l =~ s/^\s*|\s*$//g;
        $r =~ s/^\s*|\s*$//g;
        next unless( defined $so{$l} );
        my $k = "$so{$l},$l";
        $h{$k} = $r;
    }
}

print "\n";
print "To go along with these features there is also built-in regex and json support through the official sqlite extensions.\n";
