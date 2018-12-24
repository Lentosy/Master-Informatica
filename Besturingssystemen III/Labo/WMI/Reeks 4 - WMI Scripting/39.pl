use Win32::OLE 'in';
use Win32::OLE::Const 'Microsoft WMI Scripting';

my $server = ".";
my $namespace = "root/cimv2";

my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");
my $wbemService = $locator->ConnectServer($server, $namespace);

my @classes;
if(scalar @ARGV == 0){
    @classes = map { $_->{Path_}->{RelPath} } in $wbemService->ExecQuery("select * from meta_class");
} else {
    @classes = @ARGV;
}



for my $classname (@classes){
    my $class = $wbemService->Get($classname, wbemFlagUseAmendedQualifiers);

    if(in $class->{Methods_}){ # enkel klassen die methodes hebben zijn belangrijk
        print "\n\n$classname\n\n";
    }
    for my $method (in $class->{Methods_}){
        #todo, zorgen dat klassen die wel methodes hebben, maar geen valus in één van de methodes, niet geprint worden
        my @values;
        my @valuesmap;

        if(IsSet($method, "Values")){
            @values = in $method->{Qualifiers_}->{Values}->{Value};
        } else {
            next; # enkel methoden die Values hebben zijn belangrijk
        }

        if(IsSet($method, "ValueMap")){
            @valuesmap = in $method->{Qualifiers_}->{ValueMap}->{Value};
        } else {
            @valuesmap = (0 .. scalar @values);
        }

        printf "\t%s\n", $method->{Name};
        for (my $i = 0; $i < scalar @values; $i++){
            printf "\t\t%d => %s\n", $valuesmap[$i], $values[$i];
        }
    }


}



sub IsSet {
    (my $class, my $property) = @_;
    return $class->{Qualifiers_}->Item($property) && $class->{Qualifiers_}->Item($property)->{Value};
}