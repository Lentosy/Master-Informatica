use Win32::OLE qw(in);
Win32::OLE->Option(Warn => 3);
# ik heb oefening aangepast zodat het alle perl bestanden toont, dan moet ik geen excel bestanden aanmaken
my $fso = Win32::OLE->new("Scripting.FileSystemObject");

for my $file (in $fso->GetFolder(".")->{Files}){
    if($file->{Type} =~ /Perl/){
        print $file->{ShortName};
        print "\n";
    }
}