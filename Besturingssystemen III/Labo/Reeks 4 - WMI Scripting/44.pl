use Win32::OLE;
use Win32::OLE::Const 'Microsoft WMI Scripting';

my %rootKey = ( HKEY_CLASSES_ROOT   => 0x80000000
              , HKEY_CURRENT_USER   => 0x80000001
              , HKEY_LOCAL_MACHINE  => 0x80000002
              , HKEY_USERS          => 0x80000003
              , HKEY_CURRENT_CONFIG => 0x80000005
              , HKEY_DYN_DATA       => 0x80000006 );


my $server = ".";
my $namespace = "root/cimv2";

my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");
my $wbemService = $locator->ConnectServer($server, $namespace);

my $StdRegProv = $wbemService->Get("StdRegProv");

printTree("HKEY_CURRENT_CONFIG");

#
#uint32 EnumKey(
#[in] uint32 hDefKey,
#[in] string sSubKeyName,
#[out] string sNames
#);
#
#The EnumKey method enumerates the subkeys for the given path. 
#
#hDefKey
#Optional parameter that specifies the tree that contains the sSubKeyName path. The default value is HKEY_LOCAL_MACHINE (0x80000002). The following trees are defined in Winreg.h: 
#HKEY_CLASSES_ROOT (0x80000000) 
#HKEY_CURRENT_USER (0x80000001) 
#HKEY_LOCAL_MACHINE (0x80000002) 
#HKEY_USERS (0x80000003) 
#HKEY_CURRENT_CONFIG (0x80000005) 
#HKEY_DYN_DATA (0x80000006) 
#Note that HKEY_DYN_DATA is a valid tree for Windows 95 and Windows 98 computers only. 
#
#sSubKeyName
#Specifies the path that contains the subkeys to be enumerated. 
#
#sNames
#Contains an array of subkey strings. 
#
sub printTree {
    my $path = shift;
    my $inParams = $StdRegProv->{Methods_}{"EnumKey"}->{InParameters};
    $inParams->{Properties_}{"hDefKey"}->{Value} = $rootKey{HKEY_CURRENT_CONFIG};
    $inParams->{Properties_}{"sSubKeyName"}->{Value} = "HKEY_CURRENT_CONFIG";
    my $outParams = $StdRegProv->ExecuteMethod_("EnumKey", $inParams);

    my @names = @{$outParams->{sNames}};
    print join "\n", @names;

}