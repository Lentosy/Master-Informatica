use Win32::OLE 'in';
use Win32::OLE::Const 'Microsoft WMI Scripting ';

my $service =  Win32::OLE->GetObject("winmgmts://127.0.0.1/root/cimv2");

my $classes = $service->SubclassesOf(undef,wbemFlagUseAmendedQualifiers);

my %providers = ();

for (in $classes) {
    if($_->{Qualifiers_}->Item("Provider")){
        $providers{$_->{Qualifiers_}->Item("Provider")->{Value}}++;
    } else {
        $providers{"Ontbreekt"}++;
    }
}

for(sort { $providers{$b} <=> $providers{$a} } keys %providers){
    printf "%40s: %s\n", $_ , $providers{$_};
}