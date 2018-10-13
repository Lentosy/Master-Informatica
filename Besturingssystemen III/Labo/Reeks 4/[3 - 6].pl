
use strict;
use warnings;

use Win32::OLE qw(in);

my $locator = Win32::OLE->new("WbemScripting.SWbemLocator");
my $service = $locator->ConnectServer("127.0.0.1","root/CIMV2"); 

oef3();
oef4();
oef5();
oef6();

sub oef3 {
    print "\n*** Oefening 3 ***\n";
    my $networkadapter = $service->Get("Win32_NetworkAdapter");
    #my $networkadapter = Win32::OLE->GetObject("winmgmts://127.0.0.1/ROOT/CIMV2:Win32_NetworkAdapter");
    my $networkadapterInstance = $service->Get("Win32_NetworkAdapter.DeviceID='2'");
    printf $networkadapterInstance->{Name};
}

sub oef4 {
    print "\n\n*** Oefening 4 ***\n";
    my $directory = $service->Get("Win32_Directory.Name='C:/'");
    print $directory->{FileType};
}

sub oef5 {
    print "\n\n*** Oefening 5 ***\n"; 
    my $os = $service->Get("Win32_OperatingSystem=@");
    printf "%s %s v%s\n",
         $os->{Caption},
         $os->{OSArchitecture},
         $os->{Version};
}

sub oef6 {
        print "\n\n*** Oefening 6 ***\n"; 
        my ($osIO) = in $service->InstancesOf("Win32_OperatingSystem");
        printf "Met InstancesOf(): %s %s v%s\n",
         $osIO->{Caption},
         $osIO->{OSArchitecture},
         $osIO->{Version};

        my ($osWQL) = in $service->ExecQuery("select * from Win32_OperatingSystem");
        printf "met ExecQuery(): %s %s v%s\n",
         $osWQL->{Caption},
         $osWQL->{OSArchitecture},
         $osWQL->{Version};
}