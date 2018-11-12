use Win32::OLE;
my $file = $ARGV[0] or die "No filename specified $!\n";
my $fso = Win32::OLE->new("Scripting.FileSystemObject");


if($fso->FileExists($file)){
    printf "The absolute path is %s\n", $fso->GetAbsolutePathName($file); 
} else {
    printf "File %s does not exist in the current directory\n", $file;
}