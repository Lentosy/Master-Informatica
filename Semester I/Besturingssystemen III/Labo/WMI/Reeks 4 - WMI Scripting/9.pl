use Win32::OLE qw(in);
Win32::OLE->Option(Warn => 3);

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
my $service = $locator->ConnectServer('.', 'root/cimv2');

print scalar in $service->AssociatorsOf('Win32_Directory', undef, undef, undef, undef, undef, 1); 