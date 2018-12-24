use Win32::OLE;
use Win32::OLE::Const;

my $locator = Win32::OLE->new('WbemScripting.SWbemLocator');
$constants = Win32::OLE::Const->Load($locator );

for my $key (sort {$b cmp $a } keys %$constants){
    print "$key => $constants->{$key}\n";
}