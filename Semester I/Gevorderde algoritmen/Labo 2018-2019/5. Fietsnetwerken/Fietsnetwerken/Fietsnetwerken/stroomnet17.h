#ifndef __STROOMNET_H
#define __STROOMNET_H
#include "graaf.h"
#include <cassert>
#include <iostream>
#include <functional>
using std::vector;
using std::function;
using std::ostream;

template< class T>
class Stroomnetwerk;


template< class T >
class Pad :public std::vector< int > {
public:
	T geefCapaciteit() const {
		return capaciteit;
	}
	void zetCapaciteit(const T& _capaciteit) {
		capaciteit = _capaciteit;
	}
	friend ostream& operator<<(ostream& os, const Pad& p) {
		os << "Capaciteit= " << p.capaciteit << " :: ";
		if (p.size() > 0) {
			os << p[0];
		}
		for (int i = 1; i < p.size(); i++) {
			os << "->" << p[i];
		}
		os << "\n";
		return os;
	}
protected:
	T capaciteit;
};
/**********************************************************************

   Class:VergrotendPad

   beschrijving: Methodeklasse die, gegeven een stroomnetwerk,
				 een vergrotend pad teruggeeft.
				 Vermits ze hoort bij Ford-Fulkerson zal een object van deze klasse
				 elke keer een ander pad geven als het stroomnetwerk opgegeven
				 in de constructor verandert.


***************************************************************************/
template <class T>
class Vergrotendpadzoeker {
public:
	Vergrotendpadzoeker(const Stroomnetwerk<T>& stroomnetwerk) :
		stroomnetwerk(stroomnetwerk), producent(stroomnetwerk.van), verbruiker(stroomnetwerk.naar),
		gebruikteBuren(stroomnetwerk.aantalKnopen()), aanwezigheidslijst(stroomnetwerk.aantalKnopen(), false) {
	};
	Pad<T> geefVergrotendPad();
protected:
	virtual void geefVergrotendPad(int t, int x, Pad<T>& p);
	const Stroomnetwerk<T>& stroomnetwerk;
	// elke index stelt een knoop voor
	// de waarde die bij die index hoort is het knoopnummer dat we gebruikt hebben om tot de knoop 
	// bijhorend tot de knoop met het indexnummer te komen
	vector<int> gebruikteBuren; 
	vector<bool> aanwezigheidslijst; // lijst van knopen die in het vergrotend pad zitten
	int producent, verbruiker;
};


template <class T>
Pad<T>Vergrotendpadzoeker<T>::geefVergrotendPad() {
	for (int i = 0; i < aanwezigheidslijst.size(); i++) {
		aanwezigheidslijst[i] = false;
	}
	Pad<T> pad;
	assert(producent != verbruiker);
	geefVergrotendPad(producent, 0, pad);
	assert(pad.size() != 1);

	// de bottleneck van het pad bepalen = de verbinding met de kleinste capaciteit
	if (pad.size() > 1) {
		T bottleneck = *stroomnetwerk.geefTakdata(pad[0], pad[1]);
		for (int i = 2; i < pad.size(); i++) {
			T vergelijkBottleneck = *stroomnetwerk.geefTakdata(pad[i - 1], pad[i]);
			if (vergelijkBottleneck < bottleneck)
				bottleneck = vergelijkBottleneck;
		}
		pad.zetCapaciteit(bottleneck);
	}
	return pad;
}


template <class T>
void Vergrotendpadzoeker<T>::geefVergrotendPad(int huidigeKnoop, int x, Pad<T>& pad) {
	aanwezigheidslijst[huidigeKnoop] = true;
	const typename GraafMetTakdata<GERICHT, T>::Burenlijst& buren = stroomnetwerk[huidigeKnoop];
	int padLengte = x + 1;
	for (typename GraafMetTakdata<GERICHT, T>::Burenlijst::const_iterator it = buren.begin(); it != buren.end(); it++) {
		int buur = it->first;
		if (*stroomnetwerk.geefTakdata(huidigeKnoop, buur) > 0) {
			if (buur == verbruiker && padLengte + 1 > pad.size()) {
				gebruikteBuren[verbruiker] = huidigeKnoop;
				pad.resize(padLengte + 1);
				int padKnoop = verbruiker;
				int i = padLengte;
				while (padKnoop != producent) {
					pad[i--] = padKnoop;
					padKnoop = gebruikteBuren[padKnoop];
				}
				pad[0] = padKnoop;
			} else if (buur != verbruiker && !aanwezigheidslijst[buur]) {
				gebruikteBuren[buur] = huidigeKnoop;
				geefVergrotendPad(buur, padLengte, pad);
			}
		}
	}
}


/**********************************************************************

   Class: Stroomnetwerk

   beschrijving: Een stroomnetwerk gaat uit van een gewogen gerichte graaf
				 die in de constructor wordt opgegeven

***************************************************************************/

template <class T>//T = takdata
class Stroomnetwerk :public GraafMetTakdata<GERICHT, T > {
public:
	//leeg netwerk; alleen aantal knopen en van en naar gegeven.
	Stroomnetwerk(int grootte, int _van, int _naar) :
		Graaf<GERICHT>(grootte), GraafMetTakdata<GERICHT, T>(grootte), van(_van), naar(_naar) {};
	//Copyconstructor. Let op: Graaf<GERICHT>(gr) moet toegevoegd,
	//anders roept de copyconstructor van GraafMetTakdata de defaultconstructor
	//van Graaf op en krijgen we een lege graaf.
	Stroomnetwerk(const GraafMetTakdata<GERICHT, T>& gr, int _van, int _naar) :
		Graaf<GERICHT>(gr), GraafMetTakdata<GERICHT, T>(gr), van(_van), naar(_naar) {};
	Stroomnetwerk(const Stroomnetwerk<T>& gr) :
		Graaf<GERICHT>(gr), GraafMetTakdata<GERICHT, T>(gr), van(gr.van), naar(gr.naar) {};
	Stroomnetwerk(Stroomnetwerk<T>&& gr) :Stroomnetwerk(0, 0, 0) {
		swap(this->burenlijsten, gr.burenlijsten);
		swap(this->vrijgekomenVerbindingsnummers, gr.vrijgekomenVerbindingsnummers);
		std::swap(this->hoogsteVerbindingsnummer, gr.hoogsteVerbindingsnummer);
		swap(this->takdatavector, gr.takdatavector);
		std::swap(this->van, gr.van);
		std::swap(this->naar, gr.naar);
	};

	Stroomnetwerk<T> geefStroom() {
		Stroomnetwerk<T> oplossing(this->aantalKnopen(), van, naar);
		Stroomnetwerk<T> restnetwerk(*this);
		Vergrotendpadzoeker<T> vg(restnetwerk);
		Pad<T> vergrotendpad = vg.geefVergrotendPad();

		while (vergrotendpad.size() != 0) {
			restnetwerk -= vergrotendpad;
			oplossing += vergrotendpad;
			vergrotendpad = vg.geefVergrotendPad();
		}

		return oplossing;
	}

	//////////////// EIGEN IMPLEMENTATIE
	Stroomnetwerk<T>& operator-=(const Pad<T>& pad) {
		T capaciteit = pad.geefCapaciteit();
		for (int i = 0; i < pad.size() - 1; i++) {
			this->vergrootTak(pad[i], pad[i + 1], -pad.geefCapaciteit());
			this->vergrootTak(pad[i + 1], pad[i], pad.geefCapaciteit());
		}
		return *this;
	}

	Stroomnetwerk<T>& operator+=(const Pad<T>& pad) {
		for (int i = 0; i < pad.size() - 1; i++) {
			this->vergrootTak(pad[i], pad[i + 1], pad.geefCapaciteit());
		}
		return *this;
	}
	/////////////////////////



	void vergrootTak(int start, int eind, T delta) {
		int taknr = this->verbindingsnummer(start, eind);
		if (taknr == -1)
			taknr = this->voegVerbindingToe(start, eind, delta);
		else
			this->takdatavector[taknr] += delta;
	}
	T geefCapaciteit() {
		T som = 0;
		for (typename GraafMetTakdata<GERICHT, T>::Burenlijst::const_iterator it = this->burenlijsten[van].begin();
			it != this->burenlijsten[van].end(); it++)
			som += this->takdatavector[it->second];
		return som;
	}

	int van, naar;
protected:
	virtual std::string knooplabel(int i) const {
		std::ostringstream uit;
		if (i == van)
			uit << '"' << i << ":P\"";
		else if (i == naar)
			uit << '"' << i << ":V\"";
		else
			uit << i;
		return uit.str();
	};
};
#endif
