use strict;
use warnings;
use Win32::OLE qw(in);
use Win32::OLE::Const;


#SWbemObjectEx bevat Properties_ en SystemProperties_ attributen. Beiden zijn van type SWbemPropertySet
#SWbemPropertySet bevat één attribuut Count. 

if(scalar @ARGV != 1){
    print STDERR "One argument expected: a WMI class\n";
    exit 1
}

my $classname = $ARGV[0];

my $locator = Win32::OLE->new("WbemScripting.SWbemLocator");
my $service = $locator->ConnectServer("127.0.0.1", "root/CIMV2");
my $class = $service->Get($classname);

my @properties = in $class->{SystemProperties_};
push @properties, in $class->{Properties_};

my %constants = %{Win32::OLE::Const->Load($locator)};
my %cimtypes = ();
for(keys %constants){
    if ($_ =~ /wbemCimtype(.*)/){
        $cimtypes{$constants{$_}} = lc $1; # hash inverteren
    }
}

my $longestwordlength = 0; # nodig voor te padden
for(@properties){
    if(length $_->{Name} > $longestwordlength){
        $longestwordlength = length $_->{Name};
    }
}

$longestwordlength += 2;

print "Properties for class $classname:\n";
for(@properties){
    printf "%-${longestwordlength}s:  ", $_->{Name};
    print "array of " if $_->{IsArray};
    print $cimtypes{$_->{CIMType}};
    

    print "\n";
}



