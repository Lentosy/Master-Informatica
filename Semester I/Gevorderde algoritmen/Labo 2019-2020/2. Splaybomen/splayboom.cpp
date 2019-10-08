#include "splayboom.h"

/* VANAF HIER BEGINNEN DE DEFINITIES VOOR EEN BOTTOM UP SPLAYBOOM */

template <class Sleutel, class Data>
void SplayboomBottomUp<Sleutel, Data>::zig(Boom<Sleutel, Data>*& knoop, bool naarLinks) {
	Boom<Sleutel, Data>* ouder = this->geefBoomBovenKnoop(*((*knoop)->ouder));
	ouder->roteer(naarLinks);
	knoop = ouder;
}

template <class Sleutel, class Data>
void SplayboomBottomUp<Sleutel, Data>::zigzig(Boom<Sleutel, Data>*& knoop, bool naarLinks) {
	Boom<Sleutel, Data>* ouder = this->geefBoomBovenKnoop(*((*knoop)->ouder));
	Boom<Sleutel, Data>* grootouder = this->geefBoomBovenKnoop(*((*ouder)->ouder));
	grootouder->roteer(naarLinks);
	grootouder->roteer(naarLinks);
	knoop = grootouder;
}

template <class Sleutel, class Data>
void SplayboomBottomUp<Sleutel, Data>::zigzag(Boom<Sleutel, Data>*& knoop, bool naarLinks) {
	Boom<Sleutel, Data>* ouder = this->geefBoomBovenKnoop(*((*knoop)->ouder));
	Boom<Sleutel, Data>* grootouder = this->geefBoomBovenKnoop(*((*ouder)->ouder));
	ouder->roteer(naarLinks);
	grootouder->roteer(!naarLinks);
	knoop = grootouder;
}

template <class Sleutel, class Data>
void SplayboomBottomUp<Sleutel, Data>::splay(Boom<Sleutel, Data>* huidigeKnoop) {

	// Controle: knoop bestaat en heeft een ouder, anders moet er niet gesplayed worden
	if(!huidigeKnoop){
		return;
	}
	// if statements niet samennemen, dit moet met een OF, maar als huidigeKnoop een nullptr is krijgen we een exceptie bij het opvragen van de ouder
	if(!(*huidigeKnoop)->ouder) {
		return;
	}

	// Er zijn 6 gevallen, die uiteenvallen in 2 groepen van 3 gevallen die elkaar symmetrie zijn
	while(huidigeKnoop != this){
		bool huidigeKnoopIsLinkerkind = (*huidigeKnoop) == (*huidigeKnoop)->ouder->links;
		bool huidigeKnoopHeeftGrootouder = (*huidigeKnoop)->ouder->ouder;
		Boom<Sleutel, Data>* ouderBoom = geefBoomBovenKnoop(*((*huidigeKnoop)->ouder));

		// 1. De ouder van de knoop is wortel van de boom.
		if(!huidigeKnoopHeeftGrootouder) 
			this->zig(huidigeKnoop, !huidigeKnoopIsLinkerkind);
		else {
			// 2. De knoop heeft nog een grootouder.
			Boom<Sleutel, Data>* grootOuderBoom = geefBoomBovenKnoop(*((*ouderBoom)->ouder));
			bool ouderIsLinkerkind = (*ouderBoom) == (*grootOuderBoom)->links; 

			// 2a. De knoop en zijn ouder zijn beide linker (of rechter) kind
			if(huidigeKnoopIsLinkerkind == ouderIsLinkerkind) 
				this->zigzig(huidigeKnoop, !huidigeKnoopIsLinkerkind);
			// 2b. De knoop is een linkerkind (rechterkind) terwijl zijn ouder een rechterkind (linkerkind) is.
			else 
				this->zigzag(huidigeKnoop, !huidigeKnoopIsLinkerkind);
			
			huidigeKnoop = grootOuderBoom;
		}
	}
}


template <class Sleutel, class Data>
void SplayboomBottomUp<Sleutel, Data>::voegtoe(const Sleutel& sleutel,const Data& data,bool dubbelsToestaan) {
	Boom<Sleutel, Data>::voegtoe(sleutel, data, dubbelsToestaan);
	this->zoek(sleutel); // de zoekfunctie van de splayboom zal splayen -> slecht design
};


template <class Sleutel, class Data>
Knoop<Sleutel, Data>* SplayboomBottomUp<Sleutel, Data>::zoek(const Sleutel& sleutel) {
	Knoop<Sleutel, Data>* gezochteKnoop = Boom<Sleutel, Data>::zoek(sleutel);
	if(gezochteKnoop){ // Als de knoop niet gevonden wordt, moet de opvolger of voorganger tot wortel gemaakt worden
		splay(this->geefBoomBovenKnoop(*gezochteKnoop));
	}
	return gezochteKnoop;
};


/* VANAF HIER BEGINNEN DE DEFINITIES VOOR EEN TOP DOWN SPLAYBOOM */


// TODO, maar geen zin

template <class Sleutel, class Data>
Knoop<Sleutel, Data>* SplayboomTopDown<Sleutel, Data>::zoek(const Sleutel& sleutel) {
	// Er zijn drie gevallen, afhankelijk of we naar links of rechts moeten afdalen
	// Er is altijd een ouder P, die de ouder is van het huidige kind C

	Boom<Sleutel, Data>* L;
	Boom<Sleutel, Data>* R;
	Boom<Sleutel, Data>* M = this;


	bool huidigeKnoopIsLinkerkind = sleutel < (*M)->sleutel;
	// 1. C is de laatste knoop op de zoekweg
	
	//this->zig(*L, L, *R, R, huidigeKnoopIsLinkerkind)
	

	

}
