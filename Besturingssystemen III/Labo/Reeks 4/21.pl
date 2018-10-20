use strict;
use warnings;
use Win32::OLE;

geefstatus("Begin ");
my $Excel =  Win32::OLE->new('Excel.Application', 'Quit');
geefstatus("Nieuwe Excel Applicatie gestart");
$Excel = Win32::OLE->GetActiveObject('Excel.Application');
geefstatus("Draaiende Excel-applicatie gebruiken");
my $Book = $Excel->Workbooks->Add();
geefstatus("Werkbook toegevoegd");
$Book->Save();
geefstatus("Werkboek opgeslaan");


sub geefstatus {
	printf "%s\n", shift;
}