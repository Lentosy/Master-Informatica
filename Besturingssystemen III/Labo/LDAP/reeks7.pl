# Op het examen moet je inloggen met je eigen credentials. De code die hiervoor nodig is taat in de bind_object subroutine, gemarkeerd met |!|
# Op het examen wordt dan ook het ip-adres gegeven, waarschijnlijk 192.168.16.16

use strict;
no strict 'refs'; # zodat ik een subroutine mag uitvoeren op basis van een string. Anders moet ik per oefening een verwijzing maken naar een subroutine
use warnings;

use Math::BigInt;

use Win32::OLE qw(in);
use Win32::OLE::Variant;
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
    print "Geen implementatie";
}

sub oef10 {
    print "Geen implementatie";
}

sub oef11 {
    print "Geen implementatie";
}

sub oef12 {
    print "Geen implementatie";
}

sub oef13 {
    print "Geen implementatie";
}

sub oef14 {
    print "Geen implementatie";
}

sub oef15 {
    print "Geen implementatie";
}

sub oef16 {
    print "Geen implementatie"; 
}

sub oef17 {
    print "Geen implementatie";
}

sub oef18 {
    print "Geen implementatie";
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
    my $padding = -1;
    for(split ',', shift){
        if(length $_ > $padding) {
            $padding = length $_; 
        }
    }
    return $padding;
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
    
    print $resultset->{RecordCount}, " AD-objecten\n";
    print $resultset->{Fields}->{Count}, " LDAP attributen opgehaald per AD-object\n";
    until($resultset->{EOF}){
        for (in $resultset->{Fields}){
            printf "%${padding}s : ", $_->{Name};
            my $waarde = $_->{Value};
            if($_->{Type} == 204){
                printf "%*v02X", "", $waarde;
            } elsif (ref $waarde eq "ARRAY") {
                print join "|", $waarde;
            } else {
                print $waarde;
            }  
            print "\n";
        }
        print "\n";
        $resultset->MoveNext();
    }
}