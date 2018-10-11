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
	$book = $excelAppl->{Workbooks}->Add();
	$book->SaveAs($filename);
}

$excelAppl->{Workbooks}->Open($filename);
print "\nAantal werksheets: " . $excelAppl->{WorkSheets}->{Count};




