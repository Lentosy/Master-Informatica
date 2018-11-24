use Win32::OLE qw(in);
use Win32::OLE::Const 'Microsoft WMI Scripting';

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
my $service = $locator->ConnectServer('.', 'root/cimv2');


my @classes = in $service->ExecQuery('SELECT * FROM META_CLASS');

for my $class (@classes){
    next if scalar $class->{Properties_}->{Count} <= 1;  # classes with zero or one attributes cannot have a composite key
    next unless isSet($class->{Qualifiers_}, 'Association');
    
    
    my @keys;
    for(in $class->{Properties_}){
        if(isSet($_->{Qualifiers_}, 'key')){
            my $cimtype = $_->{Qualifiers_}->Item('CIMType')->{Value};
            push @keys, $_->{Name} . "($cimtype)";
        }
    }

    if(scalar @keys > 1){
        printf "%-42s (%d):",  $class->{Path_}->{Class}, scalar @keys;
        print join "|", @keys;
        print "\n";
    }
}

sub isSet {
    (my $x, my $y) = @_;
    return $x->Item($y) && $x->Item($y)->{Value};
}