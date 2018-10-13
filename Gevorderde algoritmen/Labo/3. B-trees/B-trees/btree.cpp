#include "btree.h"
#include "bknoop.h"
#include <fstream>
#include <sstream>




template<class T, class D, unsigned int m>
std::pair<blokindex, int>* Btree<T, D, m>::zoek(const T& s) const {
	
	std::pair<blokindex, int>* res;
	Bknoop<T, D, m> huidigeKnoop = wortel;
	blokindex huidigeBlokindex = wortelindex;
	while (!huidigeKnoop.isblad) {
		if (huidigeKnoop.bevatSleutel(sleutel)) {
			res = std::make_pair(huidigeBlokindex, huidigeKnoop.geefIndexVanSleutel(sleutel));
			return res;
		}

		huidigeBlokindex = huidigeKnoop.geefBlokindexVoorSleutel(sleutel);
		schijf.lees(huidigeKnoop, huidigeBlokindex);
	}
	//huidigeknoop is op dit moment een blad
	if (!huidigeKnoop.bevatSleutel(sleutel)) {
		// sleutel zit niet in btree
	}
	res = std::make_pair(huidigeBlokindex, huidigeKnoop.geefIndexVanSleutel(sleutel));
	return res;

}