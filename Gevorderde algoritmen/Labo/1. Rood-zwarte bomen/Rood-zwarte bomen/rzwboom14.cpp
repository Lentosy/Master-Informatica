#include "rzwboom14.h"

template <class Sleutel>
RZWboom<Sleutel>::RZWboom(unique_ptr<RZWknoop<Sleutel>>&& a)
	: unique_ptr<RZWknoop<Sleutel>>(move(a)) {}

template <class Sleutel>
RZWboom<Sleutel>::RZWboom(const std::vector<Sleutel>& sleutels,
	const std::vector<Sleutel>& zwarteSleutels) {
	RZWboom<Sleutel>* plaats;
	RZWknoop<Sleutel>* ouder;
	// toevoegen van de sleutels, ongeacht hun kleur
	for (size_t i = 0; i < sleutels.size(); i++) {
		zoek(sleutels[i], ouder, plaats);
		if (*plaats == nullptr) {  // enkel toevoegen indien nog niet bestaat
			*plaats = std::make_unique<RZWknoop<Sleutel>>(sleutels[i]);
			plaats->get()->ouder = ouder;
		}
	}

	// de sleutels zoeken die zwart moeten worden en effectief zwart maken.
	for (size_t i = 0; i < zwarteSleutels.size(); i++) {
		zoek(zwarteSleutels[i], ouder, plaats);
		if (*plaats != nullptr) {
			plaats->get()->kleur = RZWkleur::zwart;
		}
	}
}

template <class Sleutel>
void RZWboom<Sleutel>::voegtoe_bottomup(const Sleutel& sleutel) {
	RZWboom<Sleutel>* plaats;
	RZWknoop<Sleutel>* ouder;
	zoek(sleutel, ouder, plaats);
	if (!*plaats) { // kijken of knoop al niet bestaat
		(*plaats) = std::make_unique<RZWknoop<Sleutel>>(sleutel);
		plaats->get()->ouder = ouder;
		plaats->herstelboom();
	}
}


/*
template <class Sleutel>
void RZWboom<Sleutel>::voegtoe_topdown(const Sleutel& sleutel) {
	RZWboom<Sleutel>* plaats = this;
	RZWknoop<Sleutel>* ouder = nullptr;

	bool is_toegevoegd = false;
	while (!is_toegevoegd) {
		RZWboom<Sleutel>* linkerkind = &((*plaats)->geefKind(true));
		RZWboom<Sleutel>* rechterkind = &((*plaats)->geefKind(false));

		if (!(*plaats)) {
			(*plaats) = std::make_unique<RZWknoop<Sleutel>>(sleutel);
			(*plaats)->ouder = ouder_knoop;
			is_toegevoegd = true;
		}
		else if ((*plaats)->geefKleur() == zwart && linkerkind->geefKleur() == rood && rechterkind->geefKleur() == rood) {
			(*plaats)->zetKleur(rood);
			(*linkerkind)->zetKleur(zwart);
			(*rechterkind)->zetKleur(zwart);
		}


		if ((*plaats)->ouder 
			&& (*plaats)->ouder->ouder 
			&& ((*plaats)->geefKleur == rood) 
			&& ((*plaats)->ouder->kleur == rood)) {


		}

	}
}*/

template <class Sleutel>
void RZWboom<Sleutel>::herstelboom() {
	// notatie vanuit de cursus:
	// g = grootouder
	// p = ouder
	// b = broer van p
	// c = kind van p


	RZWknoop<Sleutel>* p = this->get()->ouder;
	if (!p) { // de huidige knoop is de wortel, gewoon de kleur zwart maken
		this->zetKleur(RZWkleur::zwart);
		return;
	}
	RZWknoop<Sleutel>* g = p->ouder;

	if (!g) return; // de huidige knoop is een kind van de wortel, herkleuring is niet nodig.

	// instellen belangrijke switches
	bool p_is_zwart = p->kleur == RZWkleur::zwart;
	bool p_is_linkerkind_van_g = p->sleutel < g->sleutel;
	RZWknoop<Sleutel>* b = g->geefKind(!p_is_linkerkind_van_g).get();
	bool b_is_zwart = !b ? true
		: g->geefKind(!p_is_linkerkind_van_g)->kleur == RZWkleur::zwart;

	bool c_ligt_aan_binnenkant;

	c_ligt_aan_binnenkant = p_is_linkerkind_van_g ? this->get()->sleutel > p->sleutel
		: this->get()->sleutel < p->sleutel;

	if (!p_is_zwart) {  // indien p zwart is kunnen we zonder problem een rode
						// knoop toevoegen, is dit echter niet het geval moeten we
						// alle gevallen afgaan
		if (!b_is_zwart) {  // b is rood
			g->kleur = RZWkleur::rood;
			p->kleur = RZWkleur::zwart;
			b->kleur = RZWkleur::zwart;
			g->geefBoomVanKnoop()->herstelboom();
		}
		else {  // b is zwart

			// indien c aan de binnenkant ligt, moet geroteerd worden zodat deze aan de buitenkant ligt met als gevolg dat de 3 knopen g, p en c op een rij liggen
			if (c_ligt_aan_binnenkant) {
				p->geefBoomVanKnoop()->roteer(p_is_linkerkind_van_g);
				c_ligt_aan_binnenkant = false;
			}

			// de vorige stap moet altijd gevolgd worden door deze stap, maar deze stap kan ook onafhankelijk van de vorige stap voorkomen.
			if (!c_ligt_aan_binnenkant) { // de 3 knopen liggen nu op een rij
				g->geefBoomVanKnoop()->roteer(!p_is_linkerkind_van_g);
				g->kleur = RZWkleur::rood;
				p->kleur = RZWkleur::zwart;
			}
		}
	}
}


// zal falen indien 'this' de wortel is
template<class Sleutel>
RZWboom<Sleutel>* RZWknoop<Sleutel>::geefBoomVanKnoop() {
	if (this->ouder) {
		if (this == ouder->links.get()) {
			return &ouder->links;
		}
		else {
			return &ouder->rechts;
		}
	}
	else {
		return nullptr; // foutief
	}
}

#pragma region Onbelangrijke functies

template <class Sleutel>
int RZWboom<Sleutel>::geefZwarteDiepte() const {
	if (*this) {
		if ((*this)->links.geefZwarteDiepte() !=
			(*this)->rechts.geefZwarteDiepte()) {
			return -1;
		}
		else {
			if ((*this)->kleur == RZWkleur::rood)
				return std::max((*this)->links.geefZwarteDiepte(),
				(*this)->rechts.geefZwarteDiepte());
			else
				return 1 + std::max((*this)->links.geefZwarteDiepte(),
				(*this)->rechts.geefZwarteDiepte());
		}
	}
	else {
		return 0;
	}
}

template <class Sleutel>
bool RZWboom<Sleutel>::repOK() const {
	bool ok = repOKZoekboom();
	if (*this) {
		if (this->get()->kleur == RZWkleur::rood) {
			throw "De wortel is niet zwart\n";
		}

		inorder([](const RZWknoop<Sleutel>& knoop) {
			if (knoop.kleur == RZWkleur::rood) {
				if (knoop.links && knoop.links.get()->kleur == RZWkleur::rood) {
					throw "Het linkerkind van een rode knoop is ook rood.";
				}
				if (knoop.rechts && knoop.rechts.get()->kleur == RZWkleur::rood)
					throw "Het rechterkind van een rode knoop is ook rood.";
			}
		});
		if (geefZwarteDiepte() == -1) {
			throw "Zwarte diepte is niet correct\n";
		}
	}

	return ok;
}

#pragma endregion

#pragma region Gegeven Functies

template <class Sleutel>
RZWkleur RZWboom<Sleutel>::geefKleur() const {
	return this->get()->kleur;
}

template <class Sleutel>
void RZWboom<Sleutel>::zetKleur(RZWkleur kl) {
	this->get()->kleur = kl;
}

template <class Sleutel>
void RZWboom<Sleutel>::inorder(
	std::function<void(const RZWknoop<Sleutel>&)> bezoek) const {
	if (*this) {
		(*this)->links.inorder(bezoek);
		bezoek(**this);
		(*this)->rechts.inorder(bezoek);
	};
}

template <class Sleutel>
void RZWboom<Sleutel>::schrijf(ostream& os) const {
	inorder([&os](const RZWknoop<Sleutel>& knoop) {
		os << "(" << knoop.sleutel << ")";
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
template <class Sleutel>
void RZWboom<Sleutel>::tekenAls234Boom(const char* bestandsnaam) const {
	ofstream uit(bestandsnaam);
	assert(uit);
	int nullteller = 0;     // nullknopen moeten een eigen nummer krijgen.
	int knoop34teller = 0;  // 3-knopen en 4-knopen worden ook genummerd
	uit << "digraph {\n";
	uit << "node[shape=rectangle]\n";
	this->tekenrec234(uit, nullteller, knoop34teller);
	uit << "}";
}
template <class Sleutel>
string RZWboom<Sleutel>::tekenrec234(ostream& uit, int& nullteller,
	int& knoop34teller) const {
	ostringstream wortelstring;
	if (!*this) {
		wortelstring << "null" << ++nullteller;
		uit << wortelstring.str() << " [shape=point];\n";
	}
	else {
		wortelstring << '"' << (*this)->sleutel << '"';
		uit << wortelstring.str() << "[label=\"" << (*this)->sleutel << "\"][style=filled]";
		if (this->geefKleur() == rood) {
			uit << "[fillcolor=red][fontcolor=black]";
		}
		else {
			uit << "[fillcolor=black][fontcolor=white]";
		}

		uit << ";\n";
		string linkskind = (*this)->links.tekenrec234(uit, nullteller, knoop34teller);
		string rechtskind = (*this)->rechts.tekenrec234(uit, nullteller, knoop34teller);
		if (!(*this)->links && !(*this)->rechts) {
			uit << wortelstring.str() << " -> " << linkskind << "\n";
			uit << wortelstring.str() << " -> " << rechtskind << "\n";
		}
		else if (!(*this)->rechts) {
			uit << wortelstring.str() << " -> " << rechtskind << "\n";
		}
		else if (!(*this)->links) {
			uit << wortelstring.str() << " -> " << linkskind << "\n";
		}
		else {
			if ((*this)->links.geefKleur() == rood ||
				(*this)->rechts.geefKleur() == rood) {
				uit << "subgraph cluster_" << ++knoop34teller
					<< " {\n   { rank=\"same\"; ";
				if ((*this)->links.geefKleur() == rood) uit << linkskind << " , ";
				if ((*this)->rechts.geefKleur() == rood) uit << rechtskind << " , ";
				uit << wortelstring.str() << "}\n";
				if ((*this)->links.geefKleur() == rood) {
					uit << "   " << linkskind << " ->" << wortelstring.str() << "[dir=back];\n";
				}

				if ((*this)->rechts.geefKleur() == rood) {
					uit << "   " << wortelstring.str() << " -> " << rechtskind << ";\n";
				}

				uit << "color=white\n}\n";
			};

			if ((*this)->links.geefKleur() == zwart) {
				uit << wortelstring.str() << " -> " << linkskind << ";\n";
			}

			if ((*this)->rechts.geefKleur() == zwart) {
				uit << wortelstring.str() << " -> " << rechtskind << ";\n";
			}

		}
	};
	return wortelstring.str();
}
template <class Sleutel>
void RZWboom<Sleutel>::tekenAlsBinaireBoom(const char* bestandsnaam) const {
	ofstream uit(bestandsnaam);
	assert(uit);
	int nullteller = 0;  // nullknopen moeten een eigen nummer krijgen.
	uit << "digraph {\n";
	uit << "node[shape=circle]\n";
	this->tekenrecBinair(uit, nullteller);
	uit << "}";
}
template <class Sleutel>
string RZWboom<Sleutel>::tekenrecBinair(ostream& uit, int& nullteller) const {
	ostringstream wortelstring;
	if (!*this) {
		wortelstring << "null" << ++nullteller;
		uit << wortelstring.str() << " [shape=point];\n";
	}
	else {
		wortelstring << '"' << (*this)->sleutel << '"';
		uit << wortelstring.str() << "[label=\"" << (*this)->sleutel
			<< "\"][style=filled]";

		if (this->geefKleur() == rood) {
			uit << "[fillcolor=red][fontcolor=black]";
		}
		else {
			uit << "[fillcolor=black][fontcolor=white]";
		}

		uit << ";\n";
		string linkskind = (*this)->links.tekenrecBinair(uit, nullteller);
		string rechtskind = (*this)->rechts.tekenrecBinair(uit, nullteller);
		uit << wortelstring.str() << " -> " << linkskind << ";\n";
		uit << wortelstring.str() << " -> " << rechtskind << ";\n";
	};
	return wortelstring.str();
}





template <class Sleutel>
bool RZWboom<Sleutel>::repOKZoekboom() const {
	const Sleutel* vorige = 0;//houdt ref naar eerder gezien sleutel bij.
	bool oke = true;
	if (*this && (*this)->ouder != 0)
		throw "wortel heeft geen null-ouder\n";
	inorder([&vorige, &oke](const RZWknoop<Sleutel>& knoop) {
		//volgorde sleutels
		if (vorige && knoop.sleutel < *vorige) {
			throw "Verkeerde volgorde\n";
		};
		vorige = &knoop.sleutel;

		//ouderpointers
		for (const RZWknoop<Sleutel>* kind : { knoop.links.get(), knoop.rechts.get() })
			if (kind != 0 && kind->ouder != &knoop) {
				std::ostringstream fout;
				fout << "Ongeldige ouderpointer bij knoop " << kind->sleutel << "\n";
				fout << " wijst niet naar " << knoop.sleutel << "\n";
				throw fout.str();
				return;
			};
		//...nog tests?
		return;
	});
	return oke;
}



template <class Sleutel>
int RZWboom<Sleutel>::geefDiepte() const {
	if (*this)
		return 1 +
		std::max((*this)->links.geefDiepte(), (*this)->rechts.geefDiepte());
	else
		return 0;
}


template <class Sleutel>
void RZWboom<Sleutel>::zoek(const Sleutel& sleutel, RZWknoop<Sleutel>*& ouder,
	RZWboom<Sleutel>*& plaats) {
	plaats = this;
	ouder = 0;
	while (*plaats && (*plaats)->sleutel != sleutel) {
		ouder = plaats->get();
		plaats = &((*plaats)->geefKind(((*plaats)->sleutel > sleutel)));
	};
};

template <class Sleutel>
RZWboom<Sleutel>& RZWknoop<Sleutel>::geefKind(bool linkerkind) {
	if (linkerkind)
		return links;
	else
		return rechts;
}


// preconditie: wortel en nodige kind bestaan
template <class Sleutel>
void RZWboom<Sleutel>::roteer(bool naarLinks) {
	RZWboom<Sleutel> kind = move((*this)->geefKind(!naarLinks));
	// beta verhangen
	(*this)->geefKind(!naarLinks) = move(kind->geefKind(naarLinks));
	// wortel verhangen
	kind->geefKind(naarLinks) = move(*this);
	// kind verhangen
	*this = move(kind);
	// ouderpointers goed zetten
	(*this)->ouder = (*this)->geefKind(naarLinks)->ouder;
	(*this)->geefKind(naarLinks)->ouder = this->get();
	if ((*this)->geefKind(naarLinks)->geefKind(!naarLinks))  // alpha niet leeg
		(*this)->geefKind(naarLinks)->geefKind(!naarLinks)->ouder =
		(*this)->geefKind(naarLinks).get();
};
#pragma endregion