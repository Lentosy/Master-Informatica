use Win32::OLE;

my $cdo = Win32::OLE->new("CDO.message");
print ref $cdo;