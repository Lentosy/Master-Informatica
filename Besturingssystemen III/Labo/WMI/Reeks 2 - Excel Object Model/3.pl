use Win32::OLE qw(in);
Win32::OLE->Option(Warn => 3);

my $excelfile = $ARGV[0] or die "No file specified\n";

my $excel = Win32::OLE->new('Excel.Application', 'Quit');
my $fso = Win32::OLE->new('Scripting.FileSystemObject');

my $absolutepath = $fso->GetAbsolutePathName($excelfile);

if(!$fso->FileExists($absolutepath)){
    print "The file $excelfile does not exist in the current directory\n";
    exit 1;
}

$book = $excel->{Workbooks}->Open($absolutepath);
print "Sheet | Rows | Columns\n";
for my $sheet (in $book->{Worksheets}){
    print $sheet->{Name};
    printf "| %4d | ", $sheet->{UsedRange}->{Rows}->{Count}; 
    printf "%7d", $sheet->{UsedRange}->{Columns}->{Count}; 
    print "\n";
}



