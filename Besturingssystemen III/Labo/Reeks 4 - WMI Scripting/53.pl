use Win32::OLE qw(in);
use Win32::OLE::Const 'Microsoft WMI Scripting';


my $notificationquery = "SELECT * FROM Win32_ProcessTrace";

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
my $wbemService = $locator->ConnectServer('.', 'root/cimv2'); 

my $eventnotification = $wbemService->ExecNotificationQuery($notificationquery);

local $| = 1;

while(1){
    my $event = $eventnotification->NextEvent();
    printf "%s %s (%d)\n", $event->{Path_}->{Class} =~ /Win32_Process(.*)Trace/g, $event->{ProcessName}, $event->{ProcessID};
}

# andere manier is zo slecht voor processen
