# Op het examen moet je inloggen met je eigen credentials. De code die hiervoor nodig is taat in de bind_object subroutine, gemarkeerd met |!|
# Op het examen wordt dan ook het ip-adres gegeven, waarschijnlijk 192.168.16.16

use strict;
no strict 'refs'; # zodat ik een subroutine mag uitvoeren op basis van een string. Anders moet ik per oefening een verwijzing maken naar een subroutine
use warnings;

use Math::BigInt;

use Win32::OLE qw(in);
use Win32::OLE::Variant;
Win32::OLE->Option(Warn => 3);
#use Win32::OLE::Const 'Active DS Type Library'; 

# als je niet op de VM werkt kan je natuurlijk de constanten van 'Active DS Type Library' niet inladen
# daarom voorzie ik volgende hashes, enkel aangevuld met constanten die nodig zijn in de oefeningen:

# ms-help://MS.MSDNQTR.v90.en/adsi/adsi/ads_authentication_enum.htm
my %ADS_AUTHENTICATION_ENUM = 
    (
        ADS_SECURE_AUTHENTICATION => 0x1
    );

# ms-help://MS.MSDNQTR.v90.en/adsi/adsi/ads_user_flag_enum.htm
my %ADS_USER_FLAG_ENUM = 
    (
        ADS_UF_ACCOUNTDISABLE => 0x2,
        ADS_UF_PASSWD_NOTREQD => 0x20
    );

# ms-help://MS.MSDNQTR.v90.en/adsi/adsi/ads_property_operation_enum.htm
my %ADS_PROPERTY_OPERATION_ENUM = 
    (
        ADS_PROPERTY_CLEAR => 1,
        ADS_PROPERTY_UPDATE => 2,
        ADS_PROPERTY_UPDATE => 3,
        ADS_PROPERTY_DELETE => 4
    );

my %E_ADS = (
        NOTIMPL                 => Win32::OLE::HRESULT(0x80004001),
        BAD_PATHNAME            => Win32::OLE::HRESULT(0x80005000),
        UNKNOWN_OBJECT          => Win32::OLE::HRESULT(0x80005004),
        PROPERTY_NOT_SET        => Win32::OLE::HRESULT(0x80005005),
        PROPERTY_INVALID        => Win32::OLE::HRESULT(0x80005007),
        BAD_PARAMETER           => Win32::OLE::HRESULT(0x80005008),
        OBJECT_UNBOUND          => Win32::OLE::HRESULT(0x80005009),
        PROPERTY_MODIFIED       => Win32::OLE::HRESULT(0x8000500B),
        OBJECT_EXISTS           => Win32::OLE::HRESULT(0x8000500E),
        SCHEMA_VIOLATION        => Win32::OLE::HRESULT(0x8000500F),
        COLUMN_NOT_SET          => Win32::OLE::HRESULT(0x80005010),
        ERRORSOCCURRED          => Win32::OLE::HRESULT(0x00005011),
        NOMORE_ROWS             => Win32::OLE::HRESULT(0x00005012),
        NOMORE_COLUMNS          => Win32::OLE::HRESULT(0x00005013),
        INVALID_FILTER          => Win32::OLE::HRESULT(0x80005014),
        INVALID_DOMAIN_OBJECT   => Win32::OLE::HRESULT(0x80005001),
        INVALID_USER_OBJECT     => Win32::OLE::HRESULT(0x80005002),
        INVALID_COMPUTER_OBJECT => Win32::OLE::HRESULT(0x80005003),
        PROPERTY_NOT_SUPPORTED  => Win32::OLE::HRESULT(0x80005006),
        PROPERTY_NOT_MODIFIED   => Win32::OLE::HRESULT(0x8000500A),
        CANT_CONVERT_DATATYPE   => Win32::OLE::HRESULT(0x8000500C),
        PROPERTY_NOT_FOUND      => Win32::OLE::HRESULT(0x8000500D) 
    );

# ms-help://MS.MSDNQTR.v90.en/adsi/adsi/adstypeenum.htm
my %ADS_TYPE_ENUM = 
    (
        ADS_TYPE_DN_STRING => 1,
        ADS_TYPE_CASE_EXACT_STRING => 2,
        ADS_TYPE_CASE_IGNORE_STRING => 3,
        ADS_TYPE_PRINTABLE_STRING => 4,
        ADS_TYPE_NUMERIC_STRING => 5,
        ADS_TYPE_BOOLEAN => 6,
        ADS_TYPE_INTEGER => 7,
        ADS_TYPE_OCTET_STRING => 8,
        ADS_TYPE_UTC_TIME => 9,
        ADS_TYPE_LARGE_INTEGER => 10,
        ADS_TYPE_NT_SECURITY_DESCRIPTOR => 25,
        ADS_TYPE_DN_WITH_BINARY => 27,
        ADS_TYPE_DN_WITH_STRING => 2
    );

# ms-help://MS.MSDNQTR.v90.en/adsi/adsi/ads_systemflag_enum.htm
my %ADS_SYSTEMFLAG_ENUM = 
    (
        ADS_SYSTEMFLAG_ATTR_IS_CONSTRUCTED => 0x00000004
    );


## STRUCTUUR VAN DIT BESTAND 
# Elke oefening krijgt zijn eigen subroutine, die op zijn beurt andere, globale subroutines kan aanroepen. 
# Met een globale subroutine bedoel ik subroutines die niet specifiek zijn voor een oefening, behalve de bind_object methode van oef 1 tot oef 5.
# Het bestand uitvoeren:
# perl reeks7.pl oefnr arg1 arg2 ... argn

my $oefnr = $ARGV[0] or die "geef oefeningnummer op";
die "$oefnr is geen getal" if $oefnr =~ /\D/;

"oef$oefnr"->();




sub oefinleiding {
    my $root = bind_object("RootDSE");
    my $domein = bind_object($root->Get("defaultnamingcontext"));
    my $base = $domein->{adspath};
    my $filter = "(&(objectCategory=printQueue)(printColor=TRUE)(printDuplexSupported=TRUE))";
    my $attributen = 'printerName,printRate,printMaxResolutionSupported,printMaxResolutionSupported,printStaplingSupported,';
    my $scope = "subtree";
    my $command = get_command();
    $command->{CommandText} = "<$base>;$filter;$attributen;$scope";
    $command->{Properties}->{"Sort On"} = "printerName"; 

    my $resultset = $command->Execute();
    print_resultset($resultset, geef_lengte_langste_attribuutnaam($attributen));
    $resultset->Close();
    close_command($command);
}

sub oef6 {
    my $root = bind_object('RootDSE');
    my $domein = bind_object($root->Get("defaultnamingcontext"));
    my $base = $domein->{adspath};
    my $filter = '(name=Bert*)';
    my $attributen = 'name';
    my $scope = 'subtree';
    my $command = get_command();
    $command->{CommandText} = "<$base>;$filter;$attributen;$scope";
    my $resultset = $command->Execute();
    print_resultset($resultset, geef_lengte_langste_attribuutnaam($attributen));
    $resultset->Close();
    close_command($command);
}

sub oef7 {
    my $postcode = $ARGV[1] or die "Geef postcode op";
    my $root = bind_object('RootDSE');
    my $domein = bind_object("OU=studenten,OU=iii," . $root->Get("defaultnamingcontext"));
    my $base = $domein->{adspath};
    my $filter = "(&(objectCategory=person)(objectClass=user)(postalCode=$postcode))";
    my $attributen = 'name,streetAddress,l';
    my $scope = 'subtree';
    my $command = get_command();
    $command->{CommandText} = "<$base>;$filter;$attributen;$scope";
    $command->{Properties}->{"Sort On"} = 'l';
    my $resultset = $command->Execute();
    print_resultset($resultset, geef_lengte_langste_attribuutnaam($attributen));
    $resultset->Close();
    close_command($command);
}

sub oef8 {
    my $root = bind_object('RootDSE');
    my $domein = bind_object($root->Get("defaultnamingcontext"));
    my $base = $domein->{adspath};
    my $filter = "(objectclass=user)";
    my $attributen = '*';
    my $scope = 'subtree';
    my $command = get_command();
    $command->{CommandText} = "<$base>;$filter;$attributen;$scope";
    $command->{Properties}->{"Sort On"} = 'cn';
    my $resultset = $command->Execute();
    print_resultset($resultset, geef_lengte_langste_attribuutnaam($attributen));
    $resultset->Close();
    close_command($command);
}

sub oef9 {
    my $ldapattribuut = $ARGV[1] or die "geef LDAP attribuut op";
    my $base = (bind_object(bind_object('RootDSE')->Get("defaultnamingcontext")))->{adspath};
    my $filter = "($ldapattribuut=*)";
    my $attributen = 'objectClass';
    my $scope = 'subtree';
    my $command = get_command();
    $command->{CommandText} = "<$base>;$filter;$attributen;$scope";
    my $resultset = $command->Execute();
    my %classes;
    until($resultset->{EOF}){
        $classes{($resultset->Fields('objectClass')->{Value})->[-1]}++;
        $resultset->MoveNext();
    }
    $resultset->Close();
    close_command($command);
    print "Volgende klassen hebben minstens 1 AD-object waarvan $ldapattribuut is ingesteld:\n";
    print_frequentiehash_geordend(\%classes);

}

sub oef10 {
    my $base = (bind_object("OU=PC's,OU=iii," . bind_object('RootDSE')->Get("defaultnamingcontext")))->{adspath};
    my $filter = "(cn=*A)";
    my $attributen = 'canonicalName';
    my $scope = 'subtree';
    my $command = get_command();
    $command->{Commandtext} = "<$base>;$filter;$attributen;$scope";
    my $resultset = $command->Execute();
    print_resultset($resultset, geef_lengte_langste_attribuutnaam($attributen));
    $resultset->Close();
    close_command($command);
}

sub oef11 {
    my $root = bind_object('RootDSE');
    my $domein = $root->Get("defaultnamingcontext");
    my $student = bind_object("CN=Bert De Saffel,OU=EM7INF,OU=Studenten,OU=iii,$domein");
    my $primarygroup = $student->{PrimaryGroupID};

    my $base = bind_object($domein)->{adspath};
    my $filter = "(objectclass=group)";
    my $attributen = 'cn,primaryGrouptoken';
    my $scope = 'subtree';
    my $command = get_command();
    $command->{Commandtext} = "<$base>;$filter;$attributen;$scope";
    my $resultset = $command->Execute();
    while(!$resultset->{EOF} && $resultset->Fields('primaryGrouptoken')->{Value} != $primarygroup){
        $resultset->MoveNext();
    }
    print "Primare group van Bert De Saffel is: " . $resultset->Fields('cn')->{Value} . " (id: $primarygroup)\n" ;
    $resultset->Close();
    close_command($command);
}

sub oef12 {
    my $root = bind_object('RootDSE');
    my $configuration = $root->Get("configurationnamingcontext"); # <-------
    my $student = bind_object("CN=Bert De Saffel,OU=EM7INF,OU=Studenten,OU=iii,$configuration");
    my $primarygroup = $student->{PrimaryGroupID};

    my $base = bind_object($configuration)->{adspath};
    my $filter = "(fromServer=be)"; # <-------
    my $attributen = 'cn,primaryGrouptoken';
    my $scope = 'subtree';
    my $command = get_command();
    $command->{Commandtext} = "<$base>;$filter;$attributen;$scope";
    my $resultset = $command->Execute();
    while(!$resultset->{EOF} && $resultset->Fields('primaryGrouptoken')->{Value} != $primarygroup){
        $resultset->MoveNext();
    }
    print "Primare group van Bert De Saffel is: " . $resultset->Fields('cn')->{Value} . " (id: $primarygroup)\n" ;
    $resultset->Close();
    close_command($command);
}

sub oef13 {
    my $root = bind_object('RootDSE');
    my $schema = bind_object($root->Get('schemanamingcontext'));
    my $base = $schema->{adspath};
    my $filter = "(&(objectClass=classSchema)(!(objectClassCategory=1)))";
    my $attributen = "cn,objectClassCategory";
    my $scope = 'subtree';
    my $command = get_command();
    $command->{CommandText} = "<$base>;$filter;$attributen;$scope";
    my $resultset = $command->Execute();
    print "Abstracte klassen: \n";
    while(!$resultset->{EOF}){
        if($resultset->Fields('objectClassCategory')->{Value} % 2 == 0){ # 0 of 2 zal 0 geven
            printf "\t%s\n", $resultset->Fields('cn')->{Value};
        }
        $resultset->MoveNext();
    }

    $resultset->MoveFirst();
    print "Hulpklassen: \n";
    while(!$resultset->{EOF}){
        if($resultset->Fields('objectClassCategory')->{Value} == 3){ 
            printf "\t%s\n", $resultset->Fields('cn')->{Value};
        }
        $resultset->MoveNext();
    }
    
    $resultset->Close();
    close_command($command);
}

sub oef14 {
    my $ldapdisplayname = $ARGV[1] or die "Geef LDAP attribuut op";
    my $attribuut = bind_object("schema/$ldapdisplayname");
    print $attribuut->Get("cn");
    
}

sub oef15 {
    # searchFlags: laagste bit = indexering
    # systemFlags: laagste bit = replicatie
    # systemFlags: derde laagste bit = geconstrueerd attribuut 

    my $root = bind_object('RootDSE');
    my $schema = bind_object($root->Get("schemanamingcontext"));
    my $base = $schema->{adspath};
    my $filter = "(|(searchFlags:1.2.840.113556.1.4.803:=1)(systemFlags:1.2.840.113556.1.4.804:=5))";
    my $attributen = 'cn,searchFlags,systemFlags';
    my $scope = 'subtree';
    my $command = get_command();
    $command->{Commandtext} = "<$base>;$filter;$attributen;$scope";
    $command->{Properties}->{"Sort On"} = 'cn';
    my $resultset = $command->Execute();

    print_resultset($resultset, geef_lengte_langste_attribuutnaam($attributen));
    $resultset->Close();
    close_command($command);
}

sub oef16 {
    my $groep = $ARGV[1] or die "Geef cn van groep op";
    my $root = bind_object('RootDSE');
    $root->GetInfo();
    my $domein = bind_object($root->Get('defaultNamingContext'));
    my $base = $domein->{adspath};
    my $filter = "(cn=$groep)";
    my $attributen = "distinguishedName";
    my $scope = 'subtree';
    
    # get_command niet oproepen => moet gebruik maken van account Interim F
    my $connection = Win32::OLE->new("ADODB.Connection");
    $connection->{Provider} = "ADsDSOObject";
    $connection->{Properties}->{"User ID"} = "Interim F";
    $connection->{Properties}->{"Password"} = "Interim F";
    $connection->{Properties}->{"Encrypt Password"} = 1;
    $connection->Open();
    my $command = Win32::OLE->new("ADODB.Command");
    $command->{ActiveConnection} = $connection;
    $command->{Properties}->{"Page Size"} = 20;

    $command->{CommandText} = "<$base>;$filter;$attributen;$scope";
    print  $command->{CommandText} ;
    my $resultset = $command->Execute();
    if($resultset->{RecordCount} == 0){
        die "$groep bestaat niet \n";
    }
    my $distinguishedname = $resultset->Fields('distinguishedName')->{Value};
    printf "Groep: %s\n", $distinguishedname;
    $filter = "(memberof:1.2.840.113556.1.4.1941:=$distinguishedname)";
    $attributen = 'cn,description,distinguishedname';
    $command->{CommandText} = "<$base>;$filter;$attributen;$scope";
    $resultset = $command->Execute();
    print_resultset($resultset, geef_lengte_langste_attribuutnaam($attributen));

    $resultset->Close();
    close_command($command);

}

sub oef17 {
    my $root = bind_object('RootDSE');
    my $schema = bind_object($root->Get("schemanamingcontext"));

    my $base = $schema->{adspath};
    my $filter = "(&(objectCategory=attributeSchema)(linkID=*)(!(linkID:1.2.840.113556.1.4.804:=1)))";
    my $attributen = "ldapdisplayname,linkID";
    my $scope = "subtree";

    my $command = get_command();
    $command->{CommandText} = "<$base>;$filter;$attributen;$scope";
    $command->{Properties}->{"Sort On"} = "linkID";

    my $forwardset = $command->Execute();
    until($forwardset->{EOF}){
        my $filter = sprintf "(&(objectCategory=attributeSchema)(linkID=%s))", $forwardset->Fields('linkID')->{Value};
        $command->{CommandText} = "<$base>;$filter;$attributen;$scope";
        my $backwardset = $command->Execute();
        until($backwardset->{EOF}){
            printf "%40s\t%s\n", $forwardset->Fields('ldapdisplayname')->{Value}, $backwardset->Fields('ldapdisplayname')->{Value};
            $backwardset->MoveNext();
        }

        $backwardset->Close();
        $forwardset->MoveNext();
    }
    $forwardset->Close();
    close_command($command);
}

sub oef18 {
    my @objectcategories = @ARGV[1 .. $#ARGV] or die "geef minstens één objectCategory (DnsNode, printQueue, person, computer, ...) mee";
    print join "-", @objectcategories;

    my $root = bind_object('RootDSE');
    my $domein = bind_object($root->Get("defaultnamingcontext"));

    my $base = $domein->{adspath};
    my $attributen = "adspath,cn,objectCategory,objectClass";
    my $scope = "subtree";
    my $padding = geef_lengte_langste_attribuutnaam($attributen);
    for my $category (@objectcategories){
        
        my $filter = "(objectCategory=$category)";


        my $command = get_command();
        $command->{Commandtext} = "<$base>;$filter;$attributen;$scope";

        my $resultset = $command->Execute();

        until($resultset->{EOF}){
            # custom code voor deze oefening
            my $object = bind_object(substr $resultset->Fields("adspath")->{Value}, 22, length $resultset->Fields("adspath")->{Value}); # omdat ik in bind_object zelf LDAP en het IP adres al toevoeg
            my $class = $object->{class};
            printf "%${padding}s : %s\n", "class", $class;
            # al de rest komt van de print_resultset methode
            for (in $resultset->{Fields}){
                printf "%${padding}s : ", $_->{Name};
                my $waarde = $_->{Value};
                if($waarde){
                    if($_->{Type} == 204){
                        printf "%*v02X", "", $waarde;
                    } elsif (ref $waarde eq "ARRAY") {
                        print join "|", @{$waarde};
                    } elsif ($_->{Name} eq "systemFlags" || $_->{Name} eq "searchFlags"){
                        printf "(%d) %b", $waarde, $waarde;
                    } else {
                        print $waarde;
                    }  
                } else {
                    print "(geen waarde)";
                }

                print "\n";
            }
            print "\n";
            $resultset->MoveNext();
        }
        $resultset->Close();
        close_command($command);
    }

    
}

sub oef19 {
    print "Geen implementatie";
}

sub oef20 {
    print "Geen implementatie";
}

sub oef21 {
    print "Geen implementatie";
}

sub oef22 {
    print "Geen implementatie";
}

sub oef23 {
    print "Geen implementatie";
}

sub get_command {
    my $connection = Win32::OLE->new("ADODB.Connection");
    $connection->{Provider} = "ADsDSOObject";
    $connection->{Properties}->{"User ID"} = "Bert De Saffel";
    $connection->{Properties}->{"Password"} = "Bert De Saffel";
    $connection->{Properties}->{"Encrypt Password"} = 1;
    $connection->Open();
    my $command = Win32::OLE->new("ADODB.Command");
    $command->{ActiveConnection} = $connection;
    $command->{Properties}->{"Page Size"} = 20;
    return $command;
}

sub close_command {
   shift->{ActiveConnection}->Close();
}

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
    
    print Win32::OLE->LastError() if Win32::OLE->LastError();
    return $object;
}

sub geef_lengte_langste_attribuutnaam {
    my $lengte = -1;
    for(split ',', shift){
        if(length $_ > $lengte) {
            $lengte = length $_; 
        }
    }
    return $lengte;
}

# Zal een resultset aflopen en elk record uitprinten
# Verwacht ook de lengte van het langste attribuut (aantal karakters)
#    => nodig om mooi te formatteren
sub print_resultset {
    if(Win32::OLE->LastError()){
        print Win32::OLE->LastError();
        return;
    }
    
    my $resultset = shift;
    my $padding = shift;
    
    # gewoon wa formatteren op basis of er 1 element of meer zijn
    $resultset->{RecordCount} == 1 
        ? print "1 AD-object\n" 
        : print $resultset->{RecordCount} . " AD-objecten\n";

    $resultset->{Fields}->{Count} == 1 
        ? print "1 LDAP attribuut opgehaald per AD-object\n" 
        : print $resultset->{Fields}->{Count} . " LDAP attributen opgehaald per AD-object\n";

    until($resultset->{EOF}){
        for (in $resultset->{Fields}){
            printf "%${padding}s : ", $_->{Name};
            my $waarde = $_->{Value};
            if($waarde){
                if($_->{Type} == 204){
                    printf "%*v02X", "", $waarde;
                } elsif (ref $waarde eq "ARRAY") {
                    print join "|", @{$waarde};
                } elsif ($_->{Name} eq "systemFlags" || $_->{Name} eq "searchFlags"){
                    printf "(%d) %b", $waarde, $waarde;
                } else {
                    print $waarde;
                }  
            } else {
                print "(geen waarde)";
            }

            print "\n";
        }
        print "\n";
        $resultset->MoveNext();
    }
}

# Een hash uitprinten, gesorteerd op de values
sub print_frequentiehash_geordend {
    my $hash = shift;
    for my $key (sort { $hash->{$b} <=> $hash->{$a} } keys %{$hash}){
        printf "%30s => %s\n", $key, $hash->{$key};
    }
}