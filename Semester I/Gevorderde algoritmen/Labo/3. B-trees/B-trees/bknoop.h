#ifndef __BKNOOP
#define __BKNOOP

#include "btree.h"

template<class T, class D, unsigned int m>
class Bknoop {
	friend class Btree<T, D, m>;
public:

	Bknoop<T, D, m>() {
		int x = 4 / (-4 + crashtest++);  // indien crashtest = 4, programma zal crashen, dit moet aangezien maar 3 knopen in geheugen moeten zitten
		std::cout << "Huidige crashtest: " << crashtest << "\n";
	};

	~Bknoop<T, D, m>() {
		crashtest--;
	};

	const Bknoop<T, D, m>& operator=(const Bknoop<T, D, m>& b);

	T sleutel[m];			 // een knoop bevat m aantal sleutels. Dit moet stijgend gerangschikt zijn
	D data[m];				 // bij die sleutels hoort uiteraard data
	blokindex index[m + 1];  // dit zijn verwijzingen naar de kinderen van de knoop
	unsigned int k;			 // het aantal huidige sleutels
	bool isblad;			 // indien true, we bevinden ons op het laagste niveau
private:
	bool bevatSleutel(const T& s) const;
	int geefIndexVoorSleutel(const T& s) const;
	D geefDataVoorSleutel(const T& s) const;
	blokindex geefBlokindexVoorSleutel(const T& s) const;
	void setDataVoorSleutel(const T& s, const D& d);
	void voegToe(const T& s, const D& d);
	bool isVol();
	static int crashtest;
};

template<class T, class D, unsigned int m>
int Bknoop<T, D, m>::crashtest = 0; // initialiseren van de default static waarde crashtest. Kan niet inline in de klasse zelf gebeuren


#endif