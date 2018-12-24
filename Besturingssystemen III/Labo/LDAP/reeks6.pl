# Op het examen moet je inloggen met je eigen credentials. De code die hiervoor nodig is taat in de bind_object subroutine, gemarkeerd met |!|
# Op het examen wordt dan ook het ip-adres gegeven, waarschijnlijk 192.168.16.16

use warnings;

use Win32::OLE qw(in);
use Win32::OLE::Variant;
#use Win32::OLE::Const 'Active DS Type Library'; 

# als je niet op de VM werkt kan je natuurlijk de constanten van 'Active DS Type Library' niet inladen
# daarom voorzie ik volgende hashes, enkel aangevuld met constanten die nodig zijn in de oefeningen:

#ms-help://MS.MSDNQTR.v90.en/adsi/adsi/ads_authentication_enum.htm
my %ADS_AUTHENTICATION_ENUM = 
    (
        ADS_SECURE_AUTHENTICATION => 0x1
    );

my %ADS_USER_FLAG_ENUM = 
    (
        ADS_UF_ACCOUNTDISABLE => 0x2,
        ADS_UF_PASSWD_NOTREQD => 0x20
    )

## STRUCTUUR VAN DIT BESTAND 
# Elke oefening krijgt zijn eigen subroutine, die op zijn beurt andere, globale subroutines kan aanroepen. 
# Met een globale subroutine bedoel ik subroutines die niet specifiek zijn voor een oefening, behalve de bind_object methode van oef 1 tot oef 5.
# Het bestand uitvoeren:
# perl reeks6.pl oefnr arg1 arg2 ... argn

my $oefnr = $ARGV[0] or die "geef oefeningnummer op";
"oef$oefnr"->();

sub oef6 {
    my $object = bind_object("CN=Satan,OU=Domain Controllers,DC=iii,DC=hogent,DC=be");
    my @attributen = qw(adspath class guid name parent schema);
    print_attributen($object, @attributen);
}

sub oef7 {
    my $object = bind_object("CN=Bert De Saffel,OU=EM7INF,OU=Studenten,OU=iii,DC=iii,DC=hogent,DC=be");
    my @attributen = qw(adspath mail);
    print_attributen($object, @attributen);
}

sub oef8 {
    my $object = bind_object("OU=EM7INF,OU=Studenten,OU=iii,DC=iii,DC=hogent,DC=be");
    my @attributen = qw(adspath guid class objectguid distinguishedname objectclass);
    print_attributen($object, @attributen);
}

sub oef9 {
    my $object = bind_object("CN=Bert De Saffel,OU=EM7INF,OU=Studenten,OU=iii,DC=iii,DC=hogent,DC=be");
    my @attributen = qw(mail givenname sn displayname homedirectory scriptpath profilepath logonhours userworkstations);
    print_attributen($object, @attributen);
}

sub oef10 {
    if(uc $ENV{USERDOMAIN} eq "III"){
        system("dsquery user- name \"Bert De Saffel\"");
        system("dsquery * \"CN=Bert De Saffel,OU=EM7INF,OU=Studenten,OU=iii,DC=iii,DC=hogent,DC=be\" -attr mail objectclass");
    } else {
        system("dsquery * \"CN=Bert De Saffel,OU=EM7INF,OU=Studenten,OU=iii,DC=iii,DC=hogent,DC=be\" -s 193.190.126.71 -u \"Bert De Saffel\" -p \"Bert De Saffel\" -attr mail objectclass");
    }
}

sub oef11 {
    print "Deze oefening moeten we niet kunnen\n";
}

sub oef12 {
    my $root = bind_object('RootDSE');
    print "Server DNS:               $root->{dnsHostName}\n";
    print "       SPN:               $root->{ldapServiceName}\n";
    print "       Datum & tijd:      $root->{currentTime}\n";
    print "       Global Catalog ?   $root->{isGlobalCatalogReady}\n";
    print "       gesynchronizeerd ? $root->{isSynchronized}\n";
    print "       DN:                $root->{serverName}\n";

    print "Domeingegevens:           $root->{defaultNamingContext}\n";
    print "Configuratiegegevens:     $root->{configurationNamingContext}\n";
    print "Schema:                   $root->{schemaNamingContext}\n";

    print "Functioneel niveau \n";
    print "    Forest:               $root->{forestFunctionality}\n";
    print "    Domein:               $root->{domainFunctionality}\n";

    print "\nOphalen object, met behulp van het attribuut 'defaultNamingContext' van RootDSE:\n";
    my $object = bind_object("CN=Administrator,CN=Users,$root->{defaultNamingContext}");
    print "\n";
    print "RDN:                   $object->{Name}\n";
    print "klasse:                $object->{Class}\n";
    print "objectGUID:            $object->{GUID}\n";
    print "ADsPath:               $object->{ADsPath}\n";
    print "ADsPath Parent:        $object->{Parent}\n";
    print "ADsPath schema klasse: $object->{Schema}\n";
}

sub oef13 {
    my $root = bind_object('RootDSE');
    my @attributen = qw(name class guid adspath parent schema defaultnamingcontext dnshostname);
    print_attributen($object, @attributen);
    print "\nOmwisselen defaultnamingcontext en dnshostname\n\n";
    ($attributen[$#attributen], $attributen[$#attributen - 1]) = ($attributen[$#attributen - 1], $attributen[$#attributen]);
    print_attributen($object, @attributen);
}

sub oef14 {
    print "Deze oefening moeten we niet kunnen\n";
}

sub oef15 {
    (my $root = bind_object('RootDSE'))->GetInfo(); # GetInfo om propertycache te initialiseren 
    my $domein = $root->{defaultnamingcontext};
    my $domeincontrollers = bind_object("OU=Domain Controllers,$domein");
    for(in $domeincontrollers){
        printf "%s\n", $_->{cn}; 
    }
}

sub oef16 {
    my $lokaalID = $ARGV[1] or die "Geef lokaal op: 219 of 225";
    (my $root = bind_object('RootDSE'))->GetInfo(); # GetInfo om propertycache te initialiseren 
    my $domein = $root->{defaultnamingcontext};
    my $lokaal = bind_object("OU=$lokaalID,OU=PC's,OU=iii,$domein");
    for(in $lokaal){
        print $_->{distinguishedname} . "\n";
    }   
}

sub oef17 {
    (my $root = bind_object('RootDSE'))->GetInfo(); # GetInfo om propertycache te initialiseren 
    my $domein = $root->{defaultnamingcontext};
    my $system = bind_object("CN=System,$domein");
    my @attributen = qw(cn class);
    print "AD objecten in de container CN=System,DC=iii,DC=hogent,DC=be\n";
    for (in $system){
        print "\n";
        print_attributen($_, @attributen);
    }
}

sub oef18 {
    my $klasse = $ARGV[1] or die "Geef klasse op";
    (my $root = bind_object('RootDSE'))->GetInfo(); # GetInfo om propertycache te initialiseren 
    my $domein = $root->{defaultnamingcontext};
    my $gebruikers = bind_object("CN=Users,$domein");
    $gebruikers->{Filter} = [$klasse];
    my @attributen = qw(adspath);
    print "AD-objecten van type $klasse:\n";
    for(in $gebruikers){
        print_attributen($_, @attributen);
    }

    print "Administrator:\n";
    my $administrator = $gebruikers->GetObject('user', 'CN=Administrator');
    print_attributen($administrator, @attributen);
}

sub oef19 {
    (my $root = bind_object('RootDSE'))->GetInfo(); # GetInfo om propertycache te initialiseren 
    my @attributen = qw(defaultnamingcontext schemanamingcontext configurationnamingcontext namingcontexts);
    print_attributen($root, @attributen);
}

sub oef20 {
    (my $root = bind_object('RootDSE'))->GetInfo(); # GetInfo om propertycache te initialiseren 
    my %klassenfrequentie; # key: klasse, value: aantal keer dat deze is voorgekomen
    my @containers = qw(defaultnamingcontext schemanamingcontext configurationnamingcontext);
    our sub overloop_recursief {
        my $obj = shift;
        my $kf = shift;
        $kf->{$obj->{class}}++;
        print "\n", $obj->{class} if $kf->{$obj->{class}} % 100 == 99;
        for(in $obj){          
            overloop_recursief($_, $kf);
        }
    };
    our sub print_hash_geordend {
        my $hash = shift;
        for my $key (sort { $hash->{$a} <=> $hash->{$b} } keys %{$hash}){
            printf "%30s => %s\n", $key, $hash->{$key};
        }
    }
    for (1 .. $#ARGV){
        overloop_recursief(bind_object($root->{$containers[$_]}), \%klassenfrequentie);
    }
    print_hash_geordend(\%klassenfrequentie);
}

sub oef21 {
    (my $root = bind_object('RootDSE'))->GetInfo();
    my $domein = $root->{defaultnamingcontext};
    my $administrator = bind_object("CN=Administrator,CN=Users,$domein");
    my @attributen = qw(accountdisabled accountexpirationdate badlogincount department description division emailaddress employeeid faxnumber firstname fullname homedirectory homepage isaccountlocked languages lastfailedlogin lastlogin lastlogoff lastname loginscript manager maxstorage nameprefix namesuffix officelocations othername passwordlastchanged passwordrequired picture postalcodes profile telephonehome telephonemobile telephonenumber telephonepager title);
    print_attributen($administrator, @attributen);
}

sub oef22 {
    # werkt enkel op VM of labotoestel
    use Win32::OLE::Const;
    %constants = %{Win32::OLE::Const->Load('Active DS Type Library')};
    for my $key (keys %constants){
        print "$key => $constants{$key}\n" if $key =~ /_UF_/;
    }

}

sub oef23 {
    my $root = bind_object('RootDSE');
    my $domein = $root->{defaultnamingcontext};
    
}




sub print_attributen {
    my $obj = shift;
    for my $attribuut (@_){
        printf "%30s : ", $attribuut;

        if($obj->{$attribuut}){
            if(ref $obj->{$attribuut} eq "ARRAY"){ # specifieke uitvoer voor een array
                print '(' . scalar @{$obj->{$attribuut}} . ') ';
                print '[';
                print join '|', @{$obj->{$attribuut}};
                print ']';
            } else { # speciale case voor objectGUID (bitstring) werkt niet somehow
                print $obj->{$attribuut};
            }
        } else {
            print '(geen waarde)';
        }
        print "\n";
    }
}


# oef 1 - 5
sub bind_object {
   # provider://[server | domein [:poort]/]distinguishedName
    my $parameter = shift;
    my $moniker, my $object;
    # |!| INLOGPROCEDURE    
    # thuis  : 193.190.126.71
    # school : 192.168.16.16
    my $ip = "193.190.126.71";
    $moniker = "LDAP://$ip/" . $parameter; 
    my $login = "Bert De Saffel";
    my $pass = "Bert De Saffel";

    my $dso = Win32::OLE->GetObject("LDAP:");
    $object = $dso->openDSObject($moniker, $login , $pass, $ADS_AUTHENTICATION_ENUM{ADS_SECURE_AUTHENTICATION});
    
  #  print Win32::OLE->LastError() if Win32::OLE->LastError();
    return $object;
}
