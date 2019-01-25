use Win32::OLE;
use Win32::OLE::Const;
use Data::Dumper;
Win32::OLE->Option(Warn => 3);

my $punten_bestand = "punten.xls";
my $punten2_bestand = "punten2.xls";

my $excel = Win32::OLE->GetActiveObject('Excel.Application') || Win32::OLE->new('Excel.Application', 'Quit');
$excel->{DisplayAlerts} = 0;
my $fso = Win32::OLE->new('Scripting.FileSystemObject');
my $punten_bestand = $fso->GetAbsolutePathName("punten.xls");
my $punten2_bestand = $fso->GetAbsolutePathName("punten2.xls");
$constants = Win32::OLE::Const->Load($excel);

# PUNTEN TOEVOEGEN AAN PUNTEN.XLS
my $book_punten2 = $excel->{Workbooks}->Open($punten2_bestand);
my $perl_sheet = $book_punten2->{Worksheets}->Item('perl');
my $range = $perl_sheet->{UsedRange};
$range->Sort($range);
my @punten2 = map {
    map {
        @{$_}[0];
    } @$_
} $perl_sheet->{UsedRange}->Columns(2)->{Value};
$book_punten2->Close();

my $book_punten = $excel->{Workbooks}->Open($punten_bestand);
my $architectuur_sheet = $book_punten->{Worksheets}->Item('architectuur');
    
# eerst punten inlezen van vak1, dan gemiddelde bepalen, dan twee kolommen terug uitschrijven (punten vak2, gemiddelde) 

my @punten = map {
    map {
        @{$_}[0];
    } @$_
} $architectuur_sheet->{UsedRange}->Columns(2)->{Value};


my $mem_range = $architectuur_sheet->Range($architectuur_sheet->Cells(1, 3), $architectuur_sheet->Cells(189, 4))->{Value};
for(0 .. scalar @punten - 1){
    $mem_range->[$_][0] = $punten2[$_];
    $mem_range->[$_][1] = int (($punten[$_] + $punten2[$_])/2); 
    # als ge een kleurke wilt geven aan de nummers op basis van geslaagd , of gebuisd, moet ge toch elk punt in de array overlopen, en per punt de stijl instellen => veel COM calls.
    # hier wordt het niet expliciet gevraagd, ge kunt wel alle nummerkes vet maken
}

$architectuur_sheet->Range($architectuur_sheet->Cells(1, 3), $architectuur_sheet->Cells(189, 4))->{Value} = $mem_range;
$architectuur_sheet->Range($architectuur_sheet->Cells(1, 3), $architectuur_sheet->Cells(189, 4))->{Font}->{Bold} = 1;
$book_punten->SaveAs($punten_bestand);
# AD VALVAS SHEET TOEVOEGEN
my $sheet_advalvas;
if($book_punten->{Worksheets}->{Count} == 1){
    $sheet_advalvas = $book_punten->{Worksheets}->Add();
    $sheet_advalvas->{Name} = 'ad valvas';
} else {
    $sheet_advalvas = $book_punten->{Worksheets}->Item('ad valvas');
}

# todo, advalvas, kmoet eerst WMI doen






$book_punten->SaveAs($punten_bestand);
$book_punten->Close();
