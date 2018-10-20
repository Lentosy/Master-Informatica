use strict;
use warnings;

use Win32::OLE qw(in);

my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");
my $service = $locator->ConnectServer("127.0.0.1", "root/CIMV2");

#ASSOCIATORS OF {Win32_Directory} WHERE schemaonly 
my @associators = in $service->AssociatorsOf("Win32_Directory", undef, undef, undef, undef, undef, 1); # 1 geeft aan dat schemaonly is (7de paramater)
print scalar @associators;
for(@associators){
	print $_->{Path_}->{Class};
	print "\n";
}