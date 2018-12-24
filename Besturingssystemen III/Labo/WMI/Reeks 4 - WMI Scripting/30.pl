use Win32::OLE 'in';
use Win32::OLE::Const 'Microsoft WMI Scripting';

#CreateBy = true geeft aan dat er instanties kunnen aangemaakt worden

my $server = ".";
my $namespace = "root/cimv2";

my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");
my $service = $locator->ConnectServer($server, $namespace);


for my $class (in $service->SubClassesOf(undef, wbemFlagUseAmendedQualifiers)){
    if(IsSet($class, "CreateBy")){
        $method = $class->{Qualifiers_}->Item("CreateBy")->{Value};
        print $class->{Path_}->{Relpath}. " : " . $method . "\n";
    }
}

sub IsSet {
    (my $class, my $property) = @_;
    return $class->{Qualifiers_}->Item($property) && $class->{Qualifiers_}->Item($property)->{Value};
}