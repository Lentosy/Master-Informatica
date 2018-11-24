use Win32::OLE::Const;
$constants = Win32::OLE::Const->Load("Microsoft CDO for Windows 2000 Library");
while((my $key, my $value) = each %$constants){
    print "$key => $value\n";
}