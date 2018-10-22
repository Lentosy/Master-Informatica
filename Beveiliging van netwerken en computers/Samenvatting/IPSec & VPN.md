# IPSec

![ipsec_model](img/ipsec_model.png)

## Netwerklaagbeveiliging Problemen
### Mogelijke bedreigingen
* Pakketten meermaals versturen (replay packets)
* IP-adres wijzigen (source spoofing)
* Geen dataintegriteit of confidentialiteit.
* Vervalste routeinformatie kan verzonden worden.

IPSec is een netwerklaagprotocol dat:

* veilige IP verbindingen maakt.
* applicatieonafhankelijk is.

## Toepassingen
### LAN-to-LAN
Deze methode zal verspreide netwerken (op geografisch verschillende locaties) veilig verbinden zodat het één lokaal netwerk lijkt. 

### Client-to-LAN
Hier zet de client zelf een IPSec verbinding op, alsof het lijkt dat hij deel uitmaakt van het lokaal subnetwerk. 

## Voordelen/nadelen
### Voordelen
* Applicatieonafhankelijk. Het biedt dus ook beveiliging voor applicaties die zelf geen beveiliging voorzien.
* 
