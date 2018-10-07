#ifndef __BRUGGEN_H
#define __BRUGGEN_H

#include <vector>
#include <stack>
#include <iostream>
#include <fstream>
#include <sstream>
// klasse dat één verbinding voorstelt
class Verbinding {
public:
	Verbinding() {};
	Verbinding(int a, int o, int w) : arenaIndex(a),
		opbrengst(o),
		winkelIndex(w) {
	}

	int arenaIndex;
	int opbrengst;
	int winkelIndex;
};


// klasse dat het probleem voorstelt. 
class Bruggen {
public:
	Bruggen(const char * bestandsnaam);
	void printStructuur(std::ostream& out); // functie voor controle
	void printOplossing(std::ostream& out);
private:
	std::vector<Verbinding> aangeslotenVerbindingen;
	std::vector<Verbinding> verbindingen;
	int aantalBruggen;
	void zoekVerbindingen();
};

#endif

// uitprinten van 1 verbinding.
std::ostream& operator<<(std::ostream& out, const Verbinding& v) {
	out << v.arenaIndex << " - > "
		<< v.winkelIndex << " ("
		<< v.opbrengst << ")\n";
	return out;
}

void Bruggen::printStructuur(std::ostream& out) {
	std::vector<Verbinding>::const_iterator it = verbindingen.begin();
	while (it != verbindingen.end()) {
		out << *it++;
	}
}
/*
std::ostringstream fout;
fout << "Ongeldige ouderpointer bij knoop " << kind->sleutel << "\n";
fout << " wijst niet naar " << knoop.sleutel << "\n";
throw fout.str();*/
Bruggen::Bruggen(const char * bestandsnaam) {
	std::ifstream bestand(bestandsnaam);
	if (!bestand.is_open()) {
		std::ostringstream fout;
		fout << bestandsnaam << " kan niet gevonden worden\n";
		throw std::string(fout.str());
	}

	int aantal;
	bestand >> aantal;
	int arenaIndex = 0, opbrengst, winkelIndex;
	while (arenaIndex < aantal) {
		bestand >> opbrengst >> winkelIndex;
		Verbinding v(arenaIndex, opbrengst, winkelIndex);
		verbindingen.push_back(v);
		arenaIndex++;
	}
	bestand.close();
}

void Bruggen::printOplossing(std::ostream& out) {
	zoekVerbindingen();
	int totaleWinst = 0;
	std::cout << "De bruggen die gelegd moeten worden voor een optimale winst zijn: \n";
	for (int i = 0; i < aangeslotenVerbindingen.size(); i++) {
		totaleWinst += aangeslotenVerbindingen[i].opbrengst;
		std::cout << aangeslotenVerbindingen[i];
	}
	out << "De totale opbrengst is : " << totaleWinst << " euro\n";
}


/*
Een verbinding (a_i, w_i) kruist een verbinding (a_j, w_j) indien:
	a_i < a_j EN w_i > w_j
	OF
	a_i > a_j EN w_i < w_j

Hieruit volgt dat voor een deelverzameling bruggen één van de
volgende twee eigenschappen moeten gelden tussen elk paar verbindingen:

	a_i <= a_j EN w_i <= w_j
	OF
	a_i >= a_j EN w_i >= w_j
*/

void Bruggen::zoekVerbindingen() {
	std::vector<int> P(verbindingen.size());
	std::vector<int> M(verbindingen.size() + 1);
	int langsteDeelSequentie = 0;
	for (size_t i = 0; i < verbindingen.size(); i++) {	
		int links = 1;
		int rechts = langsteDeelSequentie;
		while (links <= rechts) {
			int mid = std::ceil((links + rechts) / 2);
			if (verbindingen[M[mid]].winkelIndex < verbindingen[i].winkelIndex) {
				links = mid + 1;
			} else {
				rechts = mid - 1;
			}
		}
		int newL = links;
		P[i] = M[newL - 1];
		M[newL] = i;
		if (newL > langsteDeelSequentie) {
			langsteDeelSequentie = newL;
		}
	}

	// constructie langste deelsequentie
	int k = M[langsteDeelSequentie];
	for (int i = langsteDeelSequentie - 1; i >= 0; i--) {
		aangeslotenVerbindingen.push_back(verbindingen[k]);		
		k = P[k];
	}

}
