#ifndef __BTREE
#define __BTREE
#include "schijf.h"
#include <iostream>
#include <utility>


template<class T, class D, unsigned int m>
class Bknoop;
//betekenis m: maximaal aantal kinderen van een knoop

template<class T, class D, unsigned int m>
class Btree {
	typedef Bknoop<T, D, m> Knoop;
public:
	Btree(Schijf<Knoop>& s) :schijf(s) {
		wortel.k = 0; // aantal sleutels in de wortel op 0 zetten
		wortel.isblad = true;
		wortelindex = schijf.schrijf(wortel);
	};


	// Deze functie return een pair struct met:
	// first -> de blokindex waar de sleutel zou moeten zitten
	// second -> de index in die knoop waar de sleutel moet zitten
	D zoek(const T& s) const;
	void voegToe(const T& s, const D& d);


private:
	Schijf<Knoop>& schijf;
	Knoop wortel;
	blokindex wortelindex;
};
#endif
