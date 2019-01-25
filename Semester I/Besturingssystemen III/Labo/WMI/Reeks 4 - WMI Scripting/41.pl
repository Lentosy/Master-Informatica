use Win32::OLE 'in';
use Win32::OLE::Const 'Microsoft WMI Scripting';


my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");
my $wbemService = $locator->ConnectServer(".", "root/cimv2");


my @instances = in $wbemService->ExecQuery("select * from Win32_Process where name = 'notepad.exe'");

for my $instance (@instances){
    $returnvalue = $instance->Terminate();
    printf "%s\n", $returnvalue;
}