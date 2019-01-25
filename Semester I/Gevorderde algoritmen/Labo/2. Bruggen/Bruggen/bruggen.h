#ifndef __BRUGGEN_H
#define __BRUGGEN_H

#include <vector>

// klasse dat één verbinding voorstelt
class Verbinding {
public:
	Verbinding() {};
	Verbinding(int a, int o, int w) :
		arenaIndex(a),
		opbrengst(o),
		winkelIndex(w) {
	}
	//uitschrijven van één enkele verbinding.
	friend std::ostream& operator<<(std::ostream& out, const Verbinding& v);
	int arenaIndex;
	int opbrengst;
	int winkelIndex;
};


// klasse dat het probleem voorstelt. 
class Bruggen {
public:
	Bruggen(const char * bestandsnaam);
	void printOplossing(std::ostream& out) const;
private:
	// De deelverzameling van bruggen die de beste oplossing zal bevatten
	std::vector<Verbinding> aangeslotenVerbindingen;

	//de bruggen in het geheugen
	std::vector<Verbinding> verbindingen;

	//hulpfunctie dat de datastructuur uitprint
	void printStructuur(std::ostream& out) const;

	//zoekt de optimale verbindingen
	void zoekOptimaleVerbindingen();
};

#endif
