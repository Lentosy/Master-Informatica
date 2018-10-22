Als directeur van AWZ (Administratie Waterwegen en Zeekanaal) ben je verantwoordelijk voor een kanaal dat de Ringvaart heet. Daar is een heel specifiek probleem mee.

De Ringvaart is een kanaal dat van west naar oost loopt. Op de noordelijke oever zijn er n voetbalstadions. Elk stadion is gebouwd door een verschillende projectontwikkelaar. Op de zuideroever waren er vroeger n vliegvelden die, toevallig, elk recht tegenover een stadion lagen. Elk van deze vliegvelden is opgekocht door een van de projectontwikkelaars en uitgebouwd tot een winkelcentrum. Nu wil elke projectontwikkelaar om prestigeredenen een brug over de Ringvaart die rechtstreeks zijn voetbalstadion (door de projectontwikkelaars steevast een arena genoemd) met zijn winkelcentrum verbindt.

Het probleem is nu het volgende: de eigenaar van een stadion is niet noodzakelijk de eigenaar van het winkelcentrum dat er recht tegenover ligt, maar om technische redenen kunnen bruggen mekaar niet kruisen. Je zal dus niet aan de wens van elke projectontwikkelaar kunnen voldoen.

De projectontwikkelaars beseffen dat. Elk van hen nodigt je dan ook uit voor een aangenaam verblijf op zijn plezierjacht in Nice. Daar noemt hij, in alle discretie, het bedrag dat hij bereid is over te maken op jou persoonlijke bankrekening als hij zijn brug maar krijgt.

Opdracht:

Schrijf een klasse die aangeeft welke beslissing jou het meeste smeergeld oplevert. De nodige data zitten in het bestand [versnick.dat](versnick.dat), waarbij de arena's en de winkelcentra genummerd zijn van 0 tot n-1, en waarbij arena i recht tegenover winkelcentrum i ligt. Op de eerste lijn van het bestand staat het getal n. Daarna volgen n lijnen, een voor elke arena. Zo'n lijn bevat twee gehele getallen:

    Het bedrag dat de eigenaar van de arena over heeft voor een brug.
    Het nummer van het bijbehorende winkelcentrum.

Hints

    Het is een oefening op dynamisch programmeren.
    Een interessant deelprobleem is het volgende: Gegeven een arena i. Zoek de meest lucratieve oplossing die deze arena verbindt met zijn winkelcentrum, maar geen enkele arena met index groter dan i.
    Als je al deze deelproblemen hebt opgelost is het gemakkelijk de oplossing te vinden.
    Een eenvoudig probleempje dat je op papier kan oplossen vind je in [simpelBrug.dat](simpelBrug.dat).
