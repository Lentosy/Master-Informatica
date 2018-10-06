use Win32::OLE; 

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
$sheet = $book->{WorkSheets}->Item(1); # eerste worksheet selecteren // WorkSheet object 
$range = $sheet->{UsedRange}; # Range object
print "\nAantal rijen: " . $range->{Rows}->{Count};
print "\nAantal kolommen: " . $range->{Columns}->{Count};

print "\n";



