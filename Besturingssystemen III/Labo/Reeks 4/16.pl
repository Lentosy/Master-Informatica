use strict;
use warnings;

use Win32::OLE qw(in);

if(scalar @ARGV == 0){
	print STDERR "No arguments\n";
	exit 1;
}

my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");
my $service = $locator->ConnectServer("127.0.0.1", "root/CIMV2");
my $instance = $service->Get("Win32_OperatingSystem=@");

printf "Relative path = %s\n", $instance->{Path_}->{RelPath}; 
for(@ARGV){
	if($instance->{$_}){
		printf "%s\n", $instance->{$_};
	} else {
		printf "No attribute $_ found\n";
	}
}
