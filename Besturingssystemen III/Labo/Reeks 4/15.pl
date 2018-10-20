use strict;
use warnings;

use Win32::OLE qw(in);
use Win32::OLE::Variant;

my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");
my $datetime = Win32::OLE->new("WbemScripting.SWbemDateTime");
my $service = $locator->ConnectServer("127.0.0.1", "root/CIMV2");

my $instance = $service->Get("Win32_OperatingSystem=@");


my @properties = in $instance->{SystemProperties_};
push @properties, in $instance->{Properties_};

for(@properties){
	printf "%s : ", $_->{Name};
	
	if($_->{Value}){
		if($_->{CIMType} == 101){
			$datetime->{Value} = $_->{Value};
			printf "%s\n", $datetime->GetVarDate;
		} else {
			$_->{IsArray} ? print join ",", @{$_->{Value}} . "\n"
						  : printf "%s\n", $_->{Value};
		}
	} else {
		printf "No value found\n";
	}

	

}