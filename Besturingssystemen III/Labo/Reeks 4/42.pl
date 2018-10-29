use Win32::OLE 'in';
use Win32::OLE::Const 'Microsoft WMI Scripting';


my @processnames = @ARGV;

my $server = ".";
my $namespace = "root/cimv2";

my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");
my $service = $locator->ConnectServer($server, $namespace);


my $Win32_Process = $service->Get("Win32_Process", wbemFlagUseAmendedQualifiers);

my %returnvaluesCreate = getReturnValues($Win32_Process->{Methods_}->Item("Create"));
my %returnvaluesTerminate = getReturnValues($Win32_Process->{Methods_}->Item("Terminate"));
my @handles = ();


for my $processname (@processnames){
    #initialiseren invoerparameters
    my $inParameters = $Win32_Process->{Methods_}->{"Create"}->{InParameters};
    $inParameters->{Properties_}->Item("CommandLine")->{Value} = $processname;

    my $outParameters = $Win32_Process->ExecMethod_("Create", $inParameters);
    $returnvalue = $outParameters->{ReturnValue};

    if($returnvalue eq "0"){
        printf "%s,  created process $processname with handle %s\n", $returnvaluesCreate{$returnvalue}, $outParameters->{ProcessId};
        push @handles, $outParameters->{ProcessId};
    } else {
        printf "%s\n", $returnvaluesCreate{$returnvalue};
    }
}

print "Currently holding following handles [";
print join ", ", @handles;
print "]\n";
print "Pauze\n";
sleep 5;
print "Terug verder\n";
# processen terug killen


for my $handle (@handles){
    (my $instance) = in $service->ExecQuery("select * from win32_process where ProcessId='$handle'");
    my $returnvalue = $instance->Terminate();
    if($returnvalue eq "0"){
        printf "Termination of process with handle $handle succesful\n";
    } else {
        printf "%s\n", $returnvaluesTerminate{$returnvalue};
    }
}

sub getReturnValues {
    my $method = shift;
    my %values = ();
    @values{@{$method->Qualifiers_(ValueMap)->{Value}}} = @{$method->Qualifiers_(Values)->{Value}};
    return %values;
}