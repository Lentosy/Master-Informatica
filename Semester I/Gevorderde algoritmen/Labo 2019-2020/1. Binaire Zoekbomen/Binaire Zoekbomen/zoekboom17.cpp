#include "zoekboom17.h"


template<class Sleutel, class Data>
int ZoekBoom<Sleutel, Data>::geefDiepte() const {

	if (*this) {
		return std::max((*this)->links.geefDiepte(), (*this)->rechts.geefDiepte()) + 1;
	}
	return -1; // -1 want anders wordt hierboven eens +1 te veel gedaan 
}


/*
spiegeloperatie wordt via 'rotatieLinks' in één keer gedaan.
als je roteert naar rechts: geefkind(rotatielinks)   geeft dan het rechterkind
*/
template<class Sleutel, class Data>
void ZoekBoom<Sleutel, Data>::roteer(Richting richting) {

	bool rotatieLinks = richting == Richting::LINKS ? true : false;

	//indien je roteert naar (rechts|links), neem dan (linker|rechter)kind even apart
	ZoekBoom<Sleutel, Data> c = std::move((*this)->geefKind(!rotatieLinks));

	// Verhang beta
	(*this)->geefKind(!rotatieLinks) = std::move(c->geefKind(rotatieLinks));
	// p wordt het (rechter|linker)kind van c
	c->geefKind(rotatieLinks) = std::move(*this);
	// vervang de wortel door c
	*this = std::move(c);


	// De ouder van p wordt nu de ouder van c
	(*this)->ouder = std::move((*this)->geefKind(rotatieLinks)->ouder);

	// De ouderpointer van p moet nu naar c wijzen.
	(*this)->geefKind(rotatieLinks)->ouder = this->get();

	// De ouderpointer van beta moet nu naar p wijzen
	if ((*this)->geefKind(rotatieLinks)->geefKind(!rotatieLinks)) {
		(*this)->geefKind(rotatieLinks)->geefKind(!rotatieLinks)->ouder = (*this)->geefKind(rotatieLinks).get();
	}
}



/*
 draai telkens in richting tot de boom een gelinkte lijst wordt.
 Dus bv roteren naar rechts tot je ziet dat het linkerkind leeg is,
 dan doe je verder met hetzelfde op het rechterkind
*/
template<class Sleutel, class Data>
void ZoekBoom<Sleutel, Data>::maakOnevenwichtig(Richting richting) { 

	bool rotatieLinks = richting == Richting::LINKS ? true : false;
	ZoekBoom<Sleutel, Data>* huidige = this;

	while ((*huidige)->geefKind(rotatieLinks)) {
		while ((*huidige)->geefKind(!rotatieLinks)) {
			huidige->roteer(richting);
		}
		if ((*huidige)->geefKind(rotatieLinks)) {
			huidige = &((*huidige)->geefKind(rotatieLinks));
		}	
	}
}


template<class Sleutel, class Data>
void ZoekBoom<Sleutel, Data>::maakEvenwichtig() {
	//TODO 
}


template<class Sleutel, class Data>
bool ZoekBoom<Sleutel, Data>::repOK() const
{
	const Sleutel* vorige = 0;
	bool ok = true;
	this->inorder([&vorige, &ok](const ZoekKnoop<Sleutel, Data>& knoop) {

		// Controleer ofdat de sleutels in de juiste volgorde in de boom zitten.
		if (vorige && knoop.sleutel < *vorige) {
			ok = false;
		}
		vorige = &(knoop.sleutel);


		// Nog te testen: 
		//	* Check ofdat de wortel voor het ouderveld een nullpointer heeft
		//  * Controleer ouderpointers bij elke knoop
		return;
	});
	return ok;
}


