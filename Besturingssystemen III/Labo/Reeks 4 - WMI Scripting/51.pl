use Win32::OLE qw(in);
use Win32::OLE::Const 'Microsoft WMI Scripting';
Win32::OLE->Option(Warn => 3);

my @classes = @ARGV or my @classes = qw(Win32_PerfFormattedData_PerfOS_System    Win32_PerfFormattedData_PerfOS_Processor 
               Win32_PerfFormattedData_PerfDisk_LogicalDisk   Win32_PerfFormattedData_PerfOS_Memory );

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
my $wbemService = $locator->ConnectServer('.', 'root/cimv2'); 
my $refresher = Win32::OLE->new('WbemScripting.SWbemRefresher');


my @instances = ();
for my $classname (@classes){
    push @instances, in $wbemService->InstancesOf($classname);
}

for my $instance (@instances){
    $refresher->Add($wbemService, $instance->{Path_}->{RelPath});
}

$refresher->{AutoReconnect} = 1;

StartRefresh();

sub StartRefresh {
    local $| = 1; # buffering disablen
    while(1){
        sleep(5);
        $refresher->Refresh();
        PrintData();
    }
}

sub PrintData {
    for (in $refresher){
        printf "*****   %s   *****\n", $_->{Object}->{Path_}->{RelPath};
        for $property (in $_->{Object}->{Properties_}){
            next unless defined $property->{Value};
            printf "%-50s%-50s\n", $property->{Name}, $property->{Value};
        }
    }
}




