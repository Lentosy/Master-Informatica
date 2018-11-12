use strict;
use warnings;

use Win32::OLE qw(in); 

my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");

GetNameSpaces("root"); # start from root

sub GetNameSpaces {
	my $name = shift;
	my $service = $locator->ConnectServer("127.0.0.1", $name);
	if($service){ # can be unknown when not run as administrator
		my @namespaces = in $service->InstancesOf("__NAMESPACE");
		for(@namespaces){
			my $path = "$name/$_->{Name}";
			GetNameSpaces($path);
			print "$path\n";
		}
	} else {
		"Cannot access $name\n";
	}
}


