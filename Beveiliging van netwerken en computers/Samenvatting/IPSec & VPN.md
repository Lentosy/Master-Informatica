# IPSec
![ipsec_model](img/ipsec_model.png)

## Netwerklaagbeveiliging
### Mogelijke bedreigingen
* Pakketten meermaals versturen (replay packets)
* IP-adres wijzigen (source spoofing)
* Geen dataintegriteit of confidentialiteit.
* Vervalste routeinformatie kan verzonden worden.

IPSec is een netwerklaagprotocol dat:

* veilige IP verbindingen maakt.
* applicatieonafhankelijk is.

##Toepassingen
### LAN-to-LAN
Deze methode zal verspreide netwerken (op geografisch verschillende locaties) veilig verbinden zodat het één lokaal netwerk lijkt. 

### Client-to-LAN
Hier zet de client zelf een IPSec verbinding op, alsof het lijkt dat hij deel uitmaakt van het lokaal subnetwerk. 

## Voordelen/nadelen
### Voordelen
* Applicatieonafhankelijk. Het biedt dus ook beveiliging voor applicaties die zelf geen beveiliging voorzien.
* Beveiligingsmechanismen moeten maar gelden op beperkt aantal systemen (firewall of router). Het interne verkeer wordt hierdoor niet beïnvloedt.
* Eindgebruikers moeten zich hier niets van aantrekken.
### Nadelen
* Er is geen beveiliging nadat het bericht de gateway heeft gepasseerd.
* Systeemresources zijn nodig om cryptographische functies te berekenen.
* De implementatie is vrij complex en het gebeurt vaak dat verschillende versies incompatibel zijn met elkaar.
