use Win32::OLE::Const;

$filename = "voud.xlsx";

$fso = Win32::OLE->new('Scripting.FileSystemObject');
$excel = Win32::OLE->GetActiveObject('Excel.Application') || Win32::OLE->new('Excel.Application', 'Quit');

$filename = $fso->getAbsolutePathName($filename);

$book = $excel->{Workbooks}->Open($filename);
$sheet = $book->{Worksheets}->Item(1);
$sheet->{UsedRange}->{Columns}->AutoFit();
$sheet->{UsedRange}->{Rows}->AutoFit();

$sheet->{UsedRange}->{Font}->{Bold} = false;

$sheet->Range('A1:I1')->{Font}->{Bold} = true;


$book->SaveAs($filename);