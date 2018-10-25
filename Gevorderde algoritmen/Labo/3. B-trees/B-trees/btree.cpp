#include "btree.h"
#include "bknoop.h"
#include <fstream>
#include <stack>


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

// Eenvoudigste geval: de sleutel zit al in de boom, en moet dan gewoon aangepast worden
// Anders: zoek het blad waarin het element moet komen. Er zijn dan 2 gevallen:
// 1) Indien k < m(GROOTTE) in het blad, dan is er nog plaats in het blad en kan het element toegevoegd worden.
// 2) Anders is het blad vol, dit blad moet nu in twee delen gesplitst worden zodat:
//		a) Een mediaan moet gekozen worden
//		b) Alle waarden kleiner dan deze mediaan komen in het linkerdeel en alle waarden groter dan de mediaan komen in het rechterdeel
//		c) De mediaan wordt toegevoegd in de ouderknoop van dit blad, en het proces KAN zich herhalen,
//			indien dit de wortel bereikt, moet een nieuwe wortel aangemaakt worden met als gevolg dat de boom een niveau extra krijgt
template<class T, class D, unsigned int m>
void Btree<T, D, m>::voegToe(const T& s, const D& d) {

	Bknoop<T, D, m> huidigeKnoop = wortel; // KOPIE van de wortel
	blokindex huidigeIndex = wortelindex;
	std::stack<blokindex> gebruikteBlokIndices; // nodig om terug te verwijzen naar ouderknopen indien een knoop gesplitst moet worden

	while (!huidigeKnoop.isblad) {
		if (huidigeKnoop.bevatSleutel(s)) {
			// sleutel zit in huidige knoop, data vervangen en opnieuw schrijven naar de schijf
			int index = huidigeKnoop.geefIndexVoorSleutel(s);
			huidigeKnoop.setDataVoorSleutel(s, d);
			if (huidigeIndex == wortelindex) { // speciaal geval voor wanneer enkel de wortel aangepast wordt, aangezien huidigeKnoop slechts een kopie is
											   // zelfde redenering voor alle andere keren dat deze lijn voorkomt
				wortel = huidigeKnoop;
			}
			schijf.herschrijf(huidigeKnoop, index);
			return;
		}
		// sleutel zit niet in de huidige knoop, zoek naar de volgende knoop waarin de sleutel zich zou kunnen bevinden
		gebruikteBlokIndices.push(huidigeIndex);
		huidigeIndex = huidigeKnoop.geefBlokindexVoorSleutel(s);
		schijf.lees(huidigeKnoop, huidigeIndex);
	}


	// op dit moment zitten we in een blad, mogelijke gevallen:
	//   1) De sleutel die we willen toevoegen zit al in de knoop, enkel de data aanpassen voor die sleutel.
	//   2) De sleutel zit nog niet in de knoop, maar er is genoeg plaats om aan de knoop toe te voegen.
	//   3) Er is geen plaats meer in de knoop en moet dus opgesplitst worden.


	if (huidigeKnoop.bevatSleutel(s)) { // (1)

		huidigeKnoop.setDataVoorSleutel(s, d);
		schijf.herschrijf(huidigeKnoop, huidigeIndex);

		if (huidigeIndex == wortelindex) {
			wortel = huidigeKnoop;
		}
		return;
	}


	if (!huidigeKnoop.isVol()) { // (2)
		huidigeKnoop.voegToe(s, d);
		schijf.herschrijf(huidigeKnoop, huidigeIndex);
		if (huidigeIndex == wortelindex) {
			wortel = huidigeKnoop;
		}
		return;
	}
	
	// (3)

	while (huidigeKnoop.isVol()) {
		int mIndex = std::ceil(huidigeKnoop.k / 2);
		T mSleutel = huidigeKnoop.sleutel[mIndex];
		D mData = huidigeKnoop.sleutel[mIndex];

		// er moet een nieuwe broerknoop gemaakt worden die het rechterdeel van mIndex bevat

		Bknoop<T, D, m> broer;
		for (int i = 0; i < m - mIndex; i++) { // de gegevens voor de broer invullen
			broer.data[i] = data[i + mIndex];
			broer.sleutel = sleutel[i + mIndex];
			data[i + mIndex] == nullptr;
			sleutel[i + mIndex] == nullptr;
			k++;
		}

		broerIndex = huidigeIndex + 1; // -> klopt niet
		huidigeIndex = gebruikteBlokIndices.top();
		gebruikteBlokIndices.pop();

		schijf.schrijf(broer); // de broer al wegschrijven
	}

	// Er wordt een nieuwe wortel gemaakt
}





/*ITERATOR*/
template<class T, class D, unsigned int m>
typename Btree<T, D, m>::iterator Btree<T, D, m>::begin()
{
	return iterator();
}

template<class T, class D, unsigned int m>
typename Btree<T, D, m>::iterator Btree<T, D, m>::end()
{
	return iterator();
}
