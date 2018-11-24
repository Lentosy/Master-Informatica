use Win32::OLE;
use Win32::OLE::Const;
Win32::OLE->Option(Warn => 3);

my $excelfile = 'voud.xlsx';

my $excel = Win32::OLE->GetActiveObject('Excel.Application') || Win32::OLE->new('Excel.Application', 'Quit');
$excel->{DisplayAlerts} = 0;
$excel->{Visible} = 1;
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
$sheet->{Name} = 'Veelvouden van 2 tot 10';
$range = $sheet->Range($sheet->Cells(1, 1), $sheet->Cells(49, 9));

my $matrix = $range->{Value};

my $i = 1;

for ($i=1;$i<=100;$i++){
     for ($j=2; $i*$j <= 100; $j++) {
        $matrix[$i-1][$j-2]=$i*$j;
     }
}

$range->{Value} = $matrix;

$constants = Win32::OLE::Const->Load($excel);

$range->{Columns}->AutoFit();
$range->{Rows}->AutoFit();

$range->Rows(1)->{Font}->{Bold} = 1;

$range->Rows(1)->Borders($constants->{xlEdgeBottom})->{LineStyle} = $constants->{xlContinuous};
$range->Borders($constants->{xlInsideVertical})->{LineStyle} = $constants->{xlContinuous};


$book->SaveAs($absolutepath);