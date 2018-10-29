Een 2D-boom is een datastructuur waarin twee-dimensionale punten op efficiënte wijze opgeslagen en opgezocht kunnen worden.

Maak een klasse Boom2D waarin je punten zoals gegeven in [punt2.h](punt2.h) kan opslaan. Let op: punten met gelijke coördinaat als het punt in de knoop moeten naar rechts gaan, niet naar links!

Men moet kunnen
  * punten toevoegen
  * nagaan of een geg. punt in de collectie voorkomt
  * het punt in de collectie zoeken dat dichtst bij een geg. punt ligt (Euclid. afstand)

Om te testen of je programma behoorlijk werkt en efficiënt is krijg je van ons een testbestandje van 39.999 punten, [puntenverzameling.dat](puntenverzameling.dat). Lees dit in en steek de punten (in de gegeven volgorde) in een 2D-boom. Zorg ervoor dat de functie die het dichtstbijgelegen punt zoekt niet alleen dat dichtstbijzijnde punt teruggeeft maar ook het aantal bezochte knopen. In de outputlijst [uitvoer](uitvoer.txt) zit een fout: één punt heeft een verkeerde buur gekregen.

Nu kunnen verschillende punten in de puntenverzameling even ver van een opgegeven punt liggen. Jouw resultaat kan dus een beetje verschillen van dat van de opgave.

Een hoofding, met tekenfuncties voor een 2d-boom, vind je in [kdboom.h](kdboom.g).