use Win32::OLE qw(in);
use Win32::OLE::Const 'Microsoft WMI Scripting';



my $query = "SELECT * 
             FROM __InstanceModificationEvent WITHIN 5
             WHERE TargetInstance ISA 'Win32_service'";

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
my $wbemService = $locator->ConnectServer('.', 'root/cimv2'); 



my $eventNotification = $wbemService->ExecNotificationQuery($query);
local $| = 1;
while(1){
    my $event = $eventNotification->NextEvent(5000);
    $event 
        ? printf "(%s) %s -> %s\n", $event->{TargetInstance}->{DisplayName}, $event->{PreviousInstance}->{State}, $event->{TargetInstance}->{State}
        : print ".\n";
}