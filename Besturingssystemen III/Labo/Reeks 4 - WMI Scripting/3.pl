use Win32::OLE qw(in);
Win32::OLE->Option(Warn => 3);

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
my $service = $locator->ConnectServer('.', 'root/cimv2');

my $Win32_NetworkAdapter = $service->Get('Win32_NetworkAdapter');

print Win32::OLE->QueryObjectType($Win32_NetworkAdapter);

(my $Win32_NetworkAdapter_Instance) = in $service->InstancesOf('Win32_NetworkAdapter');
printf "Name of Win32_NetworkAdapter_Instance = %s\n", $Win32_NetworkAdapter_Instance->{Name};