use Win32::OLE;
Win32::OLE->Option(Warn => 3);

my $excelfile = $ARGV[0] or die "No file specified\n";

my $fso = Win32::OLE->new('Scripting.FileSystemObject');
my $excel = Win32::OLE->new('Excel.Application', 'quit');

my $absolutepath = $fso->GetAbsolutePathName($excelfile);
my $book;
if(!$fso->FileExists($absolutepath)){
    print "File $excelfile does not exist yet. Creating $excelfile ...\n";
    $book = $excel->{Workbooks}->Add();
    $book->SaveAs($absolutepath);
} else {
    $book = $excel->{Workbooks}->Open($absolutepath);
}

printf "Opened file %s, which has %d worksheet(s).\n", $excelfile, $book->{Worksheets}->{Count};

