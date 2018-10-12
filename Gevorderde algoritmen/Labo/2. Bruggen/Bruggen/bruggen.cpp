#include "bruggen.h"
#include <stack>
#include <iostream>
#include <fstream>
#include <sstream>

// uitprinten van 1 verbinding.
std::ostream& operator<<(std::ostream& out, const Verbinding& v) {
	out << v.arenaIndex << " - > "
		<< v.winkelIndex << " (opbrengst: "
		<< v.opbrengst << ")\n";
	return out;
}

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
	zoekOptimaleVerbindingen();
}


void Bruggen::printStructuur(std::ostream& out) const {
	std::vector<Verbinding>::const_iterator it = verbindingen.begin();
	while (it != verbindingen.end()) {
		out << *it++;
	}
}

void Bruggen::printOplossing(std::ostream& out) const {
	int totaleWinst = 0;
	out << "De bruggen die gelegd moeten worden voor een optimale winst zijn: \n";
	for (size_t i = 0; i < aangeslotenVerbindingen.size(); i++) {
		totaleWinst += aangeslotenVerbindingen[i].opbrengst;
		out << aangeslotenVerbindingen[i];
	}
	out << "De totale opbrengst is : " << totaleWinst << " euro\n";
}

void Bruggen::zoekOptimaleVerbindingen() {
	if (!verbindingen.empty()) {
		std::vector<int> vorige(verbindingen.size(), -1);
		std::vector<int> huidigeBesteBedragen(verbindingen.size(), 0);
		int hoogsteBedrag = 0;
		int hoogsteBedragIndex = 0;

		for (size_t i = 0; i < verbindingen.size(); i++) {
			int huidigeHoogsteBedrag = verbindingen[i].opbrengst;

			for (size_t j = 0; j < i; j++) {
				if (verbindingen[j].winkelIndex < verbindingen[i].winkelIndex &&
					verbindingen[i].opbrengst + huidigeBesteBedragen[j] >= huidigeHoogsteBedrag) {

					huidigeHoogsteBedrag = verbindingen[i].opbrengst + huidigeBesteBedragen[j];
					vorige[i] = j;
				}
			}

			huidigeBesteBedragen[i] = huidigeHoogsteBedrag;

			if (huidigeHoogsteBedrag >= hoogsteBedrag) {
				hoogsteBedrag = huidigeHoogsteBedrag;
				hoogsteBedragIndex = i;
			}
		}

		while (hoogsteBedragIndex >= 0) {
			aangeslotenVerbindingen.push_back(verbindingen[hoogsteBedragIndex]);
			hoogsteBedragIndex = vorige[hoogsteBedragIndex];
		}

	}

}
