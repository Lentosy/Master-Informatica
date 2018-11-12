use strict;
use warnings;

use Win32::OLE qw(in);

my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");
my $service = $locator->ConnectServer("127.0.0.1", "root/CIMV2");

my $instance = $service->Get("Win32_Service.Name='SNMP'");


my @properties = in $instance->{SystemProperties_};
push @properties, in $instance->{Properties_};

for(@properties){
	printf "%s : ", $_->{Name};
	
	if($_->{Value}){
		if($_->{IsArray}){
			my $value = $_->{Value};
			print join "," , @$value;
			print "\n";
		} else {
			printf "%s\n", $_->{Value};
		}
	} else {
		printf "No value found\n";
	}

	

}