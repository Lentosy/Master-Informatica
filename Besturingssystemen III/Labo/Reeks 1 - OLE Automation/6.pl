use Win32::OLE;

my $cdo = Win32::OLE->new("fout");
print Win32::OLE->LastError() if Win32::OLE->LastError();
