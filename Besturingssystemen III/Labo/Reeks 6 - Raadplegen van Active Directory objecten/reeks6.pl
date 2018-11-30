# Op examen: inloggen als administrator => geen eenvoudige connectie, met eigen credentials inloggen, zoals vanaf lijn 30 
# op examen zal het ip-adres staan, waarschijnlijk 192.168.16.16


use Win32::OLE qw(in);
use Win32::OLE::Const "Active DS Type Library";
use Win32::OLE::Variant;

#thuis: 193.190.126.71
#school: 192.168.16.16

# als je onderstaande 3 lijnen uitvoert op een labotoestel, zal dit oneindig lang duren.

#$moniker_thuis="LDAP://193.190.126.71/CN=Satan,OU=Domain Controllers,DC=iii,DC=hogent,DC=be";
#$obj=bind_object($moniker_thuis);
#print (Win32::OLE->LastError()?"not oke":"oke"),"\n";



# STRUCTUUR DIT BESTAND:
# Elke oefening heeft eigen subroutine. Sommige subroutines kunnen parameters verwachten. Roep dit bestand op volgende manier op:
# perl reeks6.pl oefnr arg1 arg2 ... argn


# perl reeks6.pl 5 Xandro slaapt
#    zal oefening 5 uitvoeren met als twee argumenten 'Xandro' en 'slaapt'


my $oefnr = $ARGV[0] or die "geef oefening nummer op\n";
"oef$oefnr"->();



sub oef6{
    my @attr = qw(adspath class guid name parent schema);
    my $obj=bind_object("LDAP://CN=Satan,OU=Domain Controllers,DC=iii,DC=hogent,DC=be");
    # alle gevraagde ADSI-attributen zijn singlevalued en eenvoudig uit te schrijven als string
    print_attributen($obj, @attr);
}

sub oef7 {
    my @attr = qw(adspath mail);
    my $obj = bind_object("CN=Bert De Saffel,OU=EM7INF,OU=Studenten,OU=iii,DC=iii,DC=hogent,DC=be");   
    print_attributen($obj, @attr);
}


sub oef8 {
    my @attr = qw(adspath guid class objectguid distinguishedname objectclass);
    my $distinguishedName="CN=Users,OU=Labo,DC=iii,DC=hogent,DC=be";
    my $obj=bind_object($distinguishedName);
    print_attributen($obj, @attr);
}

sub oef9 {
    my @attr = qw(mail givename sn displayname homedirectory scriptpath profilepath logonhours userworkstations);
    my $obj = bind_object("CN=Bert De Saffel,OU=EM7INF,OU=Studenten,OU=iii,DC=iii,DC=hogent,Dc=be");
    print_attributen($obj, @attr);
}

sub oef12 {
    my @attr = qw(name class guid adspath parent schema);
    my $DomeinDN = GetDomeinDN();
    my $o = bind_object("CN=Administrator,CN=Users,$DomeinDN");
    print_attributen($o, @attr);
}

sub oef13 {
    my @attr = qw (Name Class GUID ADSPath Parent Schema dnsHostName defaultNamingContext);
    my $RootObj = bind_object("RootDSE");

    print_attributen($RootObj, @attr);

    #De ADSI-attributen Class en Schema zijn niet ingevuld omdat RootDSE niet overeenkomt met een AD&nbsp;object
    #verwissel defaultNamingContext dnsHostName om alle uitvoer te zien.

    #In PowerShell heb je daar geen last van...
}

sub oef15 {
    my @attr = qw(name);
    my $controllers = bind_object("OU=Domain Controllers,DC=iii,DC=hogent,DC=be");
    for my $controller (in $controllers){
        print_attributen($controller, @attr);
    }
}

sub oef16 {
    my $lokaal = $ARGV[1] or die "geef het klaslokaal op (219 of 225)";
    my $computers = bind_object("OU=$lokaal,OU=PC's,OU=iii,DC=iii,DC=hogent,DC=be");
    my @attr = qw(name);
    for my $computer  (in $computers){
        print_attributen($computer, @attr);
    }
}

sub oef17 {
    my $objecten = bind_object("CN=System,DC=iii,DC=hogent,DC=be");
    my @attr = qw(name objectclass);
    for my $obj (in $objecten){
        print_attributen($obj, @attr);
    }
}

sub oef18 {
    $RootObj = bind_object('RootDSE');
    $RootObj->{DnsHostName}; #om de PropertyCache te initialiseren - zie later
    $domein = $RootObj->{defaultNamingContext};

    my $class=$ARGV[1] or die "geef een klasse op\n";

    my $Users = bind_object("CN=Users,$domein");
    $Users->{Filter} = [$class];
    print "AD-objecten van type $class:\n";
    print "$_->{adspath}\n" foreach in $Users;

    print "\nAdministrator:\n";
    my $a = $Users->GetObject("user","CN=Administrator");
    print $a->{ADsPath};

}


sub oef21 {
    $RootObj = bind_object('RootDSE');
    $RootObj->{DnsHostName}; #om de PropertyCache te initialiseren - zie later
    $domein = $RootObj->{defaultNamingContext};
    my @attr = qw(accountdisabled accountexpirationdate badlogincount department 
                  description division emailaddress employeeid faxnumber firstname
                  fullname homedirectory homepage isaccountlocked languages
                  lastfailedlogin lastlogin lastlogoff lastname loginscript
                  manager maxstorage nameprefix namesuffix
                  officelocations othername passwordlastchange passwordrequired
                  picture postalcodes profile telephonehome telephonemobile
                  telephonenumber telephonepager title);
    my $administrator = bind_object("CN=Administrator,CN=Users,$domein");
    print_attributen($administrator, @attr);
}

sub oef22 {
    my $zoekstring = $ARGV[1] || "(.*)";
    my %constanten = %{Win32::OLE::Const->Load('Active DS Type Library')};
    for my $key (keys %constanten){
        print "$key => $constanten{$key}\n" if $key =~ /$zoekstring/gms;
    }
}

sub oef23 {
    
}

# print de attributen van een AD object uit
# parameters:
#    een AD object
#    een array van attributen die gewenst zijn
sub print_attributen {
    my $obj = shift;
    my @attr = @_;
    for (@attr){

        printf "%20s : ", $_; # uitprinten attribuutnaam
        if(ref $obj->{$_} eq 'ARRAY'){
            printf join "-", @{$obj->{$_}};
        } else {
            if( $_ eq "objectguid"){
                sprintf "%*v02X ","", $obj->{$_}; # iets mis met deze sprintf functie
            } else{
                print $obj->{$_};
            }     
        }
        print "\n";
    }
}

sub bind_object{
   my $parameter=shift;
   my $moniker;
   my $obj;
   if ( uc($ENV{USERDOMAIN}) eq "III") { #ingelogd op het III domein
       $moniker = (uc( substr( $parameter, 0, 7) ) eq "LDAP://" ? "" : "LDAP://").$parameter;
       $obj = (Win32::OLE->GetObject($moniker));
   }
   else {                                #niet ingelogd
       my $ip="193.190.126.71";          #voor de controle thuis
       $moniker = (uc( substr( $parameter, 0, 7) ) eq "LDAP://" ? "" : "LDAP://$ip/").$parameter;
       my $dso = Win32::OLE->GetObject("LDAP:");
       my $loginnaam = "bdsaffel";          #vul in
       my $paswoord  = "ugentpasswoord...";          #vul in
       $obj = ($dso->OpenDSObject( $moniker, $loginnaam, $paswoord, ADS_SECURE_AUTHENTICATION ));
   }
   if(Win32::OLE->LastError()){
       print "Binding failed...\n";
   }
   
   return $obj;
}

sub GetDomeinDN {
    my $RootObj = bind_object("RootDSE");

    print "Server DNS:               $RootObj->{dnsHostName}\n";
    print "       SPN:               $RootObj->{ldapServiceName}\n";
    print "       Datum & tijd:      $RootObj->{currentTime}\n";
    print "       Global Catalog ?   $RootObj->{isGlobalCatalogReady}\n";
    print "       gesynchronizeerd ? $RootObj->{isSynchronized}\n";
    print "       DN:                $RootObj->{serverName}\n";

    print "Domeingegevens:           $RootObj->{defaultNamingContext}\n";
    print "Configuratiegegevens:     $RootObj->{configurationNamingContext}\n";
    print "Schema:                   $RootObj->{schemaNamingContext}\n";

    print "Functioneel niveau \n";
    print "    Forest:               $RootObj->{forestFunctionality}\n";
    print "    Domein:               $RootObj->{domainFunctionality}\n";

    return $RootObj->{defaultNamingContext};
}

