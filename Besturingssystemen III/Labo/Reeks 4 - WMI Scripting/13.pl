use Win32::OLE qw(in);
use Win32::OLE::Const;
use Data::Dumper;
Win32::OLE->Option(Warn => 3);



my $classname = $ARGV[0] or die 'No classname specified';

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
my $service = $locator->ConnectServer('.', 'root/cimv2');

my $class = $service->Get($classname);

$constants =  Win32::OLE::Const->Load($locator);
%cimtypes;
for my $key (%$constants){
    if($key =~ /Cimtype/){
        my $val = $constants->{$key};
        $key =~ s/wbemCimtype//g;
        $cimtypes{$val} = $key;
    }
}

printf "%-30s%-30s%-30s\n", 'Name', 'CIMType', 'IsArray';
print '-' x 90 . "\n";

for(in $class->{SystemProperties_}, $class->{Properties_}){
    printf "%-30s", $_->{Name};
    printf "%-30s", $cimtypes{$_->{CIMType}};
    printf "%-30s", $_->{IsArray} ? 'Yes' : 'No';
    print "\n";
}