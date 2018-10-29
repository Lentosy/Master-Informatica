# Projectie
* Per dimensie een gegevensstructuur waarbij sleutels voor die dimensie gerangschikt zijn.
* Sequentieel zoeken.
# Rasterstructuur
* Verdeel de zoekruimte in (regelmatige) rastergebieden (kan geïmplementeerd worden met meerdimensionale tabel).
* Elk rastergebied heeft een gelinkte lijst met punten die erin liggen.
* Kan onnodig veel geheugen innemen

# Quadtrees
* Verdeling van de zoekruimten in <a href="http://www.codecogs.com/eqnedit.php?latex=2^k" target="_blank"><img src="http://latex.codecogs.com/gif.latex?2^k" title="2^k" /></a>
  (hyper)rechthoeken.
* Origineel voor twee dimensies => <a href="http://www.codecogs.com/eqnedit.php?latex=2^k" target="_blank"><img src="http://latex.codecogs.com/gif.latex?2^k" title="2^k" /></a>-wegsboom
* Knoop heeft 4 kinderen (gebieden).
* In cursus toepassingen op het zoeken van 2D punten.
### Point quadtrees
* Uitbreiding binaire boom
* Inwendige knoop bevat een punt. De coördinaten (x en y) delen gebied op in 4 rechthoeken.
* Vorm **afhankelijk** van **toevoegvolgorde**. Slechtste geval is O(n).
### PR quadtrees
* Vereist dat zoekruimte een rechthoek is.
* Elke knoop verdeelt zijn gebied in 4 gelijke delen, totdat elk deel slechts 0 of 1 punt bevat.
* Inwendige knopen bevatten dus geen punten, maar "gebieden".
* Vorm **onafhankelijk** van **toevoegvolgorde**.
* Kan onevenwichtig zijn => onmogelijk om hoogte en grootte in functie van het aantal punten uit te drukken.
### k-d trees
* Binaire boom
* Een inwendige knoop bevat 1 punt, dat de zoekruimte verdeelt in slechts één dimensie.
* Ideale opspliting bestaat uit gelijkmatige verdeling van dimensies.
* Indien punten gekend => evenwichtige k-d tree met hoogte <a href="http://www.codecogs.com/eqnedit.php?latex=O(\lg&space;n)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?O(\lg&space;n)" title="O(\lg n)" /></a> is mogelijk met constructietijd <a href="http://www.codecogs.com/eqnedit.php?latex=O(kn\lg&space;n)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?O(kn\lg&space;n)" title="O(kn\lg n)" /></a>
* Gemiddelde hoogte van <a href="http://www.codecogs.com/eqnedit.php?latex=O(\lg&space;n)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?O(\lg&space;n)" title="O(\lg n)" /></a> in beste geval en <a href="http://www.codecogs.com/eqnedit.php?latex=O(n)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?O(n)" title="O(n)" /></a> in slechtste geval. 
* Geen rotaties van deelbomen of verwijderen van knopen mogelijk door dimensies. Wel eventueel knopen markeren als **deleted** (lazy deletion) en deelbomen **reconstrueren**.
* Men kan aantonen dat performantie in slechtste geval <a href="http://www.codecogs.com/eqnedit.php?latex=O(r&space;&plus;&space;\sqrt{n})" target="_blank"><img src="http://latex.codecogs.com/gif.latex?O(r&space;&plus;&space;\sqrt{n})" title="O(r + \sqrt{n})" /></a> bedraagt.
