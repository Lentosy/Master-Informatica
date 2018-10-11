

#pragma once
#include <vector>

class Verbinding;

class Probleem {
public:
	int huidigeWinst;
	// de index stelt de arena voor
	std::vector<Verbinding> verbindingen;
	std::vector<int> verbonden_arenas;
};


class Verbinding {
public:
	int winkelnr;
	int bedrag;

};