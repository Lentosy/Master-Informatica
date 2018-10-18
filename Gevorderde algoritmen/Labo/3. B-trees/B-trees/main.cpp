#include "schijf.h"
#include "btree.cpp"
#include "bknoop.cpp"
#include <string>
#include <fstream>
#include <regex>
#include <algorithm>

const int GROOTTE = 8;

int main(void) {
	// knoop heeft string als sleutel ( de woorden )
	//		, int als data ( de frequentie )
	//      , maximum GROOTTE aantal sleutels

	Schijf<Bknoop<std::string, int, GROOTTE>> schijf;
	Btree<std::string, int, GROOTTE> boom(schijf);
	std::ifstream input("bestand.txt");
	int aantalwoorden = 7; // hoeveel woorden van het bestand dat we willen inlezen, voor te testen
	int woordcount = 0;

	std::string woord;
	while (!input.eof() && woordcount < aantalwoorden) {
		input >> woord;

		if (std::regex_match(woord, std::regex("(.*)[,.?!]"))) { // weghalen leestekes
			woord = woord.substr(0, woord.size() - 1);
			std::transform(woord.begin(), woord.end(), woord.begin(), ::tolower);
		}

		int freq = boom.zoek(woord);
		if (freq) { // sleutel bestaat al
			boom.voegToe(woord, freq++);
		} else {
			boom.voegToe(woord, 1);
		}
		woordcount++;
	}
	input.close();
}