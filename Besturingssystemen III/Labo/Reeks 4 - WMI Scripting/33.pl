use Win32::OLE qw(in);
use Win32::OLE::Const 'Microsoft WMI Scripting';

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
my $service = $locator->ConnectServer('.', 'root/cimv2');

my @classes = in $service->ExecQuery("SELECT * FROM META_CLASS");

for my $class (@classes) {
    next unless $class->{Qualifiers_}->Item('Association');
    next if $class->{Qualifiers_}->Item('Abstract');
    my @keyvalues = ();
    for my $attribute (in $class->{Properties_}){
        if($attribute->{Qualifiers_}->Item('Key') && $attribute->{Qualifiers_}->Item('Key')->{Value}){
            push @keyvalues, $attribute->{Qualifiers_}->{CIMType}->{Value};
        }
    }
    if(scalar @keyvalues == 2 && $keyvalues[0] eq $keyvalues[1]){
        printf "%-40s => %s\n", $keyvalues[0], $class->{Path_}->{Class};
    }


}
