use Win32::OLE qw(in);
Win32::OLE->Option(Warn => 3);

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
my $service = $locator->ConnectServer('.', 'root/cimv2');

my @Win32_Environment_Instances = in $service->InstancesOf('Win32_Environment');

printf "%-30s%-30s%-30s\n", 'Name', 'Value', 'Owner';
print  '-' x 90;
print "\n";
for (@Win32_Environment_Instances){
    printf "%-30s", $_->{Name};
    printf "%-25s", substr ($_->{VariableValue},0, 25);
    if(length $_->{VariableValue} > 25){
        printf "%-5s", '...';
    } else {
        printf "%-5s", '';
    }
    
    printf "%-30s\n", $_->{userName};

}