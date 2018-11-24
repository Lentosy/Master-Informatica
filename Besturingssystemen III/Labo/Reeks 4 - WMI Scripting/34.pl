use Win32::OLE qw(in);
use Win32::OLE::Const 'Microsoft WMI Scripting';

my $classname = $ARGV[0] or die;

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
my $service = $locator->ConnectServer('.', 'root/cimv2');

my $class = $service->Get($classname, wbemFlagUseAmendedQualifiers);

for my $property (in $class->{Properties_}){
    next unless PropertyHasValueMap($property);
    print "$property->{Name}\n"; #NIET doen lol, description tekst is veel te veel . $property->{Qualifiers_}->Item('Description')->{Value};
    my %map;
    @map{@{$property->{Qualifiers_}->Item('ValueMap')->{Value}}} = @{$property->{Qualifiers_}->Item('Values')->{Value}};
    for my $key (sort {$a <=> $b} keys %map){
        print "\t$key => $map{$key}\n";
    }
}

sub PropertyHasValueMap {
    my $property = shift;
    return $property->{Qualifiers_}->Item('ValueMap');
}
