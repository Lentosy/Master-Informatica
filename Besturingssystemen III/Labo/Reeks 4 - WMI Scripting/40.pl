use Win32::OLE 'in';
use Win32::OLE::Const 'Microsoft WMI Scripting';


my $classname = $ARGV[0];

my $server = ".";
my $namespace = "root/cimv2";

my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");
my $wbemService = $locator->ConnectServer($server, $namespace);


my @classes = ($classname);

for my $classname (@classes){
    my $class = $wbemService->Get($classname, wbemFlagUseAmendedQualifiers);

    printf "Methods for %s:\n", $classname;
    for my $method (in $class->{Methods_}){
        printf "\t* %s ", $method->{Name};

        if( $method->{Qualifiers_}->Item("Static") && $method->{Qualifiers_}->Item("Static")->{Value}){
            print "[ static ]";
        }
        
        print "\n";
        
        
        
        if($method->{InParameters}){
            for $inparam(in $method->{InParameters}->{Properties_}){
                PrintParam($inparam, 1);    
            }
        }

        if($method->{Outparameters}){
            for $outparam(in $method->{Outparameters}->{Properties_}){
                PrintParam($outparam, 0);    
            }
        }

    }
}


sub PrintParam {
    (my $param, my $in) = @_;

    print "\t\t";
    $in ? print "-> " 
        : print "<- ";
    

    if($param->{Qualifiers_}->Item("Optional") && $param->{Qualifiers_}->Item("Optional")->{Value}){
        printf "[%-18s]\n", $param->{Name}, "]";
    } else {
        printf "%-20s\n", $param->{Name};
    }


}