# Samenvoegbare heaps
* Gebruikelijke implementatie van een prioriteitswachtrij is een binaire heap (eventueel d-heap).
* Twee binaire heaps samenvoegen is O(n) aangezien één van de tabellen gekopieerd moet worden.
* Wanneer efficiënt samenvoegen vereist is gebruikt men beter een andere implementatie.
* Het samenvoegen van twee prioriteitswachtrijen.

* Voorbeelden:
  * **LEFTIST HEAPS**: Gelijkaardig met binaire heaps, behalve dat het geen complete binaire boom is. Het doel is om zo **onevenwichtig** mogelijk te zijn (de linkerkant is diep). Operaties zijn efficiënt omdat ervoor gezorgd wordt dat het meeste werk aan de rechterkant ligt. Samenvoegen is <a href="http://www.codecogs.com/eqnedit.php?latex=O(\lg&space;n)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?O(\lg&space;n)" title="O(\lg n)" /></a>.
  * **SKEW HEAPS**: 
    * Zelforganiserende versie van een leftist heap. 
    * Binaire boom met heapvoorwaarde, maar zonder vormbeperkingen.
    * Reeks van m opeenvolgende operaties is <a href="http://www.codecogs.com/eqnedit.php?latex=O(m\lg&space;n)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?O(m\lg&space;n)" title="O(m\lg n)" /></a>. Geamortiseerd is dit <a href="http://www.codecogs.com/eqnedit.php?latex=O(\lg&space;n)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?O(\lg&space;n)" title="O(\lg n)" /></a>
    * Samenvoegen en Toevoegen is O(1).

## Binomial Queues


## Pairing heaps
