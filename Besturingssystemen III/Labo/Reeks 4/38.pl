use Win32::OLE 'in';
use Win32::OLE::Const 'Microsoft WMI Scripting';


if(scalar @ARGV != 1){
    print STDERR "Expected one argument, the name of a WMI class\n";
    exit 1;
}

my $server = ".";
my $namespace = "root/cimv2";

my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");
my $wbemService = $locator->ConnectServer($server, $namespace);

my $classname = $ARGV[0];

my $class = $wbemService->Get($classname, wbemFlagUseAmendedQualifiers);

for $method_ (in $class->{Methods_}){
    my $methodname = $method_->{Name};
    printf "%s\n", $methodname;

    if($method_->{InParameters}){
        print "  Input parameters:\n";
        for my $parameter (in $method_->{InParameters}->{Properties_}){
            PrintParameter($parameter);
        }
    }

    if($method_->{OutParameters}){
        print "  Output parameters:\n";
        for my $parameter (in $method_->{OutParameters}->{Properties_}){
            PrintParameter($parameter);
        }
    }
}

sub PrintParameter {
    my $parameter = shift;
    printf "    %s = %s\n", $parameter->{Name}, $parameter->{Value} ? $parameter->{Value} : "<empty>";
}