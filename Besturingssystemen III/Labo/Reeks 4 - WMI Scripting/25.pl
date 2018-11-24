
use Win32::OLE qw(in);
use Win32::OLE::Const 'Microsoft WMI Scripting';

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
my $service = $locator->ConnectServer('.', 'root/cimv2');


my $recursiondepth = 0;
GetClasses(shift);
sub GetClasses {
    my $class = shift;
    PrintClass($class);
    my @subclasses = in $service->SubclassesOf($class, wbemQueryFlagShallow);
    for my $subclass (@subclasses){
        $recursiondepth++;
        GetClasses($subclass->{Path_}->{Class});
        $recursiondepth--;
    }
}

sub PrintClass {
    print "\t" x $recursiondepth;
    print shift;
    print "\n";
}