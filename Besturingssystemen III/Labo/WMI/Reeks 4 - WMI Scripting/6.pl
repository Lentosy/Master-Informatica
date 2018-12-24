use Win32::OLE qw(in);
Win32::OLE->Option(Warn => 3);

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
my $service = $locator->ConnectServer('.', 'root/cimv2');


#(my $Win32_OperatingSystem) = in $service->InstancesOf('Win32_OperatingSystem');
(my $Win32_OperatingSystem) = in $service->ExecQuery('SELECT * FROM Win32_OperatingSystem');
print $Win32_OperatingSystem->{ServicePackMajorVersion};
print $Win32_OperatingSystem->{ServicePackMinorVersion};

print "\nCaption: ",$Win32_OperatingSystem->{Caption};
print "\nversion: ",$Win32_OperatingSystem->{Version},
print "\nOSArchitecture: ",$Win32_OperatingSystem->{OSArchitecture};