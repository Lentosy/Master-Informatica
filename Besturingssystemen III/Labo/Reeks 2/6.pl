use Win32::OLE::Const;

if(!$ARGV[0]){
	print "Name of excelfile not specified.\n";
	exit 1;
}

$filename = $ARGV[0];

$fso = Win32::OLE->new('Scripting.FileSystemObject');
$excelAppl = Win32::OLE->GetActiveObject('Excel.Application') || Win32::OLE->new('Excel.Application', 'Quit');
$excelAppl->{DisplayAlerts}=0; #geen foutboodschappen tonen 

$filename = $fso->GetAbsolutePathName($filename);
if(!$fso->FileExists($filename)){ # indien bestand nog niet bestaat wordt deze aangemaakt
	print "$filename does not exist\n";
	exit 1;
}

$book = $excelAppl->{Workbooks}->Open($filename); # WorkBook object
$sheet = $book->{WorkSheets}->Item(4);

$range = $sheet->Range("A1:D10");
print "Range('A1:D10')\n";
print_values();



$range = $sheet->Cells(4,1);
print "Cells(4, 1)\n";
print_values();



$range = $sheet->Range($sheet->Cells(1, 1), $sheet->Cells(4, 3));
print "Range(sheet->Cells(1, 1), sheet->Cells(4, 3))\n";
print_values();



sub print_values {
	$values = $range->{Value};
	foreach $rows (@$values){
		foreach $scal (@$rows){
			print "$scal\t";
		}
	print "\n";
	} 
}
