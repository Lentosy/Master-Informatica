#include "splayboom.h"


template <class Sleutel, class Data>
void Splayboom<Sleutel, Data>::splay(Boom<Sleutel, Data>* huidigePlaats) {

	// Controle bestaan van knoop en dat die minstens een ouder heeft
	if(!huidigePlaats){
		return;
	}
	// if statements niet samennemen, dit moet met een OF, maar als huidigePlaats een nullptr is, krijgen we een exceptie bij het opvragen van de ouder
	if(!(*huidigePlaats)->ouder) {
		return;
	}

	
	// Er zijn 6 gevallen, die uiteenvallen in 2 groepen van 3 gevallen die elkaar symmetrie zijn
	while(huidigePlaats != this){
		bool huidigePlaatsIsLinkerkind = (*huidigePlaats) == (*huidigePlaats)->ouder->links;
		bool huidigePlaatsHeeftGrootouder = (*huidigePlaats)->ouder->ouder;
		Boom<Sleutel, Data>* ouderBoom = geefBoomBovenKnoop(*((*huidigePlaats)->ouder));
		// 1. Als er geen grootouder is, wordt de ZIG uitgevoerd
		//    Dit is de laatste rotatie en zorgt ervoor dat de knoop de wortel wordt.
		if(!huidigePlaatsHeeftGrootouder){
			// Er moet enkel een rotatie uitgevoerd in de andere richting
			ouderBoom->roteer(!huidigePlaatsIsLinkerkind);

		} else {
			// 2. Er is wel een grootouder, er zijn nu twee gevallen.
			Boom<Sleutel, Data>* grootOuderBoom = geefBoomBovenKnoop(*((*ouderBoom)->ouder));
			bool ouderIsLinkerkind = (*ouderBoom) == (*grootOuderBoom)->links; 
			// 2a. De knoop en de ouder liggen op één lijn, zodat de ZIG ZIG uitgevoerd kan worden
			if(huidigePlaatsIsLinkerkind == ouderIsLinkerkind){
				grootOuderBoom->roteer(!huidigePlaatsIsLinkerkind);
				grootOuderBoom->roteer(!huidigePlaatsIsLinkerkind);
			} 
			// 2b . De knoop en ouder liggen niet op één lijn, zodat de ZIG ZAG uitgevoerd kan worden 
			else {
				ouderBoom->roteer(!huidigePlaatsIsLinkerkind);
				grootOuderBoom->roteer(huidigePlaatsIsLinkerkind);
			}
			huidigePlaats = grootOuderBoom;
		}
	}
}


template <class Sleutel, class Data>
void Splayboom<Sleutel, Data>::voegtoe(const Sleutel& sleutel,const Data& data,bool dubbelsToestaan) {
	Boom<Sleutel, Data>::voegtoe(sleutel, data, dubbelsToestaan);
};

template <class Sleutel, class Data>
Knoop<Sleutel, Data>* Splayboom<Sleutel, Data>::zoek(const Sleutel& sleutel) {
	Knoop<Sleutel, Data>* ouder;
	Boom<Sleutel, Data>* plaats;
	Boom<Sleutel, Data>::zoek(sleutel, ouder, plaats);
	Knoop<Sleutel, Data>* gezochteKnoop = plaats->get();

	splay(plaats);
	
	return gezochteKnoop;
}