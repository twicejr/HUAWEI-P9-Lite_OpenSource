package XML::SAX::Debian;

use strict;
use warnings;

use base "XML::SAX";

use File::Spec ();

sub save_parsers_debian {
    my $class = shift;
    my ($parser_module,$directory, $priority) = @_;

    # add parser
    {
        # We do not want load_parsers to complain.
        local $ENV{HARNESS_ACTIVE} = 1;
        $class->load_parsers("/nonexistent");
    }
    $class->add_parser($parser_module);

    # get parser's ParserDetails file
    my $file = $parser_module;
    $file = "${priority}-$file" if $priority != 0;
    $file = File::Spec->catfile($directory, $file);
    chmod 0644, $file;
    unlink($file);

    open(my $fh, ">$file") ||
        die "Cannot write to $file: $!";

    foreach my $p (@{ $class->parsers }) {
        print $fh "[$p->{Name}]\n";
        foreach my $key (keys %{$p->{Features}}) {
            print $fh "$key = $p->{Features}{$key}\n";
        }
        print $fh "\n";
    }

    print $fh "\n";

    close $fh;

    return $class;
}

1;
