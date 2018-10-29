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

## Binomial Queues


## Pairing heaps
