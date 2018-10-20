use strict;
use warnings;

use Win32::OLE qw(in);


my $IRQNumber = $ARGV[0];

if(!$IRQNumber){
	print STDERR "No IRQNumber specified\n";
	exit 1;
}

if($IRQNumber =~ /[^\d]/g){ # something else other than a number is in the argument; 
	print STDERR "The given IRQNumber does not consist of only numbers\n";
	exit 1;
}

my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");
my $service = $locator->ConnectServer("127.0.0.1", "root/CIMV2");

#Win32_IRQResource.IRQNumber=491
print "Attempting connection to path Win32_IRQResource.IRQNumber=$IRQNumber\n";
my $CIM_IRQ_INSTANCE  = $service->Get("Win32_IRQResource.IRQNumber=$IRQNumber");
if(!$CIM_IRQ_INSTANCE){
	print STDERR "The CIM_IRQ instance for IRQNumber = $IRQNumber could not be found\n";
	exit 1;
}
print "Connection succesful\n";

my @network_associations = in $service->AssociatorsOf("Win32_IRQResource.IRQNumber=$IRQNumber", undef, "Win32_NetworkAdapter");


print "Networkdescriptions of associated networkadapters are: \n";
for(@network_associations){
	my $network_instance = $service->Get("$_->{Path_}->{RelPath}");
	print "\t" . $network_instance->{Description} . "\n";
}