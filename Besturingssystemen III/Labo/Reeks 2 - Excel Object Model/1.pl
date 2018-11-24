use Win32::OLE qw(in); 
#gebruik bestaand process of start een nieuw proces in embedded mode

my $excel = Win32::OLE->GetActiveObject('Excel.Application') || Win32::OLE->new('Excel.Application', 'Quit');

print "\naantal werkboeken in excel : ", $excel->{Workbooks}->{Count};
print "\n-----------------------------------------\n";

#werkbook toevoegen
my $book=$excel->{Workbooks}->Add();
print "\naantal werkboeken in excel : ", $excel->{Workbooks}->{Count};
print "\naantal werksheets in het toegevoegd boek:", $book->{Worksheets}->{Count};
print "\n\t$_->{name}" foreach in $book->{Worksheets};
print "\n-----------------------------------------\n";

#Werkblad toevoegen
$book->{Worksheets}->add();
print "\nNa add : aantal werksheets in het toegevoegd boek:", $book->{Worksheets}->{Count};
print "\n\t$_->{name}" foreach in $book->{Worksheets};
print "\n-----------------------------------------\n";

$excel->{DisplayAlerts}=0; #geen foutboodschappen tonen 