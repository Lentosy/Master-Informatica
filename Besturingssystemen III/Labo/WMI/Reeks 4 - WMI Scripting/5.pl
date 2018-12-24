use Win32::OLE qw(in);
Win32::OLE->Option(Warn => 3);

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
my $service = $locator->ConnectServer('.', 'root/cimv2');


my $Win32_OperatingSystem = $service->Get('Win32_OperatingSystem=@');
print $Win32_OperatingSystem->{ServicePackMajorVersion};
print $Win32_OperatingSystem->{ServicePackMinorVersion};

print "\nCaption: ",$Win32_OperatingSystem->{Caption};
print "\nversion: ",$Win32_OperatingSystem->{Version},
print "\nOSArchitecture: ",$Win32_OperatingSystem->{OSArchitecture};