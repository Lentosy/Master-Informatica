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
# perl reeks6.pl oefnr arg1 arg2 ... argn

my $oefnr = $ARGV[0] or die "geef oefeningnummer op";
"oef$oefnr"->();

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
    
    print Win32::OLE->LastError() if Win32::OLE->LastError();
    return $object;
}


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
    my @attributen = qw(dnshostname ldapservicename currenttime isglobalcatalogready issynchronized servername defaultnamingcontext configurationnamingcontext schemanamingcontext forestfunctionality domainfunctionality);
    print_attributen($root, @attributen);

    print "\nOphalen object, met behulp van het attribuut 'defaultNamingContext' van RootDSE:\n";
    my $object = bind_object("CN=Administrator,CN=Users,$root->{defaultNamingContext}");
    @attributen = qw(adspath class guid name parent schema);
    print_attributen($object, @attributen);
}

sub oef13 {
    (my $root = bind_object('RootDSE'))->GetInfo();
    my @attributen = qw(name class guid adspath parent schema defaultnamingcontext dnshostname);
    print_attributen($root, @attributen);
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

    for (1 .. $#ARGV){
        overloop_recursief(bind_object($root->{$containers[$_]}), \%klassenfrequentie);
    }
    print_frequentiehash_geordend(\%klassenfrequentie);
}

sub oef21 {
    (my $root = bind_object('RootDSE'))->GetInfo(); # GetInfo om propertycache te initialiseren 
    my $domein = $root->{defaultnamingcontext};
    my $administrator = bind_object("CN=Administrator,CN=Users,$domein");
    my @attributen = qw(accountdisabled accountexpirationdate badlogincount department description division emailaddress employeeid faxnumber firstname fullname homedirectory homepage isaccountlocked languages lastfailedlogin lastlogin lastlogoff lastname loginscript manager maxstorage nameprefix namesuffix officelocations othername passwordlastchanged passwordrequired picture postalcodes profile telephonehome telephonemobile telephonenumber telephonepager title);
    print_attributen($administrator, @attributen);
}

sub oef22 {
    # werkt enkel op VM of labotoestel
    use Win32::OLE::Const;
    my %constants = %{Win32::OLE::Const->Load('Active DS Type Library')};
    for my $key (keys %constants){
        print "$key => $constants{$key}\n" if $key =~ /_UF_/;
    }

}

sub oef23 {
    (my $root = bind_object('RootDSE'))->GetInfo(); # GetInfo om propertycache te initialiseren 
    my $domein = $root->{defaultnamingcontext};
    my $gebruikers = bind_object("CN=Users,$domein");
    for my $gebruiker (in $gebruikers){
        printf "%50s : ", $gebruiker->{cn};
        my $useraccountcontrol = $gebruiker->{UserAccountControl};
        if($useraccountcontrol){
            my @text = ();
            if($useraccountcontrol & $ADS_USER_FLAG_ENUM{ADS_UF_ACCOUNTDISABLE}){
                push @text, "Account disabled";
            }
            if($useraccountcontrol & $ADS_USER_FLAG_ENUM{ADS_UF_PASSWD_NOTREQD}){
                push @text,"Geen paswoord vereist";
            }
            print join " | ", @text;
        }
        print "\n";     
    }
}

sub oef24 {
    (my $root = bind_object('RootDSE'))->GetInfo();
    my @attributen = qw(name class guid adspath parent schema defaultnamingcontext dnshostname);
    print_attributen($root, @attributen);
}

sub oef25 {
    my $root = bind_object('RootDSE');
    my $domein = $root->Get("defaultnamingcontext");
    my $object = bind_object("OU=iii,$domein");

    printf "\n\nEerste poging - geeft geen fout, maar ook geen waarde  \ncanonicalName = %s\n",$object->{canonicalName};
    printf "\nFout:%s", Win32::OLE->LastError();

    printf "\n\nTweede poging  \ncanonicalName = %s\n",@{$object->getEx("canonicalName")};
    printf "\nFout:%s", Win32::OLE->LastError(); #resulteert in de fout 0x8000500D

    $object->getInfo();
    printf "\n\nDerde poging  \ncanonicalName = %s\n",@{$object->getEx("canonicalName")};
    printf "\nFout:%s", Win32::OLE->LastError();

    $object->GetInfoEx(["canonicalName"],0);
    printf "\n\nVierde poging  \ncanonicalName = %s\n",@{$object->getEx("canonicalName")};
}

sub oef26 {
    print "Geen implementatie";
}

sub oef27 {
    my $root = bind_object('RootDSE');
    my @attributen=qw(accountNameHistory aCSPolicyName adminCount adminDescription adminDisplayName allowedAttributes allowedAttributesEffective allowedChildClasses allowedChildClassesEffective altSecurityIdentities assistant badPwdCount bridgeheadServerListBL c canonicalName cn co codePage comment company countryCode createTimeStamp defaultClassStore department description desktopProfile destinationIndicator directReports displayName displayNamePrintable distinguishedName division dSCorePropagationData dynamicLDAPServer employeeID extensionName facsimileTelephoneNumber flags fromEntry frsComputerReferenceBL fRSMemberReferenceBL fSMORoleOwner garbageCollPeriod generationQualifier givenName groupPriority groupsToIgnore homeDirectory homeDrive homePhone homePostalAddress info initials instanceType internationalISDNNumber ipPhone isCriticalSystemObject isDeleted isPrivilegeHolder l lastKnownParent legacyExchangeDN localeID logonCount mail managedObjects manager masteredBy memberOf mhsORAddress middleName mobile modifyTimeStamp mS-DS-ConsistencyChildCount msNPAllowDialin msNPCallingStationID msNPSavedCallingStationID msRADIUSCallbackNumber msRADIUSFramedIPAddress msRADIUSFramedRoute msRADIUSServiceType msRASSavedCallbackNumber msRASSavedFramedIPAddress msRASSavedFramedRoute name netbootSCPBL networkAddress nonSecurityMemberBL o objectCategory objectClass objectVersion operatorCount otherFacsimileTelephoneNumber otherHomePhone otherIpPhone otherLoginWorkstations otherMailbox otherMobile otherPager otherTelephone otherWellKnownObjects ou pager personalTitle physicalDeliveryOfficeName postalAddress postalCode postOfficeBox preferredDeliveryMethod preferredOU primaryGroupID primaryInternationalISDNNumber primaryTelexNumber profilePath proxiedObjectName proxyAddresses queryPolicyBL revision rid sAMAccountName sAMAccountType scriptPath sDRightsEffective seeAlso serverReferenceBL servicePrincipalName showInAddressBook showInAdvancedViewOnly siteObjectBL sn st street streetAddress subRefs subSchemaSubEntry systemFlags telephoneNumber textEncodedORAddress title url userAccountControl userParameters userPrincipalName userSharedFolder userSharedFolderOther userWorkstations USNIntersite wbemPath wellKnownObjects whenChanged whenCreated wWWHomePage x121Address);

    print_attributen(bind_object("CN=Administrator,CN=Users,". $root->get("defaultNamingContext")), @attributen);
}

sub oef28 {
    my $root = bind_object('RootDSE');
    my $domein = $root->Get("defaultnamingcontext");
    my $container = bind_object("OU=Studenten,OU=iii,$domein");
    $container->{Filter} = ["organizationalUnit"];
    my @attributen = qw(ou msDS-Approx-Immed-Subordinates);
    
    for my $subcontainer(in $container){
        $subcontainer->GetInfoEx(\@attributen, 0);
        printf "%20s: %s\n", $subcontainer->{ou}, $subcontainer->{"msDS-Approx-Immed-Subordinates"};
    }
}

sub oef29 {
    my $root = bind_object("RootDSE");
    my $domein = $root->get("defaultnamingcontext");
    my $cont = bind_object("OU=Studenten,OU=iii,$domein");

    print $cont->{PropertyCount}, " properties in Property Cache, omdat geen GetInfo of GetInfoEx aangeroepen werd\n";
    $cont->getInfo();
    print $cont->{PropertyCount}, " properties in Property Cache, omdat de meeste attributen door GetInfo gecached wordt\n";
    $cont->getInfoEx(["ou","canonicalName","msDS-Approx-Immed-Subordinates","objectclass"],0);
    print $cont->{PropertyCount}, " properties in Property Cache, omdat er 4 extra attributen gecached worden, waarvan er 3 niet door GetInfo gecached worden.\n";
}

sub oef30 {
    my $root = bind_object('RootDSE');
    my $domein = $root->Get("defaultnamingcontext");
    my $administrator = bind_object("CN=Administrator,CN=Users,$domein");
    print_alle_ingestelde_attributen($administrator);
}

sub oef31 {
    my $usernaam = $ARGV[1] or die "Geef usernaam op";
    my $LDAPattribuut = $ARGV[2] or die "Geef ldap-attribuut op";
    my $root = bind_object('RootDSE');
    my $domein = $root->Get("defaultnamingcontext");

    my $cont = bind_object("OU=EM7INF,OU=Studenten,OU=iii,$domein");
    my $user = $cont->GetObject('user', "cn=$usernaam");

    unless ($user){
        $cont = bind_object("OU=Docenten,OU=iii,$domein");
        $user = $cont->GetObject('user', "cn=$usernaam");
    }

    unless ($user){
        die "User $usernaam niet gevonden\n";
    }

    $user->GetInfoEx([$LDAPattribuut], 0); 
    print_property_entry($user->Next()); # omdat enkel het opgegeven LDAP attribuut opgevraagd word, zal Next sowieso dit attribuut hebben
}

sub oef32 {
    print 'Geen implementatie';
}
sub oef33 {
   my $root = bind_object('RootDSE');
   my $schema = bind_object($root->Get("schemanamingcontext"));
   my %klassen = ();
   for(in $schema){
       $klassen{$_->{class}}++;
   }

   print_frequentiehash_geordend(\%klassen);
}
sub oef34 {
    # klasse is hulpklasse: objectClassCategory = 3
    # objectClass
    my $root = bind_object('RootDSE');
    my $schema = bind_object($root->Get("schemanamingcontext"));
    $schema->{Filter} = ["classSchema"];
    my $topkind         = 0;
    my $auxiliary       = 0;
    my $hulpafhankelijk = 0;
    my $microsoft       = 0;
    my $systemonly      = 0;
    my $RDNnotCN        = 0;

    $schema->{Filter} = ["classSchema"]; #enkel klassen

    foreach my $klasse ( in $schema ) {
        $topkind++         if $klasse->{subClassOf} eq "top";
        $auxiliary++       if $klasse->{objectClassCategory} == 3;
        $hulpafhankelijk++ if ( defined( $klasse->{systemAuxiliaryClass} )
                            || defined( $klasse->{AuxiliaryClass} ) );
        $microsoft++       if substr( $klasse->{governsID}, 0, 15 ) eq "1.2.840.113556."; #vind je ook terug in de AD Library bij governsId
        $systemonly++      if $klasse->{systemOnly};
        $RDNnotCN++        if $klasse->{rdnAttID} ne "cn";
    }

    print "\nKinderen van top             : " , $topkind;
    print "\nHulpklassen                  : " , $auxiliary;
    print "\nAfhankelijk van hulpklasse(n): " , $hulpafhankelijk;
    print "\nActive Directory specifiek   : " , $microsoft;
    print "\nKunnen niet gewijzigd worden : " , $systemonly;
    print "\nRDN niet van de vorm CN=...  : " , $RDNnotCN;


}
sub oef35 {
    my $rootDSE = bind_object("rootDSE");
    my $schema  = bind_object( $rootDSE->Get("schemaNamingContext") );

    my $multivalued   = 0;
    my $catalog       = 0;
    my $geindexeerd   = 0;
    my $gerepliceerd  = 0;
    my $geconstrueerd = 0;
    my $limited       = 0;
    my $microsoft     = 0;
    my $systemonly    = 0;

    $schema->{Filter} = ["attributeSchema"];

    foreach my $attribuut ( in $schema ){
        $multivalued++    unless $attribuut->{isSingleValued};
        $catalog++        if $attribuut->{isMemberOfPartialAttributeSet};
        $geindexeerd++    if $attribuut->{searchflags} & 1;
        $gerepliceerd++   if $attribuut->{systemFlags} & 1;
        $geconstrueerd++  if $attribuut->{systemFlags} & 4;
        $limited++        if ( defined( $attribuut->{rangeLower} )
                            || defined( $attribuut->{rangeUpper} ) );
        $microsoft++      if substr( $attribuut->{attributeID}, 0, 15 ) eq "1.2.840.113556.";
        $systemonly++     if $attribuut->{systemOnly};
    }

    print "\nZijn multivalued                      : " , $multivalued;
    print "\nWorden opgenomen in de Global Catalog : " , $catalog;
    print "\nWorden geindexeerd                    : " , $geindexeerd;
    print "\nWorden niet gerepliceerd              : " , $gerepliceerd;
    print "\nWorden geconstrueerd                  : " , $geconstrueerd;
    print "\nHebben waarden met beperking op bereik: " , $limited;
    print "\nActive Directory specifiek            : " , $microsoft;
    print "\nKunnen niet gewijzigd worden          : " , $systemonly;
}
sub oef36 {
    my $root = bind_object('RootDSE');
    my $schema = bind_object($root->Get("schemanamingcontext"));
    $schema->{Filter} = ["attributeSchema"];

    my @geconstrueerd;
    my @onwijzigbaar;
    for (in $schema){
        if($_->{SystemFlags} && $_->{SystemFlags} & $ADS_SYSTEMFLAG_ENUM{ADS_SYSTEMFLAG_ATTR_IS_CONSTRUCTED}){
            push @geconstrueerd, $_->{ldapdisplayname};
        }

        if($_->{SystemOnly}){
            push @onwijzigbaar, $_->{ldapdisplayname};
        }
    }
    print "Geconstrueerde attributen: ";
    print join "-", @geconstrueerd;
    print "\n\nOnwijzigbare attributen : ";
    print join "-", @onwijzigbaar;
}
sub oef37 {
    print 'Geen implementatie';
}
sub oef38 {
    my $abstractschema = bind_object("schema");
    my %klassen = ();
    for(in $abstractschema){
        $klassen{$_->{class}}++;
    }

    print_frequentiehash_geordend(\%klassen);
}
sub oef39 {
    my $ldapdisplayname = $ARGV[1] or die "Geef ldapDisplayName";
    my $schema = bind_object("schema/$ldapdisplayname");
    my @attributen = qw(adspath class guid name parent schema);
    print_attributen($schema, @attributen);
}
sub oef40 {
    my $ldapdisplayname = $ARGV[1] or die "Geef ldapDisplayName";
    my $abstractschema = bind_object("schema/$ldapdisplayname");
    my @attributen = qw(oid auxderivedfrom abstract auxiliary possiblesuperiors mandatoryproperties optionalproperties container containment);
    print_attributen($abstractschema, @attributen);
}
sub oef41 {
    my $root = bind_object('RootDSE');
    my $domein = $root->Get("defaultnamingcontext");
    my $administrator = bind_object("CN=Administrator,CN=Users,$domein");
    my $abstractschema = bind_object($administrator->{Schema});

    #invullen property cache
    $administrator->GetInfoEx($abstractschema->{MandatoryProperties}, 0);
    $administrator->GetInfoEx($abstractschema->{optionalproperties}, 0);

    for my $attribuut (in $abstractschema->{MandatoryProperties}, $abstractschema->{optionalproperties}) {
        my $abstractattribuut = bind_object("schema/$attribuut");
        my $waarden = $administrator->GetEx($attribuut);

        print join "-", @$waarden;
    }

}
sub oef42 {
    print 'Geen implementatie';
}


# Een hash uitprinten, gesorteerd op de values
sub print_frequentiehash_geordend {
    my $hash = shift;
    for my $key (sort { $hash->{$a} <=> $hash->{$b} } keys %{$hash}){
        printf "%30s => %s\n", $key, $hash->{$key};
    }
}

sub print_alle_ingestelde_attributen {
    my $obj = shift;
    $obj->GetInfo();
    while(my $attribuut = $obj->Next()){
        print_property_entry($attribuut);
    }
}

sub print_property_entry {
    my $attribuut = shift;
    my $adstype = $attribuut->{ADsType};
    printf "%30s : ", $attribuut->{Name} . " (" . $adstype . ")";
    for my $waarde( @{$attribuut->{Values}}){
        if($adstype == $ADS_TYPE_ENUM{ADS_TYPE_OCTET_STRING}) {
            print sprintf "%*v02X", "", $waarde->GetObjectProperty($adstype);
        } elsif ($adstype == $ADS_TYPE_ENUM{ADS_TYPE_NT_SECURITY_DESCRIPTOR}){
            print "eigenaar is ... " . $waarde->GetObjectProperty($adstype)->{Owner};
        } elsif ($adstype == $ADS_TYPE_ENUM{ADS_TYPE_LARGE_INTEGER}){
            print bigint_to_string($waarde->GetObjectProperty($adstype)->{HighPart}, $waarde->GetObjectProperty($adstype)->{LowPart})
        } else {
            print $waarde->GetObjectProperty($adstype);
        }     
        print " | ";
    }
    print "\n";
}

sub print_attributen {
    my $obj = shift;
    my @attributen = @_;
    $obj->GetInfoEx(\@attributen, 0);
    unless(Win32::OLE->LastError() == $E_ADS{NOTIMPL}){
        for my $attribuut (@attributen){
            printf "%30s : ", $attribuut;
            my $waarden = $obj->GetEx($attribuut);
            if(Win32::OLE->LastError() == $E_ADS{PROPERTY_NOT_FOUND}){
                print "(geen waarde)\n";
                next; # volgend attribuut
            }
            if(scalar @{$waarden} == 1){
                print $waarden->[0];
            } else {
                print '(' . scalar @{$waarden} . ') ';
                print '[';
                print join '|', @{$waarden};
                print ']';
            }
    
            print "\n";
        }
    } else { # andere manier om te schrijven nodig
        for my $attribuut (@attributen){
            printf "%30s : ", $attribuut;
            if(ref $obj->{$attribuut} eq "ARRAY"){
                print '(' . scalar @{$obj->{$attribuut}} . ') ';
                print '[';
                print join '|', @{$obj->{$attribuut}};
                print ']';
            } else {
                print $obj->{$attribuut};
            }
            
            print "\n";
        }
    }

}

sub bigint_to_string {
    my $high = Math::BigInt->new(shift);
    my $low = Math::BigInt->new(shift);
    my $radix = Math::BigInt->new('0x10000000'); # 2^32
    $low += $radix if $low < 0;
    return $high * $radix + $low;
}

