use Win32::OLE;
Win32::OLE->Option(Warn => 2); 
# zet op 2, want 3 roept croak() op, dat de applicatie zal stoppen, 2 roept carp() op, dat enkel een foutboodschap zal printen

my $cdo = Win32::OLE->new("fout");