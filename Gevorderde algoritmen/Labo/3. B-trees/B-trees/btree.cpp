#include "btree.h"
#include "bknoop.h"
#include <fstream>
#include <sstream>

template<class T, class D, unsigned int m>
std::pair<blokindex, int>* Btree<T, D, m>::zoek(const T & sleutel) const {
	std::pair<blokindex, int> plaats;
	Bknoop<T, D, m> huidigeKnoop = wortel;
	blokindex vorigeBlokindex = wortelindex;
	while (!huidigeKnoop.isblad) { // de huidige knoop is nog geen blad, eerst zoeken in deze knoop ofdat sleutel bestaat
		int index = huidigeKnoop.geefIndexVanSleutel(sleutel);
		if (index != m) {
			plaats = std::make_pair(vorigeBlokindex, index);
			return &plaats;
		}
		if (index == 0) { // nodig voor berekening vorigeBlokIndex, aangezien we daar index + 1 doen
			index--;
		}
		vorigeBlokindex = huidigeKnoop.index[index + 1];
		schijf.lees(huidigeKnoop, vorigeBlokindex);
	}
	int index = huidigeKnoop.geefIndexVanSleutel(sleutel);
	plaats = std::make_pair(vorigeBlokindex, index);
	return &plaats;
};


template<class T, class D, unsigned int m>
void Btree<T, D, m>::voegToe(const T& sleutel) {
	std::pair<blokindex, int>* plaats = zoek(sleutel);
	Bknoop<T, D, m> knoop;
	schijf.lees(knoop, plaats->first);
	
}

