use Win32::OLE::Const 'Microsoft WMI Scripting ';


my $server = ".";
my $namespace = "root/cimv2";

my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");
my $service = $locator->ConnectServer($server, $namespace);

@ARGV = ("Win32_LocalTime", "Win32_DiskDrive", "Win32_CurrentTime", "Win32_WMISetting", "CIM_LogicalDevice");


for(@ARGV){
    my $class = $service->Get($_, wbemFlagUseAmendedQualifiers);
    if ($class->{Qualifiers_}->Item("Singleton") && $class->{Qualifiers_}->Item("Singleton")->{Value}){
        print "$_ is singleton";
    }else{
        print "$_ is geen singleton";
    }

    print "\n";
    
}