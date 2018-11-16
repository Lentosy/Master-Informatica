use Win32::OLE qw(in);
use Win32::OLE::Variant;
Win32::OLE->Option(Warn => 3);

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
my $service = $locator->ConnectServer('.', 'root/cimv2');
my $datetime = Win32::OLE->new('WbemScripting.SWbemDateTime');

(my $Win32_OperatingSystem) = in $service->InstancesOf('Win32_OperatingSystem');

my @properties = ();

for(@ARGV){
    if($Win32_OperatingSystem->{Properties_}->Item($_) && $Win32_OperatingSystem->{Properties_}->Item($_)->{Value}){
        push @properties, $Win32_OperatingSystem->{Properties_}->Item($_); 
    }
}

$longestVarName = 0;
for (@properties){
    $longestVarName = length $_->{Name} if length $_->{Name} > $longestVarName;
}

$longestVarName += 2;

printf "%-${longestVarName}s%-30s\n", 'Name', 'Value';
print '-' x ($longestVarName + 30) . "\n";
for (@properties){
    printf "%-${longestVarName}s", $_->{Name};
    if($_->{CIMType} == 101){
        $datetime->{Value} = $_->{Value};
        printf "%-30s", $datetime->GetVarDate();
    } else {
        printf "%-30s", $_->{Value};
    }

    print "\n";
}