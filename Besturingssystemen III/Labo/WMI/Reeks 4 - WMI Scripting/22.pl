use strict;
use warnings;
use Win32::OLE 'in';



#associators of {Win32_Service.Name="Cryptsvc"}
#where resultclass=Win32_Service
#resultrole=Antecedent

my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");
my $service = $locator->ConnectServer("127.0.0.1", "root/CIMV2");

my @instances = in $service->ExecQuery("select *
										from Win32_Service
										where State = 'Running'");

for(@instances){
	printf "%s (%s) : StartMode = %s", $_->{Name}, $_->{Caption}, $_->{StartMode};

	my @associators = in $service->AssociatorsOf("Win32_Service.Name='$_->{Name}'", undef, "Win32_Service", "Antecedent");
				

	#AssociatorsOf("Win32_IRQResource.IRQNumber=$IRQNumber", undef, "Win32_NetworkAdapter");
	print "\n\tFirst order dependencies => ";
	for my $assoc (@associators){
		print $assoc->{Name} . ", ";
	}
	print "\n\n\n";
}


#StartMode, Name, Caption, Description, PathName