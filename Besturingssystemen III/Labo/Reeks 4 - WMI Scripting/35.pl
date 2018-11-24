use Win32::OLE qw(in);
use Win32::OLE::Const 'Microsoft WMI Scripting';
use Data::Dumper;


my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
my $service = $locator->ConnectServer('.', 'root/cimv2');

my @instances = in $service->ExecQuery("SELECT * FROM Win32_NetworkAdapter WHERE NetConnectionStatus >=0");
my $Win32_NetworkAdapter = $service->Get('Win32_NetworkAdapter', wbemFlagUseAmendedQualifiers);

# IP- DHCP en DNS => VIA Win32_NetworkAdapterConfiguration 

sub GetValueMapping {
    my $property = shift;
    my %hash;
    @hash{@{$property->{Qualifiers_}->Item('ValueMap')->{Value}}} = @{$property->{Qualifiers_}->Item('Values')->{Value}};
    return %hash;
}

my %availability = GetValueMapping($Win32_NetworkAdapter->{Properties_}->Item('Availability'));
my %netconnectionstatus = GetValueMapping($Win32_NetworkAdapter->{Properties_}->Item('NetConnectionStatus'));

my $width = 20; # for formatting

for my $instance (@instances){
    print "-" x 100;
    print "\n";

    printf "%-${width}s:%-${width}s\n", 'Name'                , $instance->{Name};
    printf "%-${width}s:%-${width}s\n", 'Adaptertype'         , $instance->{AdapterType};
    printf "%-${width}s:%-${width}s\n", 'NetConnectionStatus' , $netconnectionstatus{$instance->{NetConnectionStatus}};
    printf "%-${width}s:%-${width}s\n", 'Availability'        , $availability{$instance->{Availability}};
    printf "%-${width}s:%-${width}s\n", 'MACAddress'          , $instance->{MACAddress};
    printf "%-${width}s:%-${width}s\n", 'ServiceName'         , $instance->{ServiceName};

    my @associators = in $service->ExecQuery("ASSOCIATORS OF {Win32_NetworkAdapter=$instance->{Index}} WHERE ASSOCCLASS=Win32_AllocatedResource");


    # eigenlijk geen good practice om dit te doen, als één van de properties een valuesmap nodig heeft om numerieke waarde te vervangen, moet ge die toch apart nemen
    @info = ( #Class, DisplayProperty (for console), Property to display from class
        ['Win32_IRQResource', 'IRQNumber', 'IRQNumber'],
        ['Win32_DeviceMemoryAddress', 'Memory Address', 'Caption'],
        ['Win32_PortResource', 'I/O Port', 'Caption'],
        ['Win32_DMAChannel', 'DMA Channel', 'DMAChannel']
    );
    for my $associator (@associators){
        for my $i (@info){
            printf "%-${width}s:%-${width}s\n", $i->[1], $associator->{$i->[2]} if $associator->{Path_}->{Class} eq $i->[0];
        }
    }

    (my $configuration) = in $service->ExecQuery("ASSOCIATORS OF {Win32_NetworkAdapter=$instance->{Index}} WHERE RESULTCLASS=Win32_NetworkAdapterConfiguration");
    
    printf "%-${width}s:%-${width}s\n", 'DHCPEnabled' , $configuration->{DHCPEnabled} ? 'Yes' : 'No';
    printf "%-${width}s:%-${width}s\n", 'DHCPServer'  , $configuration->{DHCPServer};

    #todo, gwn nog easy attributen ophalen, te saai


    print "\n"
}


sub TrimText {
    my $text = shift;
   # if(length $text > $width - 5){
    #    return substr($text,0, $width - 5) . '...';
    #}
    return $text;
}