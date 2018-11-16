use strict;
use warnings;

use Win32::OLE qw(in);
use Win32::OLE::Variant;

if(scalar @ARGV == 0){
	print STDERR "No arguments\n";
	exit 1;
}

my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");
my $service = $locator->ConnectServer("127.0.0.1", "root/CIMV2");


for(@ARGV){
	my $class = $service->get($_);
	if(!$class){
		print STDERR "$_ is not a valid class\n";
		next;
	}

	for(keys %{$class->{Path_}}){
		print "$_\n => $class->{Path_}->{$_}\n";
	}


}

# voor Win32_OperatingSystem geeft het IsSingleton = 0