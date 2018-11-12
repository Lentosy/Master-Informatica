use strict;
use warnings;

use Win32::OLE qw(in);



my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");
my $service = $locator->ConnectServer("127.0.0.1", "root/CIMv2");

my @Win32_Environment_Instances = in $service->InstancesOf("Win32_Environment");

for(@Win32_Environment_Instances){
	printf "USER = %-20s <%s = %s> \n", $_->{UserName}, $_->{Name}, $_->{VariableValue};	
}

