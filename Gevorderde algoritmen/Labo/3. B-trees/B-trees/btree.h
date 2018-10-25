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

	D zoek(const T& s) const;
	void voegToe(const T& s, const D& d);
	
	
	
	
	class iterator;
	iterator begin();
	iterator end();
private:
	Schijf<Knoop>& schijf;
	Knoop wortel;
	blokindex wortelindex;
};



template<class T, class D, unsigned int m>
class Btree<T, D, m>::iterator {
	iterator& operator++();// stack bijhouden van blokindexen want veel springen in boom aangezien maximum 3 knopen in geheugen
	bool operator==(const iterator& it) const;
	bool operator!=(const iterator& it) const;
};

#endif