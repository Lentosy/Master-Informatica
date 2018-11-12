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

6. #TODO, kwil eerst WMI doen


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
$All | Select @{Name='Class';Expression={$_.SystemProperties_.Item('__CLASS').Value}}, @{Name='Attributes';Expression={$_.Properties_ | foreach {$_.Name}}}

#Bepaal daarna de klasse met het grootste aantal "eigen" attributen.
$All | Select @{Name='Class';Expression={$_.SystemProperties_.Item('__CLASS').Value}}, @{Name='AttributeCount';Expression={$_.Properties_.Count}} | Sort-Object -Property AttributeCount -Descending | Select -First 1


13. # Bepaal het aantal instanties van Win32_LogicalDisk. Toon enkel het relatief pad van elke instantie. Bekijk de mogelijkheden van het attribuut Path_
$Win32_LogicalDisk_Instances = $service.ExecQuery('Select * From Win32_LogicalDisk')
$Win32_LogicalDisk_Instances | Select @{Name='RelPath';Expression={$_.SystemProperties_.Item('__RELPATH').Value}}

14. # Geef een overzicht van alle attributen (ook systeemattributen) van een klasse, waarvoor je de naam meegeeft als enig argument. 
    # Bepaal ook het CIMtype van elk attribuut (haal de tekstuele beschrijving op - zie oefening 1), en geef aan of de inhoud samengesteld (een array) is.
    # Test dit uit voor de klasse Win32_Directory en ook voor de associatorklasse Win32_Subdirectory.
$classname = 'Win32_Directory'
$Class = $service.Get($classname)
$Class.Properties_ + $Class.SystemProperties_ | foreach {
    Write-Host $_.Name, $_.CimType, $_.IsArray
    
}
