use Win32::OLE qw(in);
use Win32::OLE::Const 'Microsoft WMI Scripting ';
my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
GetNameSpaces('root');

sub GetNameSpaces {
    my $namespace = shift;
    my $service = $locator->ConnectServer('.', $namespace);
    if(Win32::OLE->LastError()){
        "No access to $namespace\n";
        return;
    }

    print "$namespace: " ;
    my $classCount = scalar (in $service->ExecQuery("SELECT * FROM meta_class"));
  
    my $classCountDirect = scalar (in $service->SubclassesOf(undef,wbemQueryFlagShallow));
    print "$classCountDirect < $classCount";
    print "\n";
    my @subnamespaces = map { $_->{Name} } in $service->InstancesOf('__NAMESPACE');
    while (scalar @subnamespaces){
        $subnamespace = pop @subnamespaces;
        GetNameSpaces("$namespace/$subnamespace");
    }
}
