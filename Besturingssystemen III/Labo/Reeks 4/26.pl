use strict;
use warnings;
use Win32::OLE qw(in);


my $locator = Win32::OLE->new("WbemScripting.SWbemLocator");
my $service = $locator->ConnectServer("127.0.0.1", "root/CIMV2");


