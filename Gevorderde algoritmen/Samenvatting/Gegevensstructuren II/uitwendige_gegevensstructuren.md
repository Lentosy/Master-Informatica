# B-TREES
* Uitwendige evenwichtige zoekboom.
* Zeer kleine hoogte (dus meer dan twee kinderen per knoop => **meerwegszoekboom**).
* Knoop moet eerst ingelezen worden vooraleer er mee kan gewerkjt worden. Gewijzigde knopen moeten terug opgeslagen worden.
* Voorzie geheugenruimte voor de meest recent gebruikte knopen. (zeker de wortel, en soms volledig eerste niveau).
* Elk blad heeft dezelfde diepte.
* Ingrijpende wijzigingen aan de boomstructuur zijn zeldzaam.

### Definitie
Een B-tree van orde *m*, waarbij *m > 2*, wordt als volgt gedefinieerd:
* Elke inwendige knoop heeft hoogstens *m* kinderen (een kind = pointer naar andere knoop)
* Elke inwendige knoop, behalve de wortel, heeft minstens <a href="http://www.codecogs.com/eqnedit.php?latex=\lceil&space;m/2&space;\rceil" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\lceil&space;m/2&space;\rceil" title="\lceil m/2 \rceil" /></a>. De wortel heeft minstens twee kinderen, tenzij hij een blad is.
* Alle bladeren zitten op hetzelfde niveau.
Elke knoop heeft dan:
* Een variabele *k* dat het huidig aantal **sleutels** in die knoop aanduidt.
* Een tabel voor maximaal *m* wijzers naar de **kinderen** van de knoop.
* Een tabel voor maximaal *k = m - 1* sleutels, die stijgend (niet dalend) gerangschikt zijn, plus een tweede tabel van dezelfde grootte voor de informatie.
* Een logische waarde *b* die aanduidt of de knoop een blad is.

### Eigenschappen
* **Minimaal aantal sleutels *n* voor een B-tree met hoogte *h***:
   Aangezien elke knoop minimaal <a href="http://www.codecogs.com/eqnedit.php?latex=g&space;=&space;\lceil&space;m/2&space;\rceil" target="_blank"><img src="http://latex.codecogs.com/gif.latex?g&space;=&space;\lceil&space;m/2&space;\rceil" title="g = \lceil m/2 \rceil" /></a> kinderen heeft, en de wortel minimum 1 sleutel, is het aantal knopen ten minste:
   
<a href="http://www.codecogs.com/eqnedit.php?latex=n&space;=&space;1&space;&plus;&space;2&space;&plus;&space;2g&space;&plus;&space;...&space;&plus;&space;2g^{h&space;-&space;1}&space;=&space;1&space;&plus;&space;2\sum_{i&space;=&space;0}^{h&space;-&space;1}&space;g^i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?n&space;=&space;1&space;&plus;&space;2&space;&plus;&space;2g&space;&plus;&space;...&space;&plus;&space;2g^{h&space;-&space;1}&space;=&space;1&space;&plus;&space;2\sum_{i&space;=&space;0}^{h&space;-&space;1}&space;g^i" title="n = 1 + 2 + 2g + ... + 2g^{h - 1} = 1 + 2\sum_{i = 0}^{h - 1} g^i" /></a>

<a href="http://www.codecogs.com/eqnedit.php?latex=n&space;\geq&space;1&space;&plus;&space;2(g&space;-&space;1)\bigg(\frac{g^h&space;-&space;1}{g&space;-&space;1}\bigg)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?n&space;\geq&space;1&space;&plus;&space;2(g&space;-&space;1)\bigg(\frac{g^h&space;-&space;1}{g&space;-&space;1}\bigg)" title="n \geq 1 + 2(g - 1)\bigg(\frac{g^h - 1}{g - 1}\bigg)" /></a>

<a href="http://www.codecogs.com/eqnedit.php?latex=n&space;\geq&space;2g^h&space;-&space;1" target="_blank"><img src="http://latex.codecogs.com/gif.latex?n&space;\geq&space;2g^h&space;-&space;1" title="n \geq 2g^h - 1" /></a>

<a href="http://www.codecogs.com/eqnedit.php?latex=h&space;\leq&space;log_{g}\frac{n&space;&plus;&space;1}{2}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?h&space;\leq&space;log_{g}\frac{n&space;&plus;&space;1}{2}" title="h \leq log_{g}\frac{n + 1}{2}" /></a>

De hoogte is dus O(lg n), zelfde als voor rood-zwarte bomen, maar de (verborgen) constante is een factor <a href="http://www.codecogs.com/eqnedit.php?latex=\lg&space;g" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\lg&space;g" title="\lg g" /></a> kleiner.


### Operaties

#### Zoeken
---
* In elke knoop moet nagegaan worden of de gezochte sleutel er in zit (lineair zoeken of binair zoeken).
* Is dit niet zo, en de huidige knoop is nog geen blad, dan moet de juiste wijzer naar de volgende knoop gekozen worden, deze knoop inlezen en het proces herhaalt zich.
* Is de huidige knoop een blad en zit de gezochte sleutel niet in deze knoop, dan zit de sleutel **niet** in de boom.
---
* Het resultaat van de zoekoperatie is een verwijzing naar de knoop op de schijf (paginaindex, blokindex, whatever ge het wilt noemen). 
* Aantal schijfoperaties is O(h).

#### Toevoegen
* Enkel **bottom-up** wordt besproken. De **top-down** versie wordt minder vaak gebruikt, maar is handig indien meerdere gebruikers aan de boom moeten, aangezien knopen op de zoekweg vroeger worden vrijgegeven.
---
* Toevoegen gebeurt steeds bij een blad. Heeft dit blad nog plaats, dan is er geen probleem.
* Heeft het blad reeds *m* kinderen, wordt de knoop gesplitst bij de middelste sleutel. 
* Er wordt een nieuwe knoop aangemaakt op hetzelfde niveau (op bladniveau). Deze knoop krijgt de gegevens die zicht rechts van de middelste sleutel bevinden (de gegevens links van de middelste sleutel blijven dus in de oorspronkelijke knoop zitten). Deze operatie noemt men een splitsing (kost drie schijfoperaties).
* De middelste sleutel wordt nu verwijderd van de knoop, en wordt toegevoegd bij de ouderknoop van de huidige knoop. Nu kan hetzelfde proces herhaalt worden, en de ouderknoop beschouwd worden als een blad. 
* In het slechtste geval wordt het probleem opgeschoven tot de wortel (splitsing van h + 1 knopen). In dit geval zal er een nieuwe wortel aangemaakt worden met slechts 1 element (het middelste element van de vorige wortel).
---
#### Verwijderen
* Ook enkel **bottom-up** versie.
---
* Altijd verwijderen in een blad, anders teveel structuurwijziging.
* Vervang de te verwijderen sleutel met zijn opvolger of voorloper (die zit altijd in een blad). 
* Meestal zit de gezochte sleutel wel in een blad aangezien de meeste sleutels van een B-tree in bladeren zitten.
* Wanneer een knoop te weinig sleutels heeft (< <a href="http://www.codecogs.com/eqnedit.php?latex=\lceil&space;m/2&space;\rceil" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\lceil&space;m/2&space;\rceil" title="\lceil m/2 \rceil" /></a>), dan kan men proberen om een sleutel over te nemen van een broerknoop
    1. de sleutel van de broer gaat naar zijn ouder
    1. een sleutel van de ouder gaat naar de knoop, die ook een kindwijzer van de broer overneemt.
    1. Omdat hier drie knopen worden aangepast, gaan we vaak meerdere sleutels verdelen, zodat elke knoop evenveel sleutels heeft.
* Als de ene broer geen sleutel kan uitlenen, kan men proberen bij de andere broer. 
* Indien geen van beide broers kan, gebeurt het omgekeerde van splitsen. De knoop wordt samengevoegd met een broer, de ouder verliest dus een kind, zodat de sleutel tussen de twee broers moet verdwijnen, deze wordt toegevoegd aan de samengevoegde knoop. 
---

## B+ tree
* Deze variant zal alle gegevens (sleutels en de bijhorende informatie) in de bladeren opslaan.
* De inwendige knopen worden gebruikt als index en bevatten dus enkel de sleutel.

## Prefix B+ tree
* Wordt gebruikt indien de sleutels strings zijn.
* Elke sleutel in een inwendige knoop is zo een kort mogelijke string, vaak een prefix van de te onderscheiden string.

## B* tree
* Zal bij de splitstoperatie de gegevens over de drie knopen verdelen, in plaats van de twee knopen.

# UITWENDIGE HASHING
* Indien niet geïnteresseerd in volgorde van sleutels.
* Woordenboekoperaties gemiddeld O(1) schijfoperaties
* **Hypothese**: we zouden aan elk element een schijfpagina kunnen toekennen (alle sleutels met dezelfde hashwaarde komen dus in dezelfde pagina). In het geval dat een pagina volgeraakt, zullen methoden zoals [Open Adressering](https://en.wikipedia.org/wiki/Hash_table#Open_addressing) en (Seperate Chaining)[https://en.wikipedia.org/wiki/Hash_table#Separate_chaining] zoals bij een inwendige hashtabel, het aantal schijfoperaties vergroten. Dit is niet gewenst.

