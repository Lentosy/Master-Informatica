use strict;
use warnings;
use Win32::OLE qw(in);
use Win32::OLE::Variant;

#Select * from Win32_NTLogEvent  Where Logfile = 'System' and SourceName='EventLog' 
#      and ( EventCode = '6005' or EventCode = '6006' )



my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");
my $datetime = Win32::OLE->new("WbemScripting.SWbemDateTime");
my $service = $locator->ConnectServer("127.0.0.1", "root/CIMV2");

my @instances = in $service->ExecQuery("Select * from Win32_NTLogEvent  Where Logfile = 'System' and SourceName='EventLog' 
      and ( EventCode = '6005' or EventCode='6006')");


for(@instances){
	$datetime->{Value} = $_->{TimeWritten};
	if($_->{EventCode} == 6005){
		print "Computer opgestart op: ";
	} elsif ($_->{EventCode} == 6006) {
		print "Computer afgesloten op: ";
	}
	print  $datetime->GetVarDate;
	print "\n";
}