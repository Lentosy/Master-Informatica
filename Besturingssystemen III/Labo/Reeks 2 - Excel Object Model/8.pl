use Win32::OLE;
Win32::OLE->Option(Warn => 3);

my $excelfile = 'voud.xlsx';

my $excel = Win32::OLE->new('Excel.Application', 'Quit');
my $fso   = Win32::OLE->new('Scripting.FileSystemObject');

my $absolutepath = $fso->GetAbsolutePathName($excelfile);
my $book;
if(!$fso->FileExists($absolutepath)){
    $book = $excel->{Workbooks}->Add();
    $book->SaveAs($absolutepath);
} else {
    $book = $excel->{Workbooks}->Open($absolutepath);
}

my $sheet = $book->{Worksheets}->Item(1);
my $range = $sheet->Cells() #todo, afwerken

my $matrix;


