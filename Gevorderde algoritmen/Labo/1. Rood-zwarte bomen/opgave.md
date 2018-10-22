Rood-zwarte bomen zijn altijd nogal evenwichtig. Je betaalt er wel een prijs voor: toevoegen en verwijderen is ingewikkeld. Voor we ze implementeren zijn hier een paar toepassingen om op papier op te lossen.

We vertrekken van zeer scheve boom:

![scheve_boom](img/sheve_boom.png)

als l de diepte aan de linkerkant is, en r de diepte aan de rechterkant, dan is
r=2l+1.

Slechter kan niet bij een rood-zwarte boom, en elke bewerking zal de situatie verbeteren. Probeer maar:

* sleutels -6, -1 en -3 bottom-up toevoegen.
* sleutel 36 bottom-up toevoegen.

Implementatie.

Als je dit alles implementeert moet je een rood-zwarteboomklasse hebben. Je zou denken dat je eenvoudig kan overerven van een gewone binaire boom, maar dat blijkt niet erg goed te lukken. Omdat elke knoop een kleur heeft moet er dan in elke knoop een attribuut bijkomen. Die interactie tussen boom en knoop leidt tot problemen, zodat er niet veel meer overblijft dan de lelijke weg: je kopieert gewoon de code van een zoekboom en verandert overal Zoekboom door RZWBoom. Dat is niet flexibel --als je verbeteringen aanbrengt aan de Zoekboomcode wordt die niet meegenomen naar de RZWBoom, maar het werkt wel. Je krijgt van ons het bestand rzwboom14.h met relevante code voor een binaire boom, zoals een repOK-functie voor een binaire boom en een rotatiefunctie.

Ook voor deze nieuwe klasse ga je eerst een repOK()-functie schrijven. Zoals gebruikelijk bij overerving (al is deze hier puur formeel) is de repOK()-functie van de bovenklasse een deel van die voor de onderklasse.

Daarna schrijf je een bottom-up toevoegmethode. De voorbeeldjes op de tekeningen leveren handige stof voor tests. Daar zit je met een probleem: hoe zorg je ervoor dat je een rood-zwarte boom krijgt met de structuur vanop de tekeningen?

Programmeertip: elke knoop is de wortel van een (deel)boom. Het is handig als je een functie geefKleur() maakt die geen lid is van de Knoopklasse maar van de Boomklasse. Waarom is dat?
Testen
Als je code schrijft moet je die ook testen. Dat is meer dan alleen maar nagaan of je code compileert en niet crasht op één klein voorbeeldje. Vaak is het zo dat je meer testcode hebt dan code die getest moet worden. Dat lijkt veel werk met weinig opbrengst, maar dat is het niet: alleen zo kan je zeker zijn dat je code werkt zoals het hoort.

Kleine boompjes kan je inspecteren met een uitschrijfoperatie. Die is voorzien in de code. Wie liever een tekening heeft kan gebruik maken van het dot-pakket (op labo-computers download je best de zip-versie). Een scriptje om .dot-bestanden om te zetten naar een afbeelding vind je in genereer-dot.sh (je kan de dot-code ook online een grafiek laten genereren via http://webgraphviz.com/).

234-boom (de bijbehorende lidfuncties heten tekenAlsBinaireBoom(...) en tekenAls234boom(...).

Een belangrijk concept bij testen is de rep-invariant. Dit staat voor representatie-invariant. Het is het geheel van voorwaarden waaraan de representatie in het geheugen van een object moet voldoen om de een geldig object voor te stellen. Voor een binaire zoekboom zijn de in het oog springende voorwaarden:

1. Het moet een geldige binaire boom zijn.
1. De sleutels moeten in volgorde staan.

Het eerste aspect houdt in dat alle pointers oké moeten zijn. Nu werken we met unique_ptrs. Bij normaal gebruik staat een unique_ptr op nul ofwel wijst hij naar een object terwijl hij de enige unique_ptr is die naar dat object wijst. Als dat om een of andere reden niet het geval is merken we dat meestal gauw genoeg, zodat we dat in dit geval niet moeten testen. (Er kan soms een probleem zijn met een circuit van unique_ptrs, maar zo'n circuit hangt dan per definitie nergens meer aan. Het leidt dan wel tot een geheugenlek, maar niet tot een verbreking van de rep-invariant). Onze binaire boom heeft ook ouderpointers. Dit zijn gewone pointers en het behoort natuurlijk tot de rep-invariant dat deze pointers naar de juiste knopen wijzen.

De rep-invariant van alle betrokken objecten maakt deel uit van pre- en postconditie van alle publiek toegankelijke functies (interne functies kunnen soms de rep-invariant doorbreken of een gebroken rep-invariant herstellen). Bij testen moet je hem dus regelmatig controleren. Het is gebruikelijk een te testen klasse een lidfunctie bool repOK() te geven. Deze gaat na of de rep-invariant voldaan is. Het eerste punt van de bovenstaande opdracht is dus het schrijven van de repOK()-functie voor de rood-zwarteboomklasse die de bovenstaande voorwaarden controleert. Tip: dit kan in O(n).

Als volgende punt moet je kunnen nagaan of de operaties die je programmeert wel degelijk doen wat ze moeten doen. Eén element daarbij is dat de operaties niets mogen veranderen aan de sleutelverzameling. Hiervoor is het nodig dat je

1. Een kopie kan nemen van de begintoestand voor het uitvoeren van de operatie. Noteer dat dit alleen maar mogelijk is als sleutels en data kopieerbaar zijn (is dat eigenlijk een voorwaarde die moet altijd moet voldaan zijn als je een zoekboom wil gebruiken?)
1. Van twee zoekbomen kan nagaan of ze dezelfde sleutelverzameling hebben en dezelfde data bij de gelijke sleutels. Nu heeft de zoekboom een inorder-functie die gemakkelijk kan gebruikt kan worden met λ-functies. Zijn er alternatieve manieren om een boom te doorlopen? Welke is het meest geschikt bij dit probleem?

De rotatie-operatie kan je nu gemakkelijk testen op kleine voorbeeldjes door middel van de uitschrijfoperatie. Zorg er zeker voor dat je alle speciale gevallen bekijkt:

* Roteer zowel deelbomen als basisbomen.
* Probeer alle mogelijke combinatie van aan- en afwezige kinderen. Als p de ouderknoop is van de knoop c en c moet geroteerd worden met p, dan kan p al of niet een tweede kind hebben en c kan geen of twee kinderen hebben, of alleen een linker- en een rechterkind.
* Roteer zowel naar links als naar rechts.
* Combineer de bovenstaande mogelijkheden.

![boom](img/boom.png)

Opdrachten

1. Schrijf code die de twee tekeningen hierboven (min of meer) reproduceert. Kijk dan ook eens naar de vorm als je hem als 234-boom tekent.
1. Schrijf een RepOK()-functie. Maak daarbij gebruik van de bijgeleverde RepOKZoekboom()-functie.

1. Test nu je rotaties. Deze laten de representatie-invariant van de zoekboom ongemoeid, maar je boom is geen rood-zwarte boom meer.
1. Bij beide gegeven bomen is er echter 1 rotatie die je kan uitvoeren waarbij je de rood-zwarte voorwaarden kan herstellen door alleen de geroteerde knopen te herkleuren. Voer deze rotaties uit, met de herkleuring en kijk of alles oké is. Kijk daarbij ook naar de 234-boomtekeningen. Wat gebeurt er daar?
1. Schrijf en test een toevoegfunctie. Ga meteen na of je het met de hand toevoegen van het begin juist hebt gedaan.
1. Testen moet grondig gebeuren: zorg ervoor dat alle 6 speciale gevallen uit de cursus zeker voorkomen in je testsuite (dat heet whiteboxtesten: elke lijn uit je code moet aan bod komen).
1. Laat toevoegen nu eens lopen met twee extreme gevallen: de getallen van 1 tot 1000 in random volgorde (wat goed zou moeten werken bij een gewone zoekboom) en dezelfde getallen in natuurlijke volgorde (wat een ramp is voor een gewone boom). Kijk ook hier naar de bijbehorende tekeningen.
