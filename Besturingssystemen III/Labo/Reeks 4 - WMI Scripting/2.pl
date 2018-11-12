use Win32::OLE;


my $locator = Win32::OLE->new("WbemScripting.SWbemLocator");
my $service = $locator->ConnectServer("TODO","root/CIMV2"); # lokale context

print Win32::OLE->QueryObjectType($service);

my $service = $locator->ConnectServer("TODO","root/CIMV2"); # lokale context

print Win32::OLE->QueryObjectType($service);

print Win32::OLE->LastError();