use strict;
use warnings;

use Win32::OLE qw(in);


my $locator = Win32::OLE->new("WbemScripting.SWbemLocator");
my $service = $locator->ConnectServer("127.0.0.1", "root/CIMV2");




my @networkAdapters = in $service->InstancesOf("Win32_NetworkAdapter"); 

print scalar @networkAdapters; ## aantal instances
print " instances of Win32_NetworkAdapter found\n";


print "Key values are:\n";
for(@networkAdapters){
	print "\t $_->{DeviceId} \n";
}