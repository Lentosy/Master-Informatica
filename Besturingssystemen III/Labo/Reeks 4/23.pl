use strict;
use warnings;
use Win32::OLE 'in';


if(scalar @ARGV == 0){
	print STDERR "No directory specified\n";
	exit 1;
}

my $directory = $ARGV[0]; 
my $depth = $ARGV[1]; # todo controle ofdat argument opgegeven wordt en numeriek

# check if file actaully exists
my $filesystemobject = Win32::OLE->new("Scripting.FileSystemObject");
if(!$filesystemobject->FolderExists($directory)){
	print STDERR "The directory $directory does not exist\n";
	exit 1;
}

my $locator = Win32::OLE->new("Wbemscripting.SWbemLocator");
my $service = $locator->ConnectServer("127.0.0.1", "root/CIMV2");

my $totalbytes = 0;
my $recursiondepth = 0;


# start van de recursie
DirectorySize($directory, $depth);
print "Total bytes for '$directory' and depth $depth is ";
bytes_to_readable($totalbytes);

sub DirectorySize {
	(my $directory, my $depth) = (@_);
	print_indentation();
	print "$directory\n";
	if($recursiondepth < $depth){
		$recursiondepth++;
		# opvragen alle directories en DirectorySize oproepen
		my @directories = in $service->AssociatorsOf("Win32_Directory.Name='$directory'", undef, "Win32_Directory");
		splice @directories, $#directories, 1; # verwijzing naar eigen map verwijderen
		for(@directories){
			DirectorySize($directory . "\\" . $_->{FileName}, $depth);
		}
		$recursiondepth--;
	}
	my @files = in $service->AssociatorsOf("Win32_Directory.Name='$directory'", undef , "CIM_DataFile");
	$totalbytes += $_->{FileSize} for(@files);
}

sub print_indentation {
    for (1 .. $recursiondepth ){
        print "|";
    }
}


sub bytes_to_readable {
	my $bytes = shift;
	my $index = 0;
	my @suffix = ["B", "KB", "MB", "GB", "TB];
	while($bytes > 1000){
		$bytes /= 1000;
		$index ++;
	}
	print $index;
	print $bytes . " " . $suffix[$index]; 

}