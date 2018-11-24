use Win32::OLE qw(in);
use Win32::OLE::Variant;
Win32::OLE->Option(Warn => 3);

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
my $service = $locator->ConnectServer('.', 'root/cimv2');
my $datetime = Win32::OLE->new('WbemScripting.SWbemDateTime');

(my $Win32_OperatingSystem) = in $service->InstancesOf('Win32_OperatingSystem');

$longestVarName = 0;
for (in $Win32_OperatingSystem->{Properties_}, $Win32_OperatingSystem->{SystemProperties_}){
    $longestVarName = length $_->{Name} if length $_->{Name} > $longestVarName;
}

$longestVarName += 2;

printf "%-${longestVarName}s%-30s\n", 'Name', 'Value';
print '-' x 90 . "\n";
for (in $Win32_OperatingSystem->{Properties_}, $Win32_OperatingSystem->{SystemProperties_}){
    printf "%-${longestVarName}s", $_->{Name};
    if($_->{CIMType} == 101){
        $datetime->{Value} = $_->{Value};
        printf "%-30s", $datetime->GetVarDate();
    } else {
        printf "%-30s", $_->{Value};
    }

    print "\n";
}