#include "btree.h"
#include "bknoop.h"
#include <fstream>


template<class T, class D, unsigned int m>
D Btree<T, D, m>::zoek(const T& s) const {
	Bknoop<T, D, m> huidigeKnoop = wortel;
	blokindex huidigeIndex = wortelindex;

	while (!huidigeKnoop.isblad) {
		if (huidigeKnoop.bevatSleutel(s)) {
			return huidigeKnoop.geefDataVoorSleutel(s);
		}
		huidigeIndex = huidigeKnoop.geefIndexVoorSleutel(s);
		schijf.lees(huidigeKnoop, huidigeIndex);
	}
	if (huidigeKnoop.bevatSleutel(s)) {
		return huidigeKnoop.geefDataVoorSleutel(s);
	}
	return D(); // wat returnen indien niet gevonden?

}

template<class T, class D, unsigned int m>
void Btree<T, D, m>::voegToe(const T& s, const D& d) {
	// Zoek het blad waarin het element moet komen. Er zijn dan 2 gevallen:
	// 1) Indien k < m(GROOTTE) in het blad, dan is er nog plaats in het blad en kan het element toegevoegd worden.
	// 2) Anders is het blad vol, dit blad moet nu in twee delen gesplitst worden zodat:
	//		a) Een mediaan moet gekozen worden
	//		b) Alle waarden kleiner dan deze mediaan komen in het linkerdeel en alle waarden groter dan de mediaan komen in het rechterdeel
	//		c) De mediaan wordt toegevoegd in de ouderknoop van dit blad, en het proces KAN zich herhalen,
	//			indien dit de wortel bereikt, moet een nieuwe wortel aangemaakt worden met als gevolg dat de boom een niveau extra krijgt
	Bknoop<T, D, m> huidigeKnoop = wortel;
	blokindex huidigeIndex = wortelindex;

	while (!huidigeKnoop.isblad) {

	}


	// op dit moment zitten we in een blad
		//beste geval, er is nog plaats in de knoop, sleutel gewoon toevoegen, eventueel sleutels terug in volgorde zetten

	huidigeKnoop.voegToe(s, d);
	schijf.herschrijf(huidigeKnoop, huidigeIndex);


}
