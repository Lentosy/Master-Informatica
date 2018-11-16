use Win32::OLE qw(in);
Win32::OLE->Option(Warn => 3);

my $IRQNumber = $ARGV[0] or die "No IRQNumber specified";

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
my $service = $locator->ConnectServer('.', 'root/cimv2');




my $Win32_NetworkAdapter_Associations = $service->AssociatorsOf("Win32_IRQResource.IRQNumber=$IRQNumber", undef,'Win32_NetworkAdapter');
print $Win32_NetworkAdapter_Associations->{Count};