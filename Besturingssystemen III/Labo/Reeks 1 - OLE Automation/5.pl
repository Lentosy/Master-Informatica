use Win32::OLE;

my $cdo = Win32::OLE->new("CDO.message");
my $fso = Win32::OLE->new("Scripting.FileSystemObject");

Win32::OLE->EnumAllObjects(
    sub {
        my $object = shift;
        print Win32::OLE->QueryObjectType($object);
        print "\n";
    }
)