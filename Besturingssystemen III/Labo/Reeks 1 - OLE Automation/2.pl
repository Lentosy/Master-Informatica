use Win32::OLE qw(in with);

while((my $key, my $value) = each %INC){
    print "$key => $value\n";
}