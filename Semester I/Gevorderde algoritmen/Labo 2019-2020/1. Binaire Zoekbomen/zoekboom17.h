#pragma once
#ifndef __ZoekBoom_H
#define __ZoekBoom_H
#include <cstdlib>
#include <iostream>
#include <queue>
#include <memory>
#include <functional>
#include <fstream>
#include <sstream>
#include <cassert>
#include <cstdlib>

using std::ostream;
using std::ofstream;
using std::ostringstream;
using std::unique_ptr;
using std::cerr;
using std::pair;
using std::string;
/**********************************************************************

   Class: ZoekBoom

   beschrijving: Binaire ZoekBoom waarin duplicaatsleutels wel of niet zijn toegestaan.

***************************************************************************/

enum class Richting { LINKS, RECHTS };

template <class Sleutel, class Data>
class ZoekKnoop;

template <class Sleutel, class Data>
class ZoekBoom : public unique_ptr<ZoekKnoop<Sleutel, Data>> {
public:

	using std::unique_ptr<ZoekKnoop<Sleutel, Data>>::unique_ptr;

	void inorder(std::function<void(const ZoekKnoop<Sleutel, Data>&)> bezoek) const;
	void schrijf(ostream& os) const;
	void teken(const char* bestandsnaam);
	string tekenrec(ostream& uit, int& knoopteller);


	//te implementeren
	bool repOK() const;
	int geefDiepte() const;
	void roteer(Richting richting);

	// Maakt ofwel een rechts-onevenwichtige of links-onevenwichtige boom.
	void maakOnevenwichtig(Richting richting);

	void maakEvenwichtig();
	// geefBoomBovenKnoop: gegeven een knooppointer, wele boom wijst naar de knoop
	// preconditie: knoop moet een naar een geldige knoop wijzen.
	ZoekBoom<Sleutel, Data>* geefBoomBovenKnoop(ZoekKnoop<Sleutel, Data>& knoopptr);
	void voegtoe(const Sleutel& sleutel, const Data& data, bool dubbelsToestaan = false);

protected:
	//zoekfunctie zoekt sleutel en geeft de boom in waaronder de sleutel zit (eventueel een lege boom als de sleutel
	//ontbreekt) en de pointer naar de ouder (als die bestaat, anders nulpointer).
	//noot: alhoewel de functie niets verandert aan de boom is ze geen const functie.
	void zoek(const Sleutel& sleutel, ZoekKnoop<Sleutel, Data>*& ouder, ZoekBoom<Sleutel, Data>*& plaats);
};

template <class Sleutel, class Data>
class ZoekKnoop {
	friend class ZoekBoom<Sleutel, Data>;
public:
	ZoekKnoop() :ouder(0) {}
	ZoekKnoop(const Sleutel& sl, const Data& d) :sleutel{ sl }, data(d), ouder(0){};
	ZoekKnoop(Sleutel&& sl, Data&& d) :sleutel{ std::move(sl) }, data(std::move(d)), ouder(0){};
	ZoekBoom<Sleutel, Data>& geefKind(bool naarLinks);
	Sleutel sleutel;
	Data data;
	ZoekKnoop<Sleutel, Data>* ouder;
	ZoekBoom<Sleutel, Data> links, rechts;
};





/*****************************************************************************

	Implementatie

*****************************************************************************/



template <class Sleutel, class Data>
void ZoekBoom<Sleutel, Data>::inorder(std::function<void(const ZoekKnoop<Sleutel, Data>&)> bezoek) const {
	if (*this) {
		(*this)->links.inorder(bezoek);
		bezoek(**this);
		(*this)->rechts.inorder(bezoek);
	};
}

template <class Sleutel, class Data>
void ZoekBoom<Sleutel, Data>::schrijf(ostream& os) const {
	inorder([&os](const ZoekKnoop<Sleutel, Data>& knoop) {
		os << "(" << knoop.sleutel << " -> " << knoop.data << ")";

		os << "\n  Ouder: ";
		if (knoop.ouder)
			os << knoop.ouder->sleutel;
		else
			os << "-----";


		os << "\n  Linkerkind: ";
		if (knoop.links)
			os << knoop.links->sleutel;
		else
			os << "-----";

		os << "\n  Rechterkind: ";
		if (knoop.rechts)
			os << knoop.rechts->sleutel;
		else
			os << "-----";
		os << "\n";
	});
}

template <class Sleutel, class Data>
void ZoekBoom<Sleutel, Data>::teken(const char* bestandsnaam) {
	ofstream uit(bestandsnaam);
	assert(uit);
	int knoopteller = 0;//knopen moeten een eigen nummer krijgen.
	uit << "digraph {\n";
	this->tekenrec(uit, knoopteller); //C26444 error omdat de returnwaarde van de functie niet gebruikt wordt (enkel voor de wortel)
	uit << "}";
}

template <class Sleutel, class Data>
string ZoekBoom<Sleutel, Data>::tekenrec(ostream& uit, int& knoopteller) {
	ostringstream wortelstring;
	wortelstring << '"' << ++knoopteller << '"';
	
	if (!*this) {
		uit << wortelstring.str() << " [shape=point];\n";
	}
	else {
		uit << wortelstring.str() << "[label=\"" << (*this)->sleutel << ":" << (*this)->data << "\"]";
		uit << ";\n";
		

		string linkskind = (*this)->links.tekenrec(uit, knoopteller);
		string rechtskind = (*this)->rechts.tekenrec(uit, knoopteller);
		
		uit << wortelstring.str() << " -> " << linkskind << ";\n";
		uit << wortelstring.str() << " -> " << rechtskind << ";\n";
	};


	return wortelstring.str();
}



template <class Sleutel, class Data>
ZoekBoom<Sleutel, Data>* ZoekBoom<Sleutel, Data>::geefBoomBovenKnoop(ZoekKnoop<Sleutel, Data>& knoop) {
	if (knoop.ouder == 0)
		return this;
	else
		if (knoop.ouder->links.get() == &knoop)
			return &(knoop.ouder->links);
		else
			return &(knoop.ouder->rechts);
}

template <class Sleutel, class Data>
void ZoekBoom<Sleutel, Data>::voegtoe(const Sleutel& sleutel, const Data& data, bool dubbelsToestaan) {
	ZoekKnoop<Sleutel, Data>* ouder;
	ZoekBoom<Sleutel, Data>* plaats;
	ZoekBoom<Sleutel, Data>::zoek(sleutel, ouder, plaats);
	if (dubbelsToestaan)
		while (*plaats) 
			(*plaats)->geefKind(rand() % 2).zoek(sleutel, ouder, plaats);

	if (!*plaats) {
		ZoekBoom<Sleutel, Data> nieuw =
			std::make_unique<ZoekKnoop<Sleutel, Data> >(sleutel, data);
		nieuw->ouder = ouder;
		*plaats = std::move(nieuw);
	}
}


template <class Sleutel, class Data>
void ZoekBoom<Sleutel, Data>::zoek(const Sleutel& sleutel, ZoekKnoop<Sleutel, Data>*& ouder, ZoekBoom<Sleutel, Data>*& plaats) {
	plaats = this;
	ouder = 0;
	while (*plaats && (*plaats)->sleutel != sleutel) {
		ouder = plaats->get();
		if ((*plaats)->sleutel < sleutel)
			plaats = &(*plaats)->rechts;
		else
			plaats = &(*plaats)->links;
	};
};

template <class Sleutel, class Data>
ZoekBoom<Sleutel, Data>& ZoekKnoop<Sleutel, Data>::geefKind(bool naarLinks) {
	if (naarLinks)
		return links;
	else
		return rechts;
};


#endif
