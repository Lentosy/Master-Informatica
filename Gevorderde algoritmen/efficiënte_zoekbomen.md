# ROOD-ZWARTE BOMEN
Een binaire zoekboom, waarbij bovendien:
* Elke knoop rood of zwart gekleurd is.
* Elke virtuele knoop zwart is
* De wortel zwart is
* Elke mogelijke weg vanuit een knoop naar een virtuele knoop evenveel zwarte knopen heeft ( **zwarte diepte** ).
* <a href="https://www.codecogs.com/eqnedit.php?latex=h&space;\leq&space;2&space;\lg(n&space;&plus;&space;1)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?h&space;\leq&space;2&space;\lg(n&space;&plus;&space;1)" title="h \leq 2 \lg(n + 1)" /></a>.

## Rotaties
* Behoudt de inorder volgorde van de sleutels.
* Roteert twee inwendige knopen.
* Moet drie ouder-kindverbindingen aanpassen door enkel pointers te verplaatsen.
* Een rotatie is O(1).

## Zoeken
Equivalent met een gewone binaire boom en is dus <a href="https://www.codecogs.com/eqnedit.php?latex=O(\lg&space;n)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(\lg&space;n)" title="O(\lg n)" /></a>

## Bottom-up
### Toevoegen
1. Voeg een knoop **c** toe op normale manier zoals binaire zoekboom en geef de knoop een rode kleur.
1. Indien de ouderknoop **p** zwart is, is de toevoegoperatie gelukt. Indien de ouderknoop rood is moet verder onderzoek gedaan worden.
   Dit wil ook zeggen de ouderknoop geen wortel is (want die moet zwart zijn). Er is dus wel een grootouder **g** die zwart is.

1. Indien de broer **b** van **p** rood is, moet **g** rood, **p** zwart en **b** zwart gemaakt worden. 
    Indien **g** een zwarte ouder heeft is de situatie opgelost. Is dit niet zo, neemt **g** de plaats van **c** in en moet het algoritme terug vanaf stap 2 beginnen.

1. Indien de broer **b** van **p** zwart is, zijn er twee gevallen te onderscheiden.
   1. Indien **c** aan de uitwendige kant ligt van **p**, liggen de drie knopen **g**, **b** en **c** op een lijn en meot er een rotatie naar links (
   of naar rechts, afhankelijk aan welke kant **c** ligt) uitgevoerd worden. Deze rotatie wordt gevolgd door **p** zwart en **g** rood te kleuren.
    
   1. Indien **c** aan de inwendige kant ligt van **p**, moet enkel **p** en **c** naar links (of rechts) geroteerd worden, zodat we in het vorige geval komen.


### Verwijderen


## Top-down
### Toevoegen

### Verwijderen

# SPLAY TREES
Een normale binaire zoekboom, waarbij elke operatie gevolgd wordt door een splay-operatie. De splay-operatie zal de laatste knoop die toegevoegd/gezocht werd naar de wortel roteren.
### Zoeken
Zoeken gebeurt zoals bij een normale binaire zoekboom, gevolgd door een splayoperaties totdat de gezochte knoop de wortel is.
### Toevoegen
Toevoegen gebeurt zoals bij een normale binaire zoekboom. De nieuwe knoop wordt door splayoperaties tot wortel gemaakt.
### Verwijderen
Verwijderen gebeurt zoals bij een normale binaire zoekboom. De ouder van de verwijderde knoop wordt via splayoperaties tot wortel gemaakt.

De splayoperaties hangt af of dat de splay-tree bottom-up of top-down beschouwd wordt.

## Bottom-up
* Indien de ouder **p** van knoop **c** de wortel van de boom is, moet enkel nog de knopen geroteerd worden zodat **c** de wortel wordt. 
* Indien knoop **c** nog een grootouder **g** heeft, zijn er twee gevallen te onderscheiden.
  * Knoop **c** is een inwendig kind van **p**. Er wordt een rotatie uitgevoerd zodat **c** de ouder van **p** wordt en daarna wordt een rotatie uitgevoerd zodat **c** de plaats inneemt van **g**. De kinderen van **c** zijn nu **p** en **g**.
  * Knoop **c** is een uitwendig kind van **p**. Er worden nu twee rotaties uitgevoerd in dezelfde richting, beginnend vanaf **g** die geroteerd wordt naar links of rechts, en daarna **p** die dezelfde rotatierichting neemt.



## Top-down

## Performantie

# RANDOMIZED SEARCH TREES

# SKIP LISTS
