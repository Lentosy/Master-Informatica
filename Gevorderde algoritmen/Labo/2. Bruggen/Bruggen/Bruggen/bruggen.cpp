#include "bruggen.h"

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

Bruggen::Bruggen(const char * bestandsnaam) {
	std::ifstream bestand("simpelbrug.dat");
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
	while (!aangeslotenVerbindingen.empty()) {
		Verbinding v = aangeslotenVerbindingen.front();
		out << v;
		totaleWinst += v.opbrengst;
		aangeslotenVerbindingen.pop();
	}
	out << "De totale opbrengst is : " << totaleWinst << " euro\n";
}

void Bruggen::zoekVerbindingen() {

}