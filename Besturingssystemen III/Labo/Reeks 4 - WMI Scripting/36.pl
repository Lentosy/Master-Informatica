use Win32::OLE qw(in);
use Win32::OLE::Const 'Microsoft WMI Scripting';
use Data::Dumper;

my $classname = $ARGV[0] or die 'No class specified';

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
my $service = $locator->ConnectServer('.', 'root/cimv2');


my $class = $service->Get($classname, wbemFlagUseAmendedQualifiers);

for my $property (in $class->{Properties_}){
    next unless HasOnlyValues($property);
    print "$property->{Name}\n";
    @values = @{$property->{Qualifiers_}->Item('Values')->{Value}};
    for(0 .. $#values){
        print "\t$_ => $values[$_]\n";
    }
    print "\n";
}


# returns true if the property has a values qualifer but not a valuesmap qualifier
sub HasOnlyValues {
    my $property = shift;
    return $property->{Qualifiers_}->Item('Values') && ! $property->{Qualifiers_}->Item('ValueMap') 
}
