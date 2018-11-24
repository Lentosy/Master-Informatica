use Win32::OLE;
use Win32::OLE::Const 'Microsoft WMI Scripting';


my $server = ".";
my $namespace = "root/cimv2";

my $wbemService = Win32::OLE->GetObject("winmgmts://$server/$namespace");

my $Win32_Share = $wbemService->Get("Win32_Share", wbemFlagUseAmendedQualifiers);

my $inParameters = $Win32_Share->{Methods_}->Item("Create")->{InParameters};

$inParameters->{Description} = "Een stukje tekst";
$inParameters->{Name} = "Testshare";
$inParameters->{Path} = 'F:\TempBox';
$inParameters->{Type} = 0;

#$return = $Win32_Share->ExecMethod_("Create", $inParameters);
print $return->{ReturnValue} ," ( geen interpretatie )\n";

 
# share terug verwijderen:
#  in CMD of Powershell (ALS ADMINISTRATOR)
#   net share Testshare /delete
