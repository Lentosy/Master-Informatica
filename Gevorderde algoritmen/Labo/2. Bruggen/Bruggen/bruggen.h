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
	std::vector<Verbinding> aangeslotenVerbindingen;
	std::vector<Verbinding> verbindingen;

	void printStructuur(std::ostream& out) const; // functie voor controle
	void zoekVerbindingen();
};

#endif
