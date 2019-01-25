=pod
Configureer via een script de permanente eventregistratie die er voor zorgt dat, indien er meerdere notepad of calculator processen opgestart worden, ze op de meest recente na afgebroken worden.
Test dit eerst uit met notepad, want het opstarten van calculator is moeilijker te triggeren op bepaalde besturingssystemen.

Pas het script aan zodat de events vooraf gegroepeerd worden.

Tips:

    Je kan eerst een semi-synchroon script opstellen dat de gewenste taken uitvoert. Het voordeel is dat je ook extra informatie kan uitschrijven als het niet direct werkt.
    Je kan een tweede reactie toevoegen waarbij enkel een melding wordt gemaakt (zoals in oefening 60). Daarbij wordt enkel informatie van opgehaalde attributen in de melding getoond. Als de events gegroepeerd worden kan je ook eenvoudig toevoegen in de melding hoeveel processen er werden afgesloten.
    Met de oplossing van oefening 20 kan je de logs bekijken.
=cut


use Win32::OLE qw(in);
use Win32::OLE::Const 'Microsoft WMI Scripting';


my $service = (Win32::OLE->new('WbemScripting.SWbemLocator'))->ConnectServer('.', 'root/cimv2');

my $ActiveScriptEventConsumer = $service->Get('ActiveScriptEventConsumer')->SpawnInstance_();

$ActiveScriptEventConsumer->{ScriptingEngine} = 'PerlScript';
$ActiveScriptEventConsumer->{ScriptText} = q [
use Win32::OLE qw(in);
use Win32::OLE::Const 'Microsoft WMI Scripting';
my $service = (Win32::OLE->new('WbemScripting.SWbemLocator'))->ConnectServer('.', 'root/cimv2');
my @notepadprocesses = in $service->ExecQuery("SELECT * 
                                               FROM Win32_Process 
                                               WHERE Name='$TargetEvent->{TargetInstance}->{Name}'
                                               AND CreationDate < '$TargetEvent->{TargetInstance}->{CreationDate}');
for(@notepadprocesses) {
    $_->Terminate();
}
];


$ActiveScriptEventConsumer->Put_(wbemFlagUseAmendedQualifiers);

my $EventFilter = $service->Get('__EventFilter')->SpawnInstance_();
$EventFilter->{Name} = 'Notepad startup filter';
$EventFilter->{QueryLanguage} = 'WQL';
$EventFilter->{Query} = "select *
                         from __InstanceCreationEvent Within 10
                         where processname='notepad.exe'";
$EventFilter->Put_(wbemFlagUseAmendedQualifiers);


$FilterToConsumerBinding = $service->Get('__FilterToConsumerBinding')->SpawnInstance_();
$FilterToConsumerBinding->{Consumer} = $ActiveScriptEventConsumer->{Path};
$FilterToConsumerBinding->{Filter} = $EventFilter->{Path};

$FilterToConsumerBinding->Put_(wbemFlagUseAmendedQualifiers);



