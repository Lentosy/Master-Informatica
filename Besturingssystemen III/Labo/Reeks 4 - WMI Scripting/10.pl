use strict;
use warnings;

use Win32::OLE qw(in);

my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");
my $service = $locator->ConnectServer("127.0.0.1", "root/CIMV2");

#ASSOCIATORS OF {Win32_Directory.Name="c:\\"} 
my @assoc_instances = in $service->AssociatorsOf("Win32_Directory.Name='c:\\'");
my %distinct_classes = ();


print "List of all the instances:\n";
for(@assoc_instances){
	print $_->{Path_}->{RelPath};
	print "\n";
	$distinct_classes{$_->{Path_}->{Class}} = undef;
}



my $count_distinct_classes = scalar keys %distinct_classes;
print "\nList of the distinct classes (count = $count_distinct_classes): \n";
print join "\n", keys %distinct_classes;