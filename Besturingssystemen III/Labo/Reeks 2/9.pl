use Win32::OLE::Const;

my $fso = Win32::OLE->new("Scripting.FileSystemObject");
my $excel = Win32::OLE->GetActiveObject('Excel.Application') || Win32::OLE->new('Excel.Application', 'Quit');
$excel->{DisplayAlerts} = 0;

my $bestand_punten1 = $fso->getAbsolutePathName("punten.xls");
my $bestand_punten2 = $fso->getAbsolutePathName("punten2.xls");

my $punten_perl_alfabetisch = lees_bestand2();# geeft een array referentie terug met de punten van perl gesorteerd op de naam van de student
voeg_toe_in_bestand1($punten_perl_alfabetisch);

voeg_advalvas_toe();

sub voeg_advalvas_toe {
	my $book_punten1 = $excel->{Workbooks}->Open($bestand_punten1);
	my $sheet_advalvas;
	if($book_punten1->{Worksheets}->{Count} == 1){ # als == 1, dan is er maar 1 worksheet, namelijk die met de punten
		$sheet_advalvas = $book_punten1->{Worksheets}->Add();
		$sheet_advalvas->{Name} = "ad valvas";
	} else {
		$sheet_advalvas = $book_punten1->{Worksheets}->Item("ad valvas");	
	}

	
	# hash dat per graad de studenten bijhoudt. Aangezien de originele data al gesorteerd is, zal de data ook gesorteerd zijn per graad
	my %puntenverdeling = ('A' => [], # alle studenten met punten >= 12
						   'B' => [], # alle studenten met punten < 12 en punten >= 10
						   'C' => [], # alle studenten met punten < 10 en punten >=  7
						   'D' => []  # alle studenten met punten < 7 en punten >=  0
						   );
	my $sheet_architectuur = $book_punten1->{Worksheets}->Item("architectuur");
	my $data = $sheet_architectuur->{UsedRange}->{Value};
	for(@$data){
		my ($naam, $punten) = @$_[0, 3];
		my $letter = 'A';
		if($punten < 7){
			$letter = 'D';
		} elsif ($punten < 10){
			$letter = 'C';
		} elsif ($punten < 12){
			$letter = 'B';
		}
		push @{$puntenverdeling{$letter}}, $naam;
	}
	
	# alles eerst verwijderen, handig om te testen
	$sheet_advalvas->{UsedRange}->ClearContents();

	my $basisrij = 2; # een variabele die zegt op welke rij het volgende blok moet beginnen. (de blokken 'A' ,'B', ...). Default 2 omdat ik niet wil dat 
					  # rij 1 ingevuld wordt, zodat we ook de top border zien op de eerste rij
	for my $blok (sort keys %puntenverdeling){
		my @studenten = @{$puntenverdeling{$blok}};
		my $nog_in_te_vullen = scalar @studenten; # het aantal studenten dat nog ingevuld moet worden.
		my $vorige_ingevuld = 0; # het aantal studenten dat in de vorige kolom werden ingevuld
		for(1 .. 5){ # 5 kolommen. Ik schuif op met 1 zodat de kolom A niet ingevuld wordt, ik doe dit zodat je ook links de rand hebt
			#bepalen hoeveel rijen er voor kolom $_ nodig zijn
			my $aantal_rijen = int((($nog_in_te_vullen - $vorige_ingevuld) / (5 - ($_ - 1))) + 0.9999);
			$sheet_advalvas->Cells($basisrij, 4)->{Value} = $blok; # de eerste rij van een blok waarvan de middelste kolom ingevuld is met de blokletter.
			$sheet_advalvas->Cells($basisrij, 4)->{Font}->{Bold} = 1; # nog vet zetten ook


			for(my $i = 1; $i <= $aantal_rijen; $i++){
				$sheet_advalvas->Cells($basisrij + $i, $_ + 1)->{Value} = @studenten[$i - 1 + $vorige_ingevuld];
			}

			$vorige_ingevuld += $aantal_rijen;
			
		}
		my $max_rij = int((scalar @studenten / 5) + 0.9999);
		$sheet_advalvas->Range($sheet_advalvas->Cells($basisrij, 2), $sheet_advalvas->Cells($basisrij + $max_rij, 6))->BorderAround(6);
		$basisrij = $basisrij + $max_rij + 2;
	}

	# ervoor zorgen dat de namen mooi in hun cellen passen.
	$sheet_advalvas->{UsedRange}->{Columns}->AutoFit();
	$sheet_advalvas->{UsedRange}->{Interior}->{ColorIndex} = 2; # opvullen met wit, zodat indivuele celranden niet meer zichtbaar zijn.
	$sheet_advalvas->Cells(1,1)->{ColumnWidth} = 1; # versmallen van de kolom A, aangezien we die toch niet gebruiken
	$sheet_advalvas->SaveAs($bestand_punten1);
}

sub lees_bestand2 {
	my $book_punten2 = $excel->{Workbooks}->Open($bestand_punten2);
	my $sheet_perl = $book_punten2->{Worksheets}->Item("perl");
	$sheet_perl->{UsedRange}->Sort($sheet_perl->Range("A1:A189")); # punten2.xls sorteren op naam, zodat elke rij overeenkomt met punten.xls
	my @punten =  map {
					 map { 
							@{$_}[0] 
					     } @{$_} 
				   } $sheet_perl->Range("B1:B189")->{Value}; # de punten selecteren
	return \@punten;
}

sub voeg_toe_in_bestand1 {
	my $punten_perl = shift;
	my $book_punten1 = $excel->{Workbooks}->Open($bestand_punten1);
	my $sheet_architectuur = $book_punten1->{Worksheets}->Item("architectuur");

	my $rijnr = 1;
	for (@$punten_perl){
		$sheet_architectuur->Cells($rijnr, 3)->{Value} = $_;
		if($_ < 10){
			$sheet_architectuur->Cells($rijnr, 3)->{Font}->{ColorIndex} = 3;
		} else{
			$sheet_architectuur->Cells($rijnr, 3)->{Font}->{ColorIndex} = 5;
		}

		#gemiddelde
		my $gem = int(($_ + $sheet_architectuur->Cells($rijnr, 2)->{Value}) / 2);
		$sheet_architectuur->Cells($rijnr, 4)->{Value} = $gem;
		if($gem < 10){
			$sheet_architectuur->Cells($rijnr, 4)->{Font}->{ColorIndex} = 3;
		} else{
			$sheet_architectuur->Cells($rijnr, 4)->{Font}->{ColorIndex} = 5;
		}
		$rijnr++;
	}

	$range = $sheet_architectuur->Range("C1:D189");
	$range->{Font}->{Bold} = 1;
	
	$sheet_architectuur->SaveAs($bestand_punten1);
}