# Samenvoegbare heaps
* Gebruikelijke implementatie van een prioriteitswachtrij is een binaire heap (eventueel d-heap).
* Twee binaire heaps samenvoegen is O(n) aangezien één van de tabellen gekopieerd moet worden.
* Wanneer efficiënt samenvoegen vereist is gebruikt men beter een andere implementatie.
* Het samenvoegen van twee prioriteitswachtrijen.

* Voorbeelden:
  * **LEFTIST HEAPS**: 
    * Gelijkaardig met binaire heaps, behalve dat het geen complete binaire boom is. 
    * Het doel is om zo **onevenwichtig** mogelijk te zijn (de linkerkant is diep). 
    * Operaties zijn efficiënt omdat ervoor gezorgd wordt dat het meeste werk aan de rechterkant ligt. Samenvoegen is <a href="http://www.codecogs.com/eqnedit.php?latex=O(\lg&space;n)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?O(\lg&space;n)" title="O(\lg n)" /></a>.
  * **SKEW HEAPS**: 
    * Zelforganiserende versie van een leftist heap. 
    * Binaire boom met heapvoorwaarde, maar zonder vormbeperkingen.
    * Reeks van m opeenvolgende operaties is <a href="http://www.codecogs.com/eqnedit.php?latex=O(m\lg&space;n)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?O(m\lg&space;n)" title="O(m\lg n)" /></a>. Geamortiseerd is dit <a href="http://www.codecogs.com/eqnedit.php?latex=O(\lg&space;n)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?O(\lg&space;n)" title="O(\lg n)" /></a>
    * Samenvoegen en Toevoegen is <a href="http://www.codecogs.com/eqnedit.php?latex=O(1))" target="_blank"><img src="http://latex.codecogs.com/gif.latex?O(1))" title="O(1))" /></a>.
  * **BINOMIAL QUEUES**:
    * Een bos van binomiaalbomen, elk met de heapvoorwaarde.
    * Een binomiaalboom met hoogte *h* heeft <a href="http://www.codecogs.com/eqnedit.php?latex=\binom{h}{d}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\binom{h}{d}" title="\binom{h}{d}" /></a> knopen op diepte *d*.
    * Samenvoegen, toevoegen en minimum verwijderen is <a href="http://www.codecogs.com/eqnedit.php?latex=O(\lg&space;n)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?O(\lg&space;n)" title="O(\lg n)" /></a>. Geamortiseerd is dit <a href="http://www.codecogs.com/eqnedit.php?latex=O(1))" target="_blank"><img src="http://latex.codecogs.com/gif.latex?O(1))" title="O(1))" /></a>.
  
  * **FIBONACCI HEAPS**:
    * Veralgemening van binomial queues.
    * Knopen met weinig deelbomen zijn toegelaten.
    * Binomiaalbomen worden enkel samengevoegd wanneer nodig (lazy merging).
    * Geamortiseerde performantie van samenvoegen, toevoegen en prioriteit verminderen is <a href="http://www.codecogs.com/eqnedit.php?latex=O(1))" target="_blank"><img src="http://latex.codecogs.com/gif.latex?O(1))" title="O(1))" /></a>. Het minimum en een (gelokaliseerd) element verwijderen is <a href="http://www.codecogs.com/eqnedit.php?latex=O(\lg&space;n)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?O(\lg&space;n)" title="O(\lg n)" /></a>. De constante is echter te groot zodat ze enkel **theoretisch** nut hebben.
  * **PAIRING HEAPS**:
    * Zelforganiserende, gestroomlijnde versie van een binomial queue.
    * Sneller dan andere structuren wanneer prioriteit verminderen vereist is. 
    * Geamortiseerde performantie van samenvoegen, toevoegen, minimum verwijderen en prioriteit verminderen is <a href="http://www.codecogs.com/eqnedit.php?latex=O(\lg&space;n)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?O(\lg&space;n)" title="O(\lg n)" /></a>.

  * **RELAXED HEAPS**: 
    * Onbelangrijke structuur
## Binomial Queues
#### Structuur
* Bos van binomiaalbomen, elk met de heapvoorwaarde.
* Hoogstens <a href="http://www.codecogs.com/eqnedit.php?latex=\lg&space;n" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\lg&space;n" title="\lg n" /></a> bomen in een bos.
* Binomiaalboom wordt gekenmerkt door hoogte. Slechts één binomiaalboom <a href="http://www.codecogs.com/eqnedit.php?latex=B_h" target="_blank"><img src="http://latex.codecogs.com/gif.latex?B_h" title="B_h" /></a> met hoogte *h* mogelijk.
* Op diepte *d* zijn er <a href="http://www.codecogs.com/eqnedit.php?latex=\binom{h}{d}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\binom{h}{d}" title="\binom{h}{d}" /></a> knopen. In totaal zijn er dus <a href="http://www.codecogs.com/eqnedit.php?latex=2^h" target="_blank"><img src="http://latex.codecogs.com/gif.latex?2^h" title="2^h" /></a> knopen.
* Een prioriteitswachtrij kan steeds voorgesteld worden door een bos binomiaalbomen, dat hoogsten één boom van elke hoogte bevat. Stel <a href="http://www.codecogs.com/eqnedit.php?latex=2^i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?2^i" title="2^i" /></a> knopen voor boom <a href="http://www.codecogs.com/eqnedit.php?latex=B_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?B_i" title="B_i" /></a>, dan kan een prioriteitsrij met 13 elementen voorgesteld worden als: <a href="http://www.codecogs.com/eqnedit.php?latex=\left&space;\langle&space;B_3,&space;B_2,&space;B_0&space;\right&space;\rangle" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\left&space;\langle&space;B_3,&space;B_2,&space;B_0&space;\right&space;\rangle" title="\left \langle B_3, B_2, B_0 \right \rangle" /></a>.

#### Operaties
* **MINIMUM VINDEN**: Overloop alle wortels van elke boom in het bos. Het minimum zal één van deze wortels zijn.
* **SAMENVOEGEN**: Bomen met dezelfde hoogte "optellen". De opteloperatie maakt de wortel met de grootste sleutel kind van deze met de kleinste. Het resultaat is een boom <a href="http://www.codecogs.com/eqnedit.php?latex=B_{h&space;&plus;&space;1}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?B_{h&space;&plus;&space;1}" title="B_{h + 1}" /></a>. Samenvoegen van twee binomiaalbomen is <a href="http://www.codecogs.com/eqnedit.php?latex=O(1)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?O(1)" title="O(1)" /></a>. Samenvoegen van twee binomiaalqueues is dus <a href="http://www.codecogs.com/eqnedit.php?latex=O(\lg&space;n)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?O(\lg&space;n)" title="O(\lg n)" /></a>. 

## Pairing heaps
