use Win32::OLE 'in';
use Win32::OLE::Const 'Microsoft WMI Scripting';


my $server = ".";
my $namespace = "root/cimv2";

my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");
my $wbemService = $locator->ConnectServer($server, $namespace);

my @classes = in $wbemService->ExecQuery("select * from meta_class");
my %output = ();
#%output = (
#  class1 => {
#               'method1' => [privilege1, privilege2],
#               'method2' => [privilege2, privilege4]
#            }
#  class3 => {
#               'method4' => [privilege1],
#            }
#
#
#)

for my $class (@classes){
    my $classname = $class->{Path_}->{Class};
    for my $method (in $class->{Methods_}){
        next if (!isSet($method->{Qualifiers_}, "Privileges"));
        my @privileges = in $method->{Qualifiers_}->Item("Privileges")->{Value}; 
        $output{$classname}->{$method->{Name}} = \@privileges;
    }
}

for my $class (keys %output){
    print $class . "\n";
    for my $method(keys %{$output{$class}}){
        print "\t $method:  [";
        print join ",", map { $_=~/Se([A-Za-z]*)Privilege/;} @{$output{$class}->{$method}}; # elke privilege overlopen, en uitprinten zonder Se of Privilege
        print "]\n";
    }
}

sub isSet {
    (my $x, my $prop) = @_;
    return ($x->{$prop} && $x->{$prop}->{Value})
}