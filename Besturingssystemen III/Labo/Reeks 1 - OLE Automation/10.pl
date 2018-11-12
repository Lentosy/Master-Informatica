use Win32::OLE;
use Win32::OLE::Const;

my $cdo = Win32::OLE->new("CDO.Message");
$constants = Win32::OLE::Const->Load($cdo);
while((my $key, my $value) = each %$constants){
    print "$key => $value\n";
}