use Win32::OLE 'in';
use Win32::OLE::Const 'Microsoft WMI Scripting';

if (scalar @ARGV != 1){
    printf STDERR "Expected only one argument, the name of a service\n";
    exit 1;
}

my $server = ".";
my $namespace = "root/cimv2";

my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");
my $wbemService = $locator->ConnectServer($server, $namespace);

#OracleXETNSListener

#methoden: StartService(geen invoerparameters en geen uitvoerparameters behalve returnValue) 
#       en StopService(geen invoerparameters en geen uitvoerparameters behalve returnValue) 


my $Win32_Service = $wbemService->Get("Win32_Service", wbemFlagUseAmendedQualifiers);

my $servicename = $ARGV[0];
(my $instance) = in $wbemService->ExecQuery("select * from win32_service where Name = '$servicename'");

#@status = @{$Win32_Service->{Properties_}->Item("Status")->{Qualifiers_}->Item("ValueMap")->{Value}};
#print join "\n", @status;
#print $instance->{Status};

%returnvalues = getReturnValues($Win32_Service->{Methods_}->Item("StopService"));


if ($instance->{Status} eq "OK"){
    print "Service $servicename is already running. Shutting down $servicename...\n";
    my $returnvalue = $instance->StopService();
    print $returnvalues{$returnvalue};
} else {
    print "Service $service is not running. Starting $servicename...\n";
    my $returnvalue = $instance->StartService();
    print $returnvalues{$returnvalue};
}


sub getReturnValues {
    my $method = shift;
    %r = ();
    @r{@{$method->Qualifiers_(ValueMap)->{Value}}} = @{$method->Qualifiers_(Values)->{Value}};
    return %r;
}