#ifndef __RZWboom_H
#define __RZWboom_H
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <memory>
#include <functional>
#include <fstream>
#include <sstream>
#include <vector>

using std::ostream;
using std::ofstream;
using std::ostringstream;
using std::unique_ptr;
using std::cerr;
using std::pair;
using std::string;
/**********************************************************************

   Class: RZWboom

   beschrijving: Binaire RZWboom waarin geen duplicaatsleutels zijn toegestaan.

***************************************************************************/
enum RZWkleur { rood, zwart };

template <class Sleutel>
class RZWknoop;

template <class Sleutel>
class RZWboom : public unique_ptr<RZWknoop<Sleutel>> {
	//....
public:
	using unique_ptr<RZWknoop<Sleutel>>::unique_ptr;
	RZWboom(unique_ptr<RZWknoop<Sleutel>>&& a);
	RZWboom(const std::vector<Sleutel>& sleutels, const std::vector<Sleutel>& zwarteSleutels);

	void inorder(std::function<void(const RZWknoop<Sleutel>&)> bezoek) const;
	//schrijf als tekst
	void schrijf(ostream& os) const;
	//tekenfuncties
	void tekenAls234Boom(const char * bestandsnaam) const;
	void tekenAlsBinaireBoom(const char * bestandsnaam) const;


	bool repOKZoekboom() const;
	bool repOK() const;
	int geefDiepte() const;
	int geefZwarteDiepte() const;

	//noot: volgende functie mag alleen opgeroepen worden bij hoofdboom, niet bij deelboom!
	void voegtoe(const Sleutel& sleutel);
protected:
	//zoekfunctie zoekt sleutel en geeft de boom in waaronder de sleutel zit (eventueel een lege boom als de sleutel
	//ontbreekt) en de pointer naar de ouder (als die bestaat, anders nulpointer).
	//noot: alhoewel de functie niets verandert aan de boom is ze geen const functie,
	//      omdat ze een niet-const pointer naar het inwendige van de boom teruggeeft.
	void zoek(const Sleutel& sleutel, RZWknoop<Sleutel>*& ouder, RZWboom<Sleutel>*& plaats);
	
// private...
	string tekenrecBinair(ostream& uit, int&nullteller) const;
	string tekenrec234(ostream& uit, int&nullteller, int&knoop34teller) const;
	void herstelboom();
	void roteer(bool naarlinks);

	RZWkleur geefKleur() const;
	void zetKleur(RZWkleur kl);
};

template <class Sleutel>
class RZWknoop {
	friend class RZWboom<Sleutel>;
public:
	RZWknoop() :ouder(0) {}
	RZWknoop(const Sleutel& sl) :sleutel{ sl }, ouder(0), kleur(rood){};
	RZWknoop(Sleutel&& sl) :sleutel{ move(sl) }, ouder(0), kleur(rood){};
	RZWboom<Sleutel>& geefKind(bool links);
	Sleutel sleutel;
	RZWknoop<Sleutel>* ouder;
	RZWboom<Sleutel> links, rechts;
	RZWkleur kleur;

	RZWboom<Sleutel>* geefBoomVanKnoop();
};
#endif
