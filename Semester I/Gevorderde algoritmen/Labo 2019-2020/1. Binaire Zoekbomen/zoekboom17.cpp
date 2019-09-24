#include "zoekboom17.h"
#include <stdexcept>

/*
* De diepte van een binaire zoekboom is gelijk aan het aantal knopen op het pad van de wortel naar de diepste knoop. Een lege boom krijgt als diepte -1.
*/
template<class Sleutel, class Data>
int ZoekBoom<Sleutel, Data>::geefDiepte() const {
	if (*this) {
		return std::max((*this)->links.geefDiepte(), (*this)->rechts.geefDiepte()) + 1;
	}
	return -1; // -1 want anders wordt hierboven eens +1 te veel gedaan 
}


/*
Een rotatie behoudt de inorder volgorde van de sleutels zodat de representatie van de boom nog steeds geldig is. De roteeroperatie wordt gebruikt om een boom evenwichtig te maken. Er is zowel een rotatie naar links als naar rechts gedefinieerd, maar dit is slechts het spiegelbeeld van elkaar zodat dit met een bool geïmplementeerd kan worden. De roteeroperatie is O(1).
*/
template<class Sleutel, class Data>
void ZoekBoom<Sleutel, Data>::roteer(Richting richting) {
	bool rotatieLinks = (richting == Richting::LINKS);

	// Preconditie: de wortel en nodig kind bestaan
	if(!(*this)){
		throw std::runtime_error(std::string(__FUNCTION__) + " [Er is geen wortel]");
	}
	if(!(*this)->geefKind(!rotatieLinks)){
		throw std::runtime_error(std::string(__FUNCTION__) + " [De wortel heeft geen kind om te roteren]");
	}
	// In totaal moeten er zes pointers verplaatst worden. Omdat er enkel move operaties nodig zijn is de roteeroperatie O(1)
	// Het te roteren kind wordt apart bijgehouden
	ZoekBoom<Sleutel, Data> c = std::move((*this)->geefKind(!rotatieLinks));
	// 1. Verhang beta zodat die het (linker|rechter)kind wordt van p, afhankelijk of de rotatie naar (rechts|links) uitgevoerd wordt
	ZoekBoom<Sleutel, Data>& beta = std::move(c->geefKind(rotatieLinks)); // beta is het (linker|rechter) kind van c, afhankelijk of de rotatie naar (links|rechts) uitgevoerd wordt
	(*this)->geefKind(!rotatieLinks) = std::move(beta); // kan ook in 1 operatie

	// 2. Verhang p zodat deze het (linker|rechter)kind wordt van c, afhankelijk of de rotatie naar (links|rechts) uitgevoerd wordt 
	c->geefKind(rotatieLinks) = std::move(*this);

	// 3. Vervang de wortel door c
	*this = std::move(c);

	// 4. Vervang de ouder van c door de oorspronkelijker ouder van p
	(*this)->ouder = std::move((*this)->geefKind(rotatieLinks)->ouder);
	
	// 5. De nu lege ouderpointer van p moet naar c wijzen
	(*this)->geefKind(rotatieLinks)->ouder = this->get();

	// 6. Indien er een beta is, moet de ouderpointer van beta naar p wijzen.
	if ((*this)->geefKind(rotatieLinks)->geefKind(!rotatieLinks)) {
		(*this)->geefKind(rotatieLinks)->geefKind(!rotatieLinks)->ouder = (*this)->geefKind(rotatieLinks).get();
	}
}



/*
De meest onevenwichtige boom is een boom waarbij elke knoop enkel een linkerkind heeft, of enkel een rechterkind. Deze representatie is dan een gelinkte lijst, zodat de operaties op de boom O(n) worden in plaats van O(log n). Het algoritme zelf is O(n). 
*/
template<class Sleutel, class Data>
void ZoekBoom<Sleutel, Data>::maakOnevenwichtig(Richting richting) { 
	// BUG: een boom onevenwichtig maken is geen probleem, maar een LINKS onevenwichtig boom RECHTS onevenwichtig maken werkt niet, de boom verandert helemaal niet

	bool rotatieLinks = (richting == Richting::LINKS);
	
	// Deze implementatie laat toe om te kiezen of de boom links of rechts onevenwichtig is.
	// In beide gevallen wordt er gestart vanuit de wortel. 
	// Het algoritme blijft rotaties uitvoeren zolang er nog kinderen in de (linker|rechter)deelboom aanwezig zijn, afhankelijk of de boom (rechts|links) onevenwichtig moet zijn.
	// Wanneer een knoop geen (linker|rechter)kinderen meer heeft, wordt er afgedaald naar de volgende knoop waar het proces zich herhaalt en stopt wanneer de diepste knoop bereikt is (na rotaties).

	ZoekBoom<Sleutel, Data>* huidige = this;
	
	if(!*huidige){
		throw std::runtime_error(std::string(__FUNCTION__) + " [Er is geen wortel]");
	}

	// Zolang dat er nog dieper in de boom kan gedaald worden OF als de huidige knoop de wortel is
	while ((*huidige)->geefKind(rotatieLinks) || (*huidige)->ouder == nullptr ) {
		// Roteer zolang er nog kinderen zijn in de verkeerde deelboom
		while ((*huidige)->geefKind(!rotatieLinks)) 
			huidige->roteer(richting);
		
		// daal naar de volgende knoop
		if((*huidige)->geefKind(rotatieLinks))
			huidige = &((*huidige)->geefKind(rotatieLinks));
	} 
	

}


template<class Sleutel, class Data>
void ZoekBoom<Sleutel, Data>::maakEvenwichtig() {
	// TODO: hier heb ik in gedachten om dus eerst de boom zo onevenwichtig mogelijk te maken (met functie maakOnevenwichtig)
	// Daarna roteren we vanaf de wortel tot aan de helft (cutoff) van die 'gelinkte lijst'
	// Dan zou je zo een boom moeten krijgen:
	//
	//      /\
	//     /  \
	//	  /	   \	 
	//	 /      \
	//	/        \
	//
	//	Dan kan je hetzelfde doen op die twee deelbomen tot een evenwichtige boom bereikt is
	

	// Eerst controleren of de boom compleet onevenwichtig is, anders doen we het zelf nog
	bool isOnevenwichtig = true;
	this->inorder([&isOnevenwichtig](const ZoekKnoop<Sleutel, Data>& knoop){
		// als een knoop 2 kinderen heeft is de boom NIET evenwichtig
		if(knoop.links && knoop.rechts){
			isOnevenwichtig = false;
		}
	});

	if(!isOnevenwichtig){
		this->maakOnevenwichtig(Richting::RECHTS);
	}

	// De boom is nu zeker onevenwichtig, het algoritme kan uitgevoerd worden
	int cutoff = round(this->geefDiepte() / 2);
	bool rotatieNaarLinks = true;
	std::cout << cutoff << "\n";
	while(cutoff > 1){
		for(int i = 0; i < cutoff; i++){
			this->roteer(rotatieNaarLinks ? Richting::LINKS : Richting::RECHTS);
		}
		cutoff = round(this->geefDiepte() / 2);
		rotatieNaarLinks = !rotatieNaarLinks;
		
	}
}


/*
* Deze functie test of de binaire zoekboom een geldige interne structuur heeft. Volgende controles worden uitgevoerd:
*  1. De sleutels in inorder overlopen moet de sleutels gerangschikt opleveren. Dit impliceert dat de sleutels in de linkerdeelboom van een boom kleiner zijn dan de sleutel van de wortel van die boom en dat de sleutels in de rechterdeelboom groter zijn dan diezelfde sleutel van de wortel.
*  2. De wortel 'w' van de hele boom mag geen ouderpointer hebben.
*  3. Elke andere knoop 'k' in de boom moet een ouderpointer hebben naar een knoop 'o' die 'k' als rechter- of linkerkind heeft. 
*/
template<class Sleutel, class Data>
bool ZoekBoom<Sleutel, Data>::repOK() const
{
	const Sleutel* vorige = 0;
	bool ok = true;

	// 2. Controleer of de wortel een ouderpointer heeft
	if((*this)->ouder != 0){
		ok = false;
	}

	// Overloop de boom in inorder
	this->inorder([&vorige, &ok](const ZoekKnoop<Sleutel, Data>& knoop) {
		// 1. Controleer of dat de sleutels in de juiste volgorde in de boom zitten.
		if (vorige && knoop.sleutel < *vorige) {
			ok = false;
		}
		vorige = &(knoop.sleutel);

		/*
			In principe dient de inorder traversal enkel voor de volgorde te controleren, maar aangezien we nu toch elke knoop aan het overlopen zijn kunnen andere eigenschappen ook hierin gecontroleerd worden. 
		*/

		// 3. Controleer dat de twee kinderen van de knoop de juiste ouderpointer hebben
		// TODO

	});

	return ok;
}


