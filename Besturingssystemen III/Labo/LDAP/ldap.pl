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
        ADS_PROPERTY_APPEND => 3,
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

my %ADS_GROUP_TYPE_ENUM = (
    ADS_GROUP_TYPE_GLOBAL_GROUP => 2,
    ADS_GROUP_TYPE_DOMAIN_LOCAL_GROUP => 4,
    ADS_GROUP_TYPE_UNIVERSAL_GROUP => 8,
    ADS_GROUP_TYPE_SECURITY_ENABLED => Win32::OLE::HRESULT(80000000)
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
# perl ldap.pl r<reeksnummer>_o<oefeningnumer> arg1 arg2 ... argn

my $oefnr = $ARGV[0] or die "geef reeks en oefeningnummer op in volgend formaat: r<reeksnummer>_o<oefeningnumer> [argumenten]";
"$oefnr"->();

# oef 1 - 5 reeks 6. Belangrijke methode
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

# dient voor groepering => kan ook dichtgeklapt worden text editor
sub reeks6 {
    sub r6_o6 {
    my $object = bind_object("CN=Satan,OU=Domain Controllers,DC=iii,DC=hogent,DC=be");
    my @attributen = qw(adspath class guid name parent schema);
    print_attributen($object, @attributen);
    }

    sub r6_o7 {
        my $object = bind_object("CN=Bert De Saffel,OU=EM7INF,OU=Studenten,OU=iii,DC=iii,DC=hogent,DC=be");
        my @attributen = qw(adspath mail);
        print_attributen($object, @attributen);
    }



    sub r6_o8 {
        my $object = bind_object("OU=EM7INF,OU=Studenten,OU=iii,DC=iii,DC=hogent,DC=be");
        my @attributen = qw(adspath guid class objectguid distinguishedname objectclass);
        print_attributen($object, @attributen);
    }

    sub r6_o9 {
        my $object = bind_object("CN=Bert De Saffel,OU=EM7INF,OU=Studenten,OU=iii,DC=iii,DC=hogent,DC=be");
        my @attributen = qw(mail givenname sn displayname homedirectory scriptpath profilepath logonhours userworkstations);
        print_attributen($object, @attributen);
    }

    sub r6_o10 {
        if(uc $ENV{USERDOMAIN} eq "III"){
            system("dsquery user- name \"Bert De Saffel\"");
            system("dsquery * \"CN=Bert De Saffel,OU=EM7INF,OU=Studenten,OU=iii,DC=iii,DC=hogent,DC=be\" -attr mail objectclass");
        } else {
            system("dsquery * \"CN=Bert De Saffel,OU=EM7INF,OU=Studenten,OU=iii,DC=iii,DC=hogent,DC=be\" -s 193.190.126.71 -u \"Bert De Saffel\" -p \"Bert De Saffel\" -attr mail objectclass");
        }
    }

    sub r6_o11 {
        print "Deze oefening moeten we niet kunnen\n";
    }

    sub r6_o12 {
        my $root = bind_object('RootDSE');
        my @attributen = qw(dnshostname ldapservicename currenttime isglobalcatalogready issynchronized servername defaultnamingcontext configurationnamingcontext schemanamingcontext forestfunctionality domainfunctionality);
        print_attributen($root, @attributen);

        print "\nOphalen object, met behulp van het attribuut 'defaultNamingContext' van RootDSE:\n";
        my $object = bind_object("CN=Administrator,CN=Users,$root->{defaultNamingContext}");
        @attributen = qw(adspath class guid name parent schema);
        print_attributen($object, @attributen);
    }

    sub r6_o13 {
        (my $root = bind_object('RootDSE'))->GetInfo();
        my @attributen = qw(name class guid adspath parent schema defaultnamingcontext dnshostname);
        print_attributen($root, @attributen);
    }

    sub r6_o14 {
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

    sub r6_o16 {
        my $lokaalID = $ARGV[1] or die "Geef lokaal op: 219 of 225";
        (my $root = bind_object('RootDSE'))->GetInfo(); # GetInfo om propertycache te initialiseren 
        my $domein = $root->{defaultnamingcontext};
        my $lokaal = bind_object("OU=$lokaalID,OU=PC's,OU=iii,$domein");
        for(in $lokaal){
            print $_->{distinguishedname} . "\n";
        }   
    }

    sub r6_o17 {
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

    sub r6_o18 {
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

    sub r6_o19 {
        (my $root = bind_object('RootDSE'))->GetInfo(); # GetInfo om propertycache te initialiseren 
        my @attributen = qw(defaultnamingcontext schemanamingcontext configurationnamingcontext namingcontexts);
        print_attributen($root, @attributen);
    }

    sub r6_o20 {
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


        overloop_recursief(bind_object($root->{$containers[1]}), \%klassenfrequentie);
        
        print_frequentiehash_geordend(\%klassenfrequentie);
    }

    sub r6_o21 {
        (my $root = bind_object('RootDSE'))->GetInfo(); # GetInfo om propertycache te initialiseren 
        my $domein = $root->{defaultnamingcontext};
        my $administrator = bind_object("CN=Administrator,CN=Users,$domein");
        my @attributen = qw(accountdisabled accountexpirationdate badlogincount department description division emailaddress employeeid faxnumber firstname fullname homedirectory homepage isaccountlocked languages lastfailedlogin lastlogin lastlogoff lastname loginscript manager maxstorage nameprefix namesuffix officelocations othername passwordlastchanged passwordrequired picture postalcodes profile telephonehome telephonemobile telephonenumber telephonepager title);
        print_attributen($administrator, @attributen);
    }

    sub r6_o22 {
        # werkt enkel op VM of labotoestel
        use Win32::OLE::Const;
        my %constants = %{Win32::OLE::Const->Load('Active DS Type Library')};
        for my $key (keys %constants){
            print "$key => $constants{$key}\n" if $key =~ /_UF_/;
        }

    }

    sub r6_o23 {
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

    sub r6_o24 {
        (my $root = bind_object('RootDSE'))->GetInfo();
        my @attributen = qw(name class guid adspath parent schema defaultnamingcontext dnshostname);
        print_attributen($root, @attributen);
    }

    sub r6_o25 {
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

    sub r6_o26 {
        print "Geen implementatie";
    }

    sub r6_o27 {
        my $root = bind_object('RootDSE');
        my @attributen=qw(accountNameHistory aCSPolicyName adminCount adminDescription adminDisplayName allowedAttributes allowedAttributesEffective allowedChildClasses allowedChildClassesEffective altSecurityIdentities assistant badPwdCount bridgeheadServerListBL c canonicalName cn co codePage comment company countryCode createTimeStamp defaultClassStore department description desktopProfile destinationIndicator directReports displayName displayNamePrintable distinguishedName division dSCorePropagationData dynamicLDAPServer employeeID extensionName facsimileTelephoneNumber flags fromEntry frsComputerReferenceBL fRSMemberReferenceBL fSMORoleOwner garbageCollPeriod generationQualifier givenName groupPriority groupsToIgnore homeDirectory homeDrive homePhone homePostalAddress info initials instanceType internationalISDNNumber ipPhone isCriticalSystemObject isDeleted isPrivilegeHolder l lastKnownParent legacyExchangeDN localeID logonCount mail managedObjects manager masteredBy memberOf mhsORAddress middleName mobile modifyTimeStamp mS-DS-ConsistencyChildCount msNPAllowDialin msNPCallingStationID msNPSavedCallingStationID msRADIUSCallbackNumber msRADIUSFramedIPAddress msRADIUSFramedRoute msRADIUSServiceType msRASSavedCallbackNumber msRASSavedFramedIPAddress msRASSavedFramedRoute name netbootSCPBL networkAddress nonSecurityMemberBL o objectCategory objectClass objectVersion operatorCount otherFacsimileTelephoneNumber otherHomePhone otherIpPhone otherLoginWorkstations otherMailbox otherMobile otherPager otherTelephone otherWellKnownObjects ou pager personalTitle physicalDeliveryOfficeName postalAddress postalCode postOfficeBox preferredDeliveryMethod preferredOU primaryGroupID primaryInternationalISDNNumber primaryTelexNumber profilePath proxiedObjectName proxyAddresses queryPolicyBL revision rid sAMAccountName sAMAccountType scriptPath sDRightsEffective seeAlso serverReferenceBL servicePrincipalName showInAddressBook showInAdvancedViewOnly siteObjectBL sn st street streetAddress subRefs subSchemaSubEntry systemFlags telephoneNumber textEncodedORAddress title url userAccountControl userParameters userPrincipalName userSharedFolder userSharedFolderOther userWorkstations USNIntersite wbemPath wellKnownObjects whenChanged whenCreated wWWHomePage x121Address);

        print_attributen(bind_object("CN=Administrator,CN=Users,". $root->get("defaultNamingContext")), @attributen);
    }

    sub r6_o28 {
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

    sub r6_o29 {
        my $root = bind_object("RootDSE");
        my $domein = $root->get("defaultnamingcontext");
        my $cont = bind_object("OU=Studenten,OU=iii,$domein");

        print $cont->{PropertyCount}, " properties in Property Cache, omdat geen GetInfo of GetInfoEx aangeroepen werd\n";
        $cont->getInfo();
        print $cont->{PropertyCount}, " properties in Property Cache, omdat de meeste attributen door GetInfo gecached wordt\n";
        $cont->getInfoEx(["ou","canonicalName","msDS-Approx-Immed-Subordinates","objectclass"],0);
        print $cont->{PropertyCount}, " properties in Property Cache, omdat er 4 extra attributen gecached worden, waarvan er 3 niet door GetInfo gecached worden.\n";
    }

    sub r6_o30 {
        my $root = bind_object('RootDSE');
        my $domein = $root->Get("defaultnamingcontext");
        my $administrator = bind_object("CN=Administrator,CN=Users,$domein");
        print_alle_ingestelde_attributen($administrator);
    }

    sub r6_o31 {
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

    sub r6_o32 {
        print 'Geen implementatie';
    }
    sub r6_o33 {
    my $root = bind_object('RootDSE');
    my $schema = bind_object($root->Get("schemanamingcontext"));
    my %klassen = ();
    for(in $schema){
        $klassen{$_->{class}}++;
    }

    print_frequentiehash_geordend(\%klassen);
    }
    sub r6_o34 {
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
    sub r6_o35 {
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
    sub r6_o36 {
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
    sub r6_o37 {
        print 'Geen implementatie';
    }
    sub r6_o38 {
        my $abstractschema = bind_object("schema");
        my %klassen = ();
        for(in $abstractschema){
            $klassen{$_->{class}}++;
        }

        print_frequentiehash_geordend(\%klassen);
    }
    sub r6_o39 {
        my $ldapdisplayname = $ARGV[1] or die "Geef ldapDisplayName";
        my $schema = bind_object("schema/$ldapdisplayname");
        my @attributen = qw(adspath class guid name parent schema);
        print_attributen($schema, @attributen);
    }
    sub r6_o40 {
        my $ldapdisplayname = $ARGV[1] or die "Geef ldapDisplayName";
        my $abstractschema = bind_object("schema/$ldapdisplayname");
        my @attributen = qw(oid auxderivedfrom abstract auxiliary possiblesuperiors mandatoryproperties optionalproperties container containment);
        print_attributen($abstractschema, @attributen);
    }
    sub r6_o41 {
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
    sub r6_o42 {
        print 'Geen implementatie';
    }
}

sub reeks7 {

    # reeks 7 inleiding
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

    sub r7_o6 {
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

    sub r7_o7 {
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

    sub r7_o8 {
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

    sub r7_o9 {
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

    sub r7_o10 {
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

    sub r7_o11 {
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

    sub r7_o12 {
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

    sub r7_o13 {
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

    sub r7_o14 {
        my $ldapdisplayname = $ARGV[1] or die "Geef LDAP attribuut op";
        my $attribuut = bind_object("schema/$ldapdisplayname");
        print $attribuut->Get("cn");
        
    }

    sub r7_o15 {
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

    sub r7_o16 {
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

    sub r7_o17 {
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

    sub r7_o18 {
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

    sub r7_o19 {
        print "Geen implementatie";
    }

    sub r7_o20 {
        my $root = bind_object("RootDSE");
        my @containers = qw(defaultnamingcontext schemanamingcontext configurationnamingcontext);
        shift @ARGV; # remove the argument '20' that was used to call this exercise
        @ARGV = 0 .. 2 unless @ARGV;
        my $command = get_command(); 
        my $filter = "(objectcategory=*)";
        my $attributen = "objectclass";
        my $scope = "subtree";
        for(0 .. $#ARGV){
            printf "Classes for %s:\n", $containers[$_];
            my $context = bind_object($root->get($containers[$_]));
            my $base = $context->{adspath};
            $command->{CommandText} = "<$base>;$filter;$attributen;$scope";
            my $resultset = $command->Execute();

            my %classhash = ();
            until($resultset->{EOF}){
                my $class = pop @{$resultset->Fields('objectclass')->{Value}};
                $classhash{$class}++;
                $resultset->MoveNext();
            }
            $resultset->Close();
            print_frequentiehash_geordend(\%classhash);
        }
        close_command($command);
    }

    sub r7_o21 {
        # syntax en single-valued => opzoeken in abstracte schema
        #    hoe? Binden met ldapDisplayName, rechtstreeks toegang tot syntax en multiValued attributen

        # geïndexeerd => enkel in het reële schema. Maak gebruik van LDAP query
        
        my $ldapDisplayName = $ARGV[1] or die "Geef ldapDisplayName op";
        my $attr = bind_object("schema/$ldapDisplayName");
        printf "syntax: %s\n", $attr->{syntax};  
        printf "multiValued: %s\n", $attr->{multiValued} ? "Yes" : "No";  


        my $root = bind_object('RootDSE');
        my $context = bind_object($root->Get("schemanamingcontext"));

        my $base = $context->{adspath};
        my $filter = "(&(objectcategory=attributeschema)(ldapdisplayname=$ldapDisplayName))";
        my $attributes = "searchflags";
        my $scope = "subtree";

        my $command = get_command();
        $command->{CommandText} = "<$base>;$filter;$attributes;$scope";
        my $resultset = $command->Execute();

        printf "indexed: %s\n", $resultset->Fields('searchflags')->{Value} & 1 ? "Yes" : "No";

        $resultset->Close();
        close_command($command);
    }

    sub r7_o22 {
        print "Geen implementatie";
    }

    sub r7_o23 {
        print "Geen implementatie";
    }
}


sub reeks8 {
    sub r8_o1 {
        print "Geen implementatie. Deze oefening gaat over de implementatie van de  subroutine 'valueattribuut(object, ldapDisplayName)'";
    }

    sub r8_o2 {
        
    }

    sub r8_o3 {
        my $klassenaam = $ARGV[1] or die "Geef klassenaam op (vb. container, user, organizationalUnit, ...)";
        my $klasse = bind_object("schema/$klassenaam");

        my $row = 1;
        my @attributen = ();
        for(in $klasse->{MandatoryProperties}){
            printf "%d. %s\n", $row++, $_;
            push @attributen, $_;
        }
        printf "Selecteer een getal van %d tot en met %d: ", 1, $row - 1;
        my $num = <STDIN>;
        my $attribuut = $attributen[$num - 1];
        printf "%s geselecteerd. Overzicht van de inhoud van dit attribuut voor alle objecten van '%s:'\n", $attribuut, $klassenaam;

        my $root = bind_object('RootDSE');
        my $context = bind_object($root->Get("defaultnamingcontext"));

        my $base = $context->{adspath};
        my $filter = "(objectclass=$klassenaam)";
        my $attributen = "distinguishedname";
        my $scope = "subtree";

        my $command = get_command();
        $command->{CommandText} = "<$base>;$filter;$attributen;$scope";

        my $resultset = $command->Execute();
        until($resultset->{EOF}){
            my $object = bind_object($resultset->Fields('distinguishedname')->{Value});
            print join (";",@{valueattribuut($object,$attribuut)}), " ($object->{name})\n";
                
            $resultset->MoveNext();
        }
        $resultset->Close();
        close_command($command); 
    }

    sub r8_o4 {
        my $ou_naam = $ARGV[1] or die "Geef naam van nieuwe organizationalUnit op.";
        (my $root = bind_object('RootDSE'))->GetInfo();
        my $container = bind_object("OU=Bert De Saffel,OU=Labo,$root->{defaultNamingContext}");
        
        my $ou = $container->Create("organizationalUnit", "ou=$ou_naam");
        $ou->SetInfo();
        
    }

    sub r8_o5 {
        my $root = bind_object('RootDSE');
        my $domain = bind_object($root->Get("defaultnamingcontext"));

        my $base = $domain->{adspath};
        my $filter = "(&(objectclass=user)(samAccountName=*))";
        my $attributes = "samAccountName";
        my $scope = "subtree";

        my $command = get_command();
        $command->{CommandText} = "<$base>;$filter;$attributes;$scope";
        my $resultset = $command->Execute();

        my $maxSam = "";
        until($resultset->{EOF}){
            my $samAccountName = $resultset->Fields('samAccountName')->{Value};
            printf "%s\n", $samAccountName;
            if(length $samAccountName > length $maxSam){
                $maxSam = $samAccountName;
            }
            $resultset->MoveNext();
        }

        printf "Langste samAccountName = %s met %d letters", $maxSam, length $maxSam;

        $resultset->Close();
        close_command($command);
    }

    sub r8_o6 {
        my $naam = "user_BertDeSaffel";
        my $root = bind_object('RootDSE');
        my $ou = bind_object("OU=Custom Container,OU=Bert De Saffel,OU=Labo,$root->{defaultNamingContext}");

        # te implementeren: gewoon kijken ofda $naam al ergens bestaat als een samAccountName van een ander object 
        #  => gewoon LDAP query uitvoeren:  (&(samAccountName=$name)(|(objectcategory=group)(objectcategory=computer)(objectcategory=person)))
        #  => Indien geen records => samAccountName is nog bruikbaar

        my $user = $ou->Create("user", "cn=$naam");
        $user->Put("samAccountName", $naam);
        $user->SetInfo();
    }

    sub r8_o7 {
        my $root = bind_object('RootDSE');
        my $ou = bind_object("OU=Custom Container,OU=Bert De Saffel,OU=Labo,$root->{defaultNamingContext}");
        $ou->{Filter} = ["user"];
        for(in $ou){
            print "Geef nieuwe mail op:";
            my $mail = <STDIN>;
            if($mail){
                $_->Put("mail", $mail);
            } else {
                $_->PutEx($ADS_PROPERTY_OPERATION_ENUM{ADS_PROPERTY_CLEAR}, "mail", []);
            }
            
            $_->SetInfo();
        }
    }

    sub r8_o8 {
        # why the fuck
    }

    sub r8_o9 {
        (my $root = bind_object('RootDSE'))->GetInfo();
        my $context = bind_object($root->Get("DefaultNamingContext"));

        my $base = $context->{adspath};
        my $filter = "(objectcategory=group)";
        my $attributes = "cn, groupType";
        my $scope = "subtree";

        my $command = get_command();
        $command->{CommandText} = "<$base>;$filter;$attributes;$scope";
        my $resultset = $command->Execute();

        until($resultset->{EOF}){
            printf "%04b: %s\n", $resultset->Fields('groupType')->{Value}, $resultset->Fields('cn')->{Value};
            $resultset->MoveNext();
        }

        $resultset->Close();
        close_command($command);
    }

    sub r8_o10 {
        my $root = bind_object('RootDSE');
        my $domain = bind_object($root->Get("DefaultNamingContext"));

        my $base = $domain->{adspath};
        my $filter = "(&(&(objectcategory=group)(groupType:1.2.840.113556.1.4.803:=" . $ADS_GROUP_TYPE_ENUM{ADS_GROUP_TYPE_DOMAIN_LOCAL_GROUP}. "))(!groupType:1.2.840.113556.1.4.803:=" . $ADS_GROUP_TYPE_ENUM{ADS_GROUP_TYPE_SECURITY_ENABLED} ."))";
        my $attributes = "samAccountName,grouptype";
        my $scope = "subtree";
        my $command = get_command();
        $command->{CommandText} = "<$base>;$filter;$attributes;$scope";
        $command->{Properties}->{"Sort On"} = "samAccountName";

        my $resultset = $command->Execute();
        until($resultset->{EOF}){
            printf "%40s: %b\n", $resultset->Fields('samAccountName')->{Value}, $resultset->Fields('groupType')->{Value} % 16;
            $resultset->MoveNext();
        }

        $resultset->Close();
        close_command($command);
    }

    sub r8_o11 {
        my $root = bind_object("RootDSE");
        my $container = bind_object("OU=Custom Container,OU=Bert De Saffel,OU=Labo,$root->{defaultNamingContext}");

        my $groepnaam = "groep11";
        for(in $container){
            $_->GetInfoEx(["canonicalName"], 0);
            $_->GetInfo("canonicalName") =~ m[".*/(.*)$"];
            if(lc ($1) eq lc $groepnaam){
                die "Groepsnaam $groepnaam bestaat al\n";
            }
        }

        # controle samAccountName is uniek
        my $base = $root->Get("DefaultNamingContext")->{adspath};
        my $filter = "(&(objectcategory=group)(samAccountName=*))";
        my $attributes = "samAccountName";
        my $scope = "subtree";
        
        my $command = get_command();
        $command->{CommandText} = "<$base>;$filter;$attributes;$scope";
        my $resultset = $command->Execute();
        until($resultset->{EOF}){
            die "SamAccountName $groepnaam bestaat al" if lc $resultset->Fields('SamAccountName')->{Value} == lc $groepnaam; 
            $resultset->MoveNext();
        }
        $resultset->Close();
        close_command($command);
        # einde controle

        my $group = $container->Create("group", "cn=$groepnaam");
        $group->Put("samAccountName", $groepnaam);
        $group->SetInfo();
    }

    sub r8_o12 {
        my $root = bind_object("RootDSE");
        my $container = bind_object("OU=Custom Container,OU=Bert De Saffel,OU=Labo,$root->{defaultNamingContext}");

        $container->{Filter} = ["user"];

        my @users = ();
        for(in $container){
            push @users, $_->{DistinguishedName};
        }

        my $group = bind_object("CN=Custom Group,OU=Custom Container,OU=Bert De Saffel,OU=Labo,$root->{defaultNamingContext}");
        $group->PutInfoEx($ADS_PROPERTY_OPERATION_ENUM{ADS_PROPERTY_UPDATE}, "member", \@users);
        $group->SetInfo();
    }

    sub r8_o13 {
        my $root = bind_object("RootDSE");
        my $container = bind_object("OU=Custom Container,OU=Bert De Saffel,OU=Labo,$root->{defaultNamingContext}");
        $container->{Filter} = ["organizationalUnit"];
    }

    sub r8_o14 {
        my $root = bind_object("RootDSE");
        my $domain = bind_object($root->Get("DefaultNamingContext"));

        my $base = $domain->{AdsPath};
        my $filter = "(&(objectCategory=group)(member=*))";
        my $attributes = "distinguishedname,member,cn";
        my $scope = "subtree";

        my $command = get_command();
        $command->{CommandText} = "<$base>;$filter;$attributes;$scope";
        $command->{Properties}->{"Sort On"} = "cn";
        my $resultset = $command->Execute();

        my %groepen;
        my $teller = 1;
        until($resultset->{EOF}){
           # my $groupDN = $resultset->Fields('distinguishedname')->{Value};
            my $cn = $resultset->Fields('cn')->{Value};
            my $leden = $resultset->Fields('member')->{Value};
            $groepen{$teller} = $leden;
            printf "%3d. %40s | aantal leden: %d\n", $teller++, $cn, scalar @{$leden};
            
            $resultset->MoveNext();
        }
        
        printf "Kies een nummer van 1 tot %d om de leden van de corresponderende groep te tonen: ", $teller - 1;
        chomp (my $keuze =  <STDIN>);
        print join "\n", @{$groepen{$keuze}};
        $resultset->Close();
        close_command($command);
    }

    sub r8_o15 {
        my $root = bind_object("RootDSE");
        my $domain = bind_object($root->Get("DefaultNamingContext"));

        my $base = $domain->{AdsPath};
        my $filter = "(&(objectClass=user)(objectCategory=person)(samAccountName=*))";
        my $attributes = "SamAccountName,distinguishedname";
        my $scope = "subtree";

        my $command = get_command();
        $command->{CommandText} = "<$base>;$filter;$attributes;$scope";
        $command->{Properties}->{"Sort On"} = "SamAccountName";
        my $resultset = $command->Execute();


        my %users = ();
        until($resultset->{EOF}){
            $users{$resultset->Fields('samAccountName')->{Value}} = $resultset->Fields('distinguishedname')->{Value};
            $resultset->MoveNext();
        }
        $resultset->Close();
        
        my $it=0;
        printf "%-21s%s", $_, ++$it%4 ? "" : "\n" for sort keys %users;
        print "\nGeef de samAccountName op van een user: ";
        chomp(my $samAccountName = <STDIN>);
        my $user = bind_object($users{$samAccountName});

        my $primarygroupnr = $user->Get("PrimaryGroupId");
        $filter = "(objectclass=group)";
        $attributes = "primaryGroupToken,samAccountName";

        $command->{CommandText} = "<$base>;$filter;$attributes;$scope";
        $resultset = $command->Execute();
        my $primarygroup; # Naam van de primaire groep.
        until($resultset->{EOF}){
            my $groupnr = $resultset->Fields('primaryGroupToken')->{Value};
            if($groupnr == $primarygroupnr){
                $primarygroup = $resultset->Fields('samAccountName')->{Value};
                last;
            }
            $resultset->MoveNext();
        }
        $resultset->Close();
        close_command($command);   

        printf "Primaire groep: %s\n", $primarygroup;
        print "Behoort ook tot de volgende groepen: \n";
        print join "\n", @{$user->GetEx("memberOf")};
        
    }
}


sub valueattribuut {
    my ($object,$attribuut)=@_;
    my $attr_schema = bind_object( "schema/$attribuut" );
    my $tabel = $object->GetEx($attribuut);

    if (Win32::OLE->LastError() == Win32::OLE::HRESULT(0x8000500D)){
	$object->GetInfoEx([$attribuut], 0);
        $tabel = $object->GetEx($attribuut);
    }
    return ["<niet ingesteld>"] if Win32::OLE->LastError() == Win32::OLE::HRESULT(0x8000500D);

    my $v=[];
    my $waarde;
    foreach ( in $tabel ) {
        if ( $attr_schema->{Syntax} eq "OctetString" ) {
            $waarde = sprintf ("%*v02X ","", $_) ;
        }
        elsif ( $attr_schema->{Syntax} eq "ObjectSecurityDescriptor" ) {
            $waarde = "eigenaar is ... " . $_->{owner};
        }
        elsif ( $attr_schema->{Syntax} eq "INTEGER8" ) {
            $waarde = bigint_to_string($_->{HighPart},$_->{LowPart});
        }
        else {
            $waarde = $_;
        }
        push @{$v},$waarde;
    }
    return $v;
}

# Een hash uitprinten, gesorteerd op de values
sub print_frequentiehash_geordend {
    my $hash = shift;
    for my $key (sort { $hash->{$b} <=> $hash->{$a} } keys %{$hash}){
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

