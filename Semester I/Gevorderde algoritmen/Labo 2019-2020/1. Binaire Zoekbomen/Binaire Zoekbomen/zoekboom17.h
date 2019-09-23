#pragma once
#ifndef __Zoekboom_H
#define __Zoekboom_H
#include <cstdlib>
#include <iostream>
#include <queue>
#include <memory>
#include <functional>
#include <fstream>
#include <sstream>

using std::ostream;
using std::ofstream;
using std::ostringstream;
using std::unique_ptr;
using std::cerr;
using std::pair;
using std::string;
/**********************************************************************

   Class: Zoekboom

   beschrijving: Binaire Zoekboom waarin duplicaatsleutels wel of niet zijn toegestaan.

***************************************************************************/

template <class Sleutel, class Data>
class zoekKnoop;

template <class Sleutel, class Data>
class Zoekboom : public unique_ptr<zoekKnoop<Sleutel, Data>> {
	//....move en copy. Noot: als er geen copy nodig is, zet hem beste op delete.
public:
	void inorder(std::function<void(const zoekKnoop<Sleutel, Data>&)> bezoek) const;
	void schrijf(ostream& os) const;
	void teken(const char* bestandsnaam);
	string tekenrec(ostream& uit, int& knoopteller);


	//te implementeren
	bool repOK() const;
	int geefDiepte();
	// geefBoomBovenKnoop: gegeven een knooppointer, wele boom wijst naar de knoop
	// preconditie: knoop moet een naar een geldige knoop wijzen.
	Zoekboom<Sleutel, Data>* geefBoomBovenKnoop(zoekKnoop<Sleutel, Data>& knoopptr);
	void voegtoe(const Sleutel& sleutel, const Data& data, bool dubbelsToestaan = false);

protected:
	//zoekfunctie zoekt sleutel en geeft de boom in waaronder de sleutel zit (eventueel een lege boom als de sleutel
	//ontbreekt) en de pointer naar de ouder (als die bestaat, anders nulpointer).
	//noot: alhoewel de functie niets verandert aan de boom is ze geen const functie.
	void zoek(const Sleutel& sleutel, zoekKnoop<Sleutel, Data>*& ouder, Zoekboom<Sleutel, Data>*& plaats);
};

template <class Sleutel, class Data>
class zoekKnoop {
	friend class Zoekboom<Sleutel, Data>;
public:
	zoekKnoop() :ouder(0) {}
	zoekKnoop(const Sleutel& sl, const Data& d) :sleutel{ sl }, data(d), ouder(0){};
	zoekKnoop(Sleutel&& sl, Data&& d) :sleutel{ move(sl) }, data(move(d)), ouder(0){};
	Zoekboom<Sleutel, Data>& geefKind(bool links);
	Sleutel sleutel;
	Data data;
	zoekKnoop<Sleutel, Data>* ouder;
	Zoekboom<Sleutel, Data> links, rechts;
};


/*****************************************************************************

	Implementatie

*****************************************************************************/


template <class Sleutel, class Data>
void Zoekboom<Sleutel, Data>::inorder(std::function<void(const zoekKnoop<Sleutel, Data>&)> bezoek) const {
	if (*this) {
		(*this)->links.inorder(bezoek);
		bezoek(**this);
		(*this)->rechts.inorder(bezoek);
	};
}

template <class Sleutel, class Data>
void Zoekboom<Sleutel, Data>::schrijf(ostream& os) const {
	inorder([&os](const zoekKnoop<Sleutel, Data>& knoop) {
		os << "(" << knoop.sleutel << " -> " << knoop.data << ")";
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
void Zoekboom<Sleutel, Data>::teken(const char* bestandsnaam) {
	ofstream uit(bestandsnaam);
	assert(uit);
	int knoopteller = 0;//knopen moeten een eigen nummer krijgen.
	uit << "digraph {\n";
	this->tekenrec(uit, knoopteller);
	uit << "}";
}

template <class Sleutel, class Data>
string Zoekboom<Sleutel, Data>::tekenrec(ostream& uit, int& knoopteller) {
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
Zoekboom<Sleutel, Data>* Zoekboom<Sleutel, Data>::geefBoomBovenKnoop(zoekKnoop<Sleutel, Data>& knoop) {
	if (knoop.ouder == 0)
		return this;
	else
		if (knoop.ouder->links.get() == &knoop)
			return &(knoop.ouder->links);
		else
			return &(knoop.ouder->rechts);
}

template <class Sleutel, class Data>
void Zoekboom<Sleutel, Data>::voegtoe(const Sleutel& sleutel, const Data& data, bool dubbelsToestaan) {
	zoekKnoop<Sleutel, Data>* ouder;
	Zoekboom<Sleutel, Data>* plaats;
	Zoekboom<Sleutel, Data>::zoek(sleutel, ouder, plaats);
	if (dubbelsToestaan)
		while (*plaats)
			(*plaats)->geefKind(random() % 2).zoek(sleutel, ouder, plaats);
	if (!*plaats) {
		Zoekboom<Sleutel, Data> nieuw =
			std::make_unique<zoekKnoop<Sleutel, Data> >(sleutel, data);
		nieuw->ouder = ouder;
		*plaats = move(nieuw);
	}
}


template <class Sleutel, class Data>
void Zoekboom<Sleutel, Data>::zoek(const Sleutel& sleutel, zoekKnoop<Sleutel, Data>*& ouder, Zoekboom<Sleutel, Data>*& plaats) {
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
Zoekboom<Sleutel, Data>& zoekKnoop<Sleutel, Data>::geefKind(bool linkerkind) {
	if (linkerkind)
		return links;
	else
		return rechts;
};


#endif
