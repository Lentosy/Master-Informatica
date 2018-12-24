
use Win32::OLE qw(in);
use Win32::OLE::Const 'Microsoft WMI Scripting';

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
my $wbemService = $locator->ConnectServer('.', 'root/cimv2'); 

# 1ste deel is letterlijk hetzelfde als oef 53

#kan blijkbaar nie aan msapps12 op windows 10 (eigen toestel)