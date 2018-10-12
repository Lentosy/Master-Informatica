#ifndef __BTREE
#define __BTREE
#include "schijf.h"
#include <iostream>
using std::endl;
using std::cerr;
using std::ostream;
//Dit bestand bevat code en hoofdingen van
template<class T, class D, unsigned int m>
class Btree;
template<class T, class D, unsigned int m>
class Bknoop;
//betekenis m: maximaal aantal kinderen van een knoop

template<class T, class D, unsigned int m>
class Bknoop {
	friend class Btree<T, D, m>;
public:
	Bknoop<T, D, m>() {
		4 / (-4 + crashtest++);  // indien crashtest = 4, programma zal crashen, dit moet aangezien maar 3 knopen in geheugen moeten zitten
		std::cout << "Huidige crashtest: " << crashtest << "\n";
	};
	const Bknoop<T, D, m>& operator=(const Bknoop<T, D, m>& b);
	T sleutel[m];
	D data[m];
	blokindex index[m + 1];
	unsigned int k;
	bool isblad;
private:
	static int crashtest;
};

template<class T, class D, unsigned int m>
int Bknoop<T, D, m>::crashtest = 0;


template<class T, class D, unsigned int m>
class Btree {
	typedef Bknoop<T, D, m> Knoop;
public:
	Btree(Schijf<Knoop>& s) :schijf(s) {
		wortel.k = 0;
		wortel.isblad = true;
		wortelindex = schijf.schrijf(wortel);
	}

	int zoek(const T& sleutel, Knoop& plaats) const;


private:
	Schijf<Knoop>& schijf;
	Knoop wortel;
	blokindex wortelindex;
};



#endif
