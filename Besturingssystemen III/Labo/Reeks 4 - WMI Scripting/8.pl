use Win32::OLE qw(in);
Win32::OLE->Option(Warn => 2);


my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
GetNameSpaces('root');

sub GetNameSpaces {
    my $namespace = shift;
    print "$namespace\n" ;
    my $service = $locator->ConnectServer('.', $namespace);
    return if (Win32::OLE->LastError());
    my @subnamespaces = map { $_->{Name} } in $service->InstancesOf('__NAMESPACE');
    while (scalar @subnamespaces){
        $subnamespace = pop @subnamespaces;
        GetNameSpaces("$namespace/$subnamespace");
    }
}
