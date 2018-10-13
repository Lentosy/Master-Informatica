# Het ProgID van het Locator-obect is WbemScripting.SWbemLocator. De TypeLibrary is wbemdisp.

use strict;
use warnings;

use Win32::OLE::Const;


my $locator = Win32::OLE->new("WbemScripting.SWbemLocator");

my %constants = %{Win32::OLE::Const->Load($locator)};

for (sort {$a cmp $b} keys %constants){
    printf "%30s : %s\n", $_, $constants{$_};
}