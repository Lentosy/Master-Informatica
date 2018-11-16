use Win32::OLE qw(in);
use Win32::OLE::Const 'Microsoft WMI Scripting';
use Data::Dumper;

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
my $service = $locator->ConnectServer('.', 'root/cimv2');

