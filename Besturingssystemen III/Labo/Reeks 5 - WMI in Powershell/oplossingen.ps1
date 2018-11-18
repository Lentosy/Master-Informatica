1.
#EVENTUEEL EERST 'Set-Culture en-US' doen, BUG powershell, kan enkel excel open indien engels
$excel = New-Object -ComObject Excel.Application
$excel.Workbooks.Add()
$excel.Workbooks.Count

2.
#Type library activeren
Add-Type -AssemblyName Microsoft.Office.Interop.Excel
#Probeer deze commandos dan eens uit om te zien of het gaat
[Microsoft.Office.Interop.Excel.Constants]::xlDoubleQuote.value__
[Microsoft.Office.Interop.Excel.Constants]::xlTop.value__

3.
# Aantal services bepalen
(Get-Service).Count
# Eerste service ophalen
$service = Get-Service | Select -First 1
# Uitprinten attributen
$service | Select-Object -Property *
# Naam uitprinten van alle gestopte services
(Get-Service) | Where Status -eq 'Stopped' | Select-Object -Property Name
# Groeperen op status
(Get-Service) | Group-Object Status | Select -Property Name, Count

4.
# Bepaal voor één service het aantal services dat moet opgestart zijn, alvorens je die éne service kan opstarten.
#  -- ik selecteer een random service, waarvan DependentServices bestaat
(Get-Service | Where DependentServices | Get-Random -Count 1) | Select -Property Name, DependantServices # TODO, hoe COUNT doen op dependantServices?
# Toon nu alle services die van geen enkele service afhangen en die ook effectief zijn opgestart.
Get-Service | Where { $_.DependentServices.Count -EQ 0 -AND $_.Status -EQ 'Running' }

5.
#Toon alle bestanden van de huidige map. Je kan hierbij vertrekken van de gekende alias "dir". 
Get-ChildItem -File 
    # OF
Get-ChildItem | Where Extension
#Toon het aantal directories/bestanden/... (per soort)
#Toon enkel de bestanden.
#Beperk het overzicht tot bestanden die na "1/10/2017" zijn gewijzigd en toon enkel de naam en de datum. Merk op de een datum begint met de "maand". Sorteer het overzicht op datum (de recentste eerst).
Get-ChildItem -File | Where LastWriteTime -GT @(Get-Date -Year 2017 -Month 10 -Day 1 -Minute 0 -Second 0 -Hour 0)

6. # Er zijn in PowerShell heel wat bewerkingen beschikbaar op specifieke objecten. We bekijken de mogelijkheden van een tijd-object. 
   # Je kan dit terugvinden door een variabele te initialiseren met een tijd, en van die variabele de beschikbare methodes en attributen op te vragen.
   # Bepaal nu alle bestanden van de huidige map die op een zondag laatst aangepast werden. Toon voor die bestanden de naam, en enkel het uur van de dag.
   # Tip: Je kan een Expressie @{Name="";Expression={..}} gebruiken om bewerkingen te vragen op een attribuut. Een alternatief is Foreach-Object gebruiken. Met Write-Host kan je een mooiere uitvoer krijgen. 
Get-ChildItem -File | Where {$_.LastWriteTime.DayOfWeek -EQ "Sunday"} | Select Name, @{Name="Last Access";Expression={$_.LastWriteTime.Hour}}

################## WMI IN POWERSHELL
# IN HET BEGIN UITVOEREN, ZODAT LOCATOR EN SERVICE AANGEMAAKT WORDEN, dan moet ik da nie voor elke opgave doen 
$locator = New-Object -ComObject WbemScripting.SWbemLocator
$service = $locator.ConnectServer('.', 'root/cimv2')


7.#Toon alle beschikbare powershell-properties van het WMI-COM-object dat de klasse Win32_LogicalDisk representeert.
$Win32_LogicalDisk = $service.Get('Win32_LogicalDisk')
$Win32_LogicalDisk | Select -Property *
#Hoe kan je alle WMI-properties tonen van deze klasse.
$Win32_LogicalDisk.Properties_ + $Win32_LogicalDisk.SystemProperties_
#Toon de waarde van het WMI-property __DERIVATION
$Win32_LogicalDisk.SystemProperties_ | Where Name -EQ '__DERIVATION' | Select Value


8.#Herneem vorige oefening voor één instantie van de klasse (maakt niet uit welke instantie).
$Win32_LogicalDisk = $service.InstancesOf('Win32_LogicalDisk') | Get-Random -Count 1
$Win32_LogicalDisk | Select -Property *
$Win32_LogicalDisk.Properties_ + $Win32_LogicalDisk.SystemProperties_
$Win32_LogicalDisk.SystemProperties_ | Where Name -EQ '__DERIVATION' | Select Value
#Toon de inhoud van een beperkt aantal WMI-eigenschappen (DeviceID, VolumeName, Description) van deze instantie. Toon ook de waarde van een systeemattribuut van deze instantie.
($Win32_LogicalDisk.Properties_ | Where {$_.Name -EQ 'DeviceID' -OR $_.Name -EQ 'VolumeName' -OR $_.Name -EQ 'Description'} | Select -Property Name, Value) + ($Win32_LogicalDisk.SystemProperties_ | Get-Random -Count 1)
# -- De systemproperties van Win32_logicaldisk zal dezelfde attributen selecteren als van properties, dus daar moet je die niet meer specificeren.


9. #Bepaal voor alle instanties van de klasse Win32_LogicalDisk de waarde van DeviceID. Voor WMI-COM-objecten moet je alle instanties ophalen met een methode
$Win32_LogicalDisk_Instances = $service.InstancesOf('Win32_logicalDisk')
$Win32_LogicalDisk_Instances | Select @{Name = 'DeviceID';Expression={$_.Properties_.Item('DeviceID').Value}}

10. #Bepaal het aantal "eigen" WMI-attributen van de klasse Win32_LogicalDisk.
$Win32_LogicalDisk = $service.Get('Win32_LogicalDisk')
$__SUPERCLASS = $service.Get($Win32_LogicalDisk.SystemProperties_.Item('__SUPERCLASS').Value)
$Win32_LogicalDisk.Properties_.Count - $__SUPERCLASS.Properties_.Count # oops, opgave bedoelt gewoon $Win32_LogicalDisk.Properties_.Count, en niet de nieuwe attributen geïntroduceerd door Win32_logicalDisk, ze moet maar duidelijker zijn

11. #Zoek alle Win32-klassen die met "events" te maken hebben (het woordje Event in de naam). Gebruik een WQL-query om alle klassen op te halen.
$Event_Classes = $service.ExecQuery('Select * From meta_class Where __CLASS Like "%EVENT%"')
$Event_Classes | Select @{Name='Class';Expression={$_.SystemProperties_.Item('__CLASS').Value}}

12. # Geef een overzicht van alle klassen, gevolgd door het aantal "eigen" attributen. 
$All = $service.ExecQuery('Select * From meta_class')
$All | Select @{Name='Class';Expression={$_.SystemProperties_.Item('__CLASS').Value}}, @{Name='Attributes';Expression={$_.Properties_ | Foreach {$_.Name}}}

#Bepaal daarna de klasse met het grootste aantal "eigen" attributen.
$All | Select @{Name='Class';Expression={$_.SystemProperties_.Item('__CLASS').Value}}, @{Name='AttributeCount';Expression={$_.Properties_.Count}} | Sort-Object -Property AttributeCount -Descending | Select -First 1


13. # Bepaal het aantal instanties van Win32_LogicalDisk. Toon enkel het relatief pad van elke instantie. Bekijk de mogelijkheden van het attribuut Path_
$Win32_LogicalDisk_Instances = $service.ExecQuery('Select * From Win32_LogicalDisk')
$Win32_LogicalDisk_Instances | Select @{Name='RelPath';Expression={$_.SystemProperties_.Item('__RELPATH').Value}}

14. # Geef een overzicht van alle attributen (ook systeemattributen) van een klasse, waarvoor je de naam meegeeft als enig argument. 
    # Bepaal ook het CIMtype van elk attribuut (haal de tekstuele beschrijving op - zie oefening 1), en geef aan of de inhoud samengesteld (een array) is.
    # Test dit uit voor de klasse Win32_Directory en ook voor de associatorklasse Win32_Subdirectory.
function GiveAttributes([string]$classname){
    $Class = $service.Get($classname)
    Write-Host "Attributes for", $classname
    $Class.Properties_ + $Class.SystemProperties_ | Foreach {
        Write-Host "`t", $_.Name, $_.CimType, $_.IsArray
    }
}
GiveAttributes('Win32_Directory');
GiveAttributes('Win32_Subdirectory');


15. # Geef van de SNMP service een op naam gesorteerde lijst van alle attributen en systeemattributen, en hun waarden. Zorg er ook voor dat meervoudige waarden geconcateneerd op ��n lijn getoond worden.
    # Wijzig je oplossing zodat je die informatie ophaalt voor de bijhorende klasse. Wat merk je op ? 

# kan ik nie doen thuis omda ik geen SNMP heb


16. # Bepaal alle klassequalifiers voor de klasse Win32_LogicalDisk. Toon ook de waarde van elke qualifier.
$Win32_LogicalDisk = $service.Get("Win32_LogicalDisk", 131072) #131072 -> wbemFlagUseAmendedQualifiers
$Win32_LogicalDisk.Qualifiers_ | Select -Property Name, Value
    # Toon nu enkel de "beschrijving" van de klasse. 
($Win32_LogicalDisk.Qualifiers_ | Where {$_.Name -EQ "Description"}).Value  # NIET   | Select Value doen, zal niet de hele description printen

17. # Bepaal alle attribuutqualifiers van alle attributen die specifiek zijn voor een klasse (bv Win32_LogicalDisk).
$Win32_LogicalDisk = $service.Get("Win32_LogicalDisk", 131072)
$Win32_LogicalDisk.Properties_ | Select Name, Value

18. # Toon alle abstracte klassen waarvan de naam begint met WIN32. Toon ook het aantal van deze klassen. 
$Abstract_classes = $service.ExecQuery("Select * From meta_class Where __CLASS like 'Win32%'")
$count = 0
$Abstract_classes | Foreach {
    if(($_.Qualifiers_ | Where {$_.Name -EQ 'abstract'}).Value){
        $_.SystemProperties_.Item('__CLASS').Value
        $count++
    }
}
Write-Host $count, "abstract classes"


19. # Bepaal alle event-klassen die expliciet door een provider zijn toegevoegd (van welke klassen zijn ze afgeleid?).
    # Orden dit overzicht op aantal eigen attributen properties van elke klasse. 

    # dunno

20. # Bepaal de naam van alle WMI-methodes van de klasse Win32_LogicalDisk 
$Win32_LogicalDisk = $service.Get('Win32_LogicalDisk')
$Win32_LogicalDisk.Methods_ | Select Name

21. # Toon alle methodes + methodequalifiers voor Win32_Process. De uitvoer afwerken zodat je alle qualifiers ook ziet is niet zo evident. Gebruik daarvoor foreach + Write-Host.
$Win32_Process = $service.Get('Win32_Process', 131072)
Foreach ($method in $Win32_Process.Methods_) {
    $method.Name
    Foreach($qualifier in $method.Qualifiers_){
        "`t" + $qualifier.Name
    }
}


22. # Bepaal voor de klasse Win32_Directory een overzicht met alle methodes, en het aantal in- en uit-parameters. 
$Win32_Directory = $service.Get('Win32_Directory', 131072)
Write-Host 'Methods of Win32_directory'
$Win32_Directory.Methods_ | Select Name, @{Name='In';Expression={$_.InParameters.Properties_.Count}}, @{Name='Out';Expression={$_.OutParameters.Properties_.Count}}

23. # Beperk de lijst tot methodes die een tekstuele interpretie hebben voor de return-value. Geef ook een mooie voorstelling voor die tekstuele interpretatie (is vrij complex!!) 
$Win32_Directory = $service.Get('Win32_Directory', 131072)
Write-Host 'Methods of Win32_directory, who have a textual interpretation for the return value'
$Win32_Directory.Methods_ | Foreach {  
    if ($_.Qualifiers_ | where{$_.Name -eq "Values"}) {
        $_.Name
    }
} #TOTODODOTODO


24. # Welke parameters zijn beschikbaar voor de cmdlet Sort-Object en Select-Object ?
    # Toon nu de 10 processen met het hoogste aantal Handles.
Get-Process | Sort-Object -Descending -Property Handles | Select-Object -First 10

25. # Bekijk de parameters van de cmdlet Group-Object.
    # Toon de 10 werkwoorden die meest voorkomen in een commando. Er zijn ook commando's zonder werkwoord.
Get-Command | Group-Object -Property Verb | Sort -Descending -Property Count | Select-Object -First 10
    # Hoe kan je het overzicht aanpassen zodat je enkel informatie krijgt over cmdlet-commando's. 
Get-Command -CommandType Cmdlet| Group-Object -Property Verb | Sort -Descending -Property Count | Select-Object -First 10


26. # Toon alle properties die beschikbaar zijn voor een commando. Beperk het overzicht tot de properties (geen methodes)
    # Gebruik nu de juiste property om een lijst te tonen van alle commando's zonder werkwoord. Gebruik een reguliere expressie in het Where-Object .
    # Hoe kan je snel nagaan dat dit hoofdzakelijk Aliassen zijn ? 
Get-Command | Where {$_.Verb -MATCH "^$"}

27. # Zoek alle cmdlets waarmee je services kan aanspreken. Bepaal het aantal services.
    # Initialiseer een variabele met ��n service, neem bijvoorbeeld de eerste service. Toon alle properties van de service.
    # Toon de naam van alle services die gestopt zijn.
    # Bepaal het totaal aantal services voor elke status.
    
    
    # NIE VERGETEN OM LOCATOR EN SERVICE AAN TE MAKEN (lijn 51 en 52 in dit script)
$Win32_Service_Instance = $service.InstancesOf('Win32_Service') | Get-Random -Count 1
$Win32_Service_Instance.Properties_ | Select -Property Name, Value

$Win32_Services_Stopped = $service.ExecQuery("Select * From Win32_Service where State='Stopped'")
$Win32_Services_Stopped | Select @{Name="Process";Expression={$_.Properties_.Item('Name').Value}}

$Win32_Service_Instances = $service.InstancesOf('Win32_Service')
$Win32_Service_Instances | Select @{Name="Service";Expression={$_.Properties_.Item('Name').Value}}, @{Name='State';Expression={$_.Properties_.Item('State').Value}} | Group-Object State | Select Name, Count

28. # Toon een aantal interessante properties (Caption, Description en FileSystem) van de logical disk die hoort bij C: 
$C_LogicalDisk = $service.Get("Win32_LogicalDisk.DeviceID='C:'")
$C_LogicalDisk | Select @{Name='Caption';Expression={$_.Properties_.Item('Caption').Value}},
                        @{Name='Description';Expression={$_.Properties_.Item('Description').Value}},
                        @{Name='FileSystem';Expression={$_.Properties_.Item('FileSystem').Value}}

29. # Start zelf minstens 1 keer Notepad op. Toon nu de naam en het handlenummer van (alle) Notepad-processen. 
$service.ExecQuery("SELECT * FROM Win32_Process WHERE Name='notepad.exe'") | Select @{Name='Name';Expression={$_.Properties_.Item('Name').Value}}, 
                                                                                    @{Name='Handle';Expression={$_.Properties_.Item('Handle').Value}}

30. # Toon de beschrijving van alle Win32-klassen die iets met NetWorkAdapter te maken hebben. 
$service.ExecQuery("SELECT * FROM META_CLASS Where __CLASS like '%NetworkAdapter%'", 'WQL', 131072) | Select @{Name='Class';Expression={$_.Path_.Class}},
                                                                                                             @{Name='Description';Expression={$_.Qualifiers_.Item('Description').Value}}


31. # Toon alle namespaces, startend vanaf "root\cimV2". Schrijf hiervoor een recursieve functie. Indien je onvoldoende rechten hebt, dan resulteert dit in een fout. 

$locator = New-Object -ComObject WbemScripting.SWbemLocator

function Get-NameSpaces([string] $namespace){
    $service = $locator.ConnectServer('.', $namespace)
    $namespaces = $service.InstancesOf('__NAMESPACE')
    $namespaces | ForEach-Object {
       $newnamespace = $namespace + "\" + $_.Properties_.Item('Name').Value
       $newnamespace
       Get-NameSpaces($newnamespace)
   }
}

Get-NameSpaces('root\cimv2')