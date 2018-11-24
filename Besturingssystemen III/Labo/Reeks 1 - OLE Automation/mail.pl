# bevat de uitwerking van oef 13 tot en met oef 20.
use strict;
use warnings;

use Win32::OLE qw(in);
use Win32::OLE::Const;
Win32::OLE->Option(Warn => 3);

my $message = Win32::OLE->new("CDO.Message");
# Initialisatie Message object
$message->{From} = 'Bert.DeSaffel@UGent.be';
$message->{To} = 'Xandro.Vermeulen@UGent.be';
$message->{Subject} = 'ver-assing';
$message->{TextBody} = 'gegenereerd met perl';


my $configuration = Win32::OLE->new('CDO.Configuration');
printf "Er zijn %d objecten in de Fields collectie\n", $configuration->{Fields}->{Count};
printf "Het objecttype van de objecten uit de Fields collectie is : %s\n", join '/', Win32::OLE->QueryObjectType($configuration->{Fields}->Item(0));

print "De naam en waarde van elk standaard configuration field: \n";
for my $field (in $configuration->{Fields}){
    print "\t$field->{Name} => $field->{Value}\n";
}

print "Relevante constanten met behhulp van de type library: \n";
my $constants  = Win32::OLE::Const->Load($configuration);
while((my $key, my $value) = each %$constants){
    print "\t$key\n" if $key =~ /SMTPServer|SendUsing/gms;
}

$configuration->{Fields}->Item($constants->{cdoSMTPServer})->{Value}     = "smpt.ugent.be";
$configuration->{Fields}->Item($constants->{cdoSMTPServerPort})->{Value} = 25;
$configuration->{Fields}->Item($constants->{cdoSendUsingPort})->{Value}      = 2;
$configuration->{Fields}->Update();      #is noodzakelijk

$message->{Configuration} = $configuration;


$message->Send();