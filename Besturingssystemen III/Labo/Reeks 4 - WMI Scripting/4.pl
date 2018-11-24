use Win32::OLE qw(in);
Win32::OLE->Option(Warn => 3);

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
my $service = $locator->ConnectServer('.', 'root/cimv2');

my $Win32_Directory = $service->Get('Win32_Directory.Name=\'C:\\\'');
print $Win32_Directory->{FileType};