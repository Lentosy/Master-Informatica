use Win32::OLE qw(in);
Win32::OLE->Option(Warn => 3);

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
my $service = $locator->ConnectServer('.', 'root/cimv2');

#$count = scalar (in $service->InstancesOf('Win32_NetworkAdapter'));
$count = scalar (in $service->ExecQuery('SELECT * FROM Win32_NetworkAdapter'));

print $count;