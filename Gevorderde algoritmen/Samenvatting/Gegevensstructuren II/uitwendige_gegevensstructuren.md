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
* In elke knoop moet nagegaan worden of de gezochte sleutel er in zit (lineair zoeken of binair zoeken).
* Is dit niet zo, en de huidige knoop is nog geen blad, dan moet de juiste wijzer naar de volgende knoop gekozen worden, deze knoop inlezen en het proces herhaalt zich.
* Is de huidige knoop een blad en zit de gezochte sleutel niet in deze knoop, dan zit de sleutel **niet** in de boom.


* Het resultaat van de zoekoperatie is een verwijzing naar de knoop op de schijf (paginaindex, blokindex, whatever ge het wilt noemen). 
* Aantal schijfoperaties is O(h).

#### Toevoegen
* Enkel **bottom-up** wordt besproken. De **top-down** versie wordt minder vaak gebruikt, maar is handig indien meerdere gebruikers aan de boom moeten, aangezien knopen op de zoekweg vroeger worden vrijgegeven.

* Toevoegen gebeurt steeds bij een blad. Heeft dit blad nog plaats, dan is er geen probleem.
* Heeft het blad reeds *m* kinderen, wordt de knoop gesplitst bij de middelste sleutel. 




#### Verwijderen


# UITWENDIGE HASHING
