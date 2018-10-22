use Win32::OLE::Const 'Microsoft WMI Scripting';
use Win32::OLE 'in';

my $server = ".";
my $namespace = "root/cimv2";

my $service = Win32::OLE->GetObject("winmgmts://$server/$namespace");

my @classes = in $service->SubClassesOf(undef, wbemFlagUseAmendedQualifiers);

%categories = (
    "abstract" => 0,
    "association" => 0,
    "dynamic" => 0,
    "singleton" => 0
);


for (@classes){
    for my $category (keys %categories){
        $categories{$category}++ if (IsSet($_, $category));
    }
}

my $totalclasses = scalar @classes;

for(keys %categories){
    printf "%15s: %5d (+) %5d (-)\n",$_, $categories{$_}, $totalclasses - $categories{$_};
}

sub IsSet {
    (my $class, my $property) = @_;
    return $class->{Qualifiers_}->Item($property) && $class->{Qualifiers_}->Item($property)->{Value};
}