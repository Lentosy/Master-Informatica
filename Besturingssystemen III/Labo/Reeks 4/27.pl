use Win32::OLE 'in';
use Win32::OLE::Const 'Microsoft WMI Scripting ';

my $server = ".";
my $namespace = "root/cimv2";

my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");
my $service = $locator->ConnectServer($server, $namespace);


# test variables
my @classes = ("Win32_LocalTime", "Win32_DiskDrive", "Win32_Product");
my @instances = ("Win32_LocalTime=@",
                 "Win32_DiskDrive.DeviceID='\\\\.\\PHYSICALDRIVE0'",
                 "Win32_Product.IdentifyingNumber='{25A13826-8E4A-4FBF-AD2B-776447FE9646}',Name='WMI Tools',Version='1.50.1131.0001'");



for(my $i = 0; $i < 3; $i++){
    $class = $service->Get($classes[$i], wbemFlagUseAmendedQualifiers);
    $instance = $service->InstanceOf($instances[$i], wbemFlagUseAmendedQualifiers);
    print "---"  . $classes[$i] . " class ---\n";
    for (in $class->{Qualifiers_}){
        next if $_->{Name} eq "Description";
        printf "%-30s", $_->{Name};
        if(ref $_->{Value} eq "ARRAY"){
            print join ",", @{$_->{Value}};
         } else {
            print $_->{Value};
        }
        print "\n"; 
    }

        print "---"  . $classes[$i] . " instance ---\n";
    for (in $instance->{Qualifiers_}){
        next if $_->{Name} eq "Description";
        printf "%-30s", $_->{Name};
        if(ref $_->{Value} eq "ARRAY"){
            print join ",", @{$_->{Value}};
         } else {
            print $_->{Value};
        }
        print "\n"; 
    }
}