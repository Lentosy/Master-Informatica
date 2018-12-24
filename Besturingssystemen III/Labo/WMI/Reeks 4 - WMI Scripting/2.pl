use Win32::OLE;
Win32::OLE->Option(Warn => 3);

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');

my $servicelocal = $locator->ConnectServer('localhost', 'root/cimv2');
#my $serviceother = $locator->ConnectServer('192.168.1.41', 'root/cimv2');
print Win32::OLE->QueryObjectType($servicelocal);
print "\n";
#print Win32::OLE->QueryObjectType($serviceother);