#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "knuthmorrispratt.h"

void print(std::queue<const uchar*>& plaatsen, const uchar* naald, uint naaldlengte, const uchar* hooiberg, uint hooiberglengte) {

	std::cout << "De zoekstring '" << naald << "' werd " << plaatsen.size() << " keer gevonden in " << hooiberg << "\n";

	while (!plaatsen.empty()) {
		const uchar* resultaat = plaatsen.front();
		plaatsen.pop();

		int i = (resultaat - hooiberg);
		std::cout << "[" << i << " -> " << i + naaldlengte << "]\n";
	}
}

void testsuite() {
	std::ifstream testset("testset.dat");

	std::string naald, hooiberg;
	int aantal_gevonden, kmp_vergelijkingen, prefix_vergelijkingen;
	while (testset >> naald >> hooiberg >> aantal_gevonden >> kmp_vergelijkingen >> prefix_vergelijkingen ) {
		const uchar * P = (uchar *)naald.c_str();
		uint p = naald.size();
		const uchar * T = (uchar *)hooiberg.c_str();
		uint t = hooiberg.size();


		KnuthMorrisPratt kmp(P, p);
		std::queue<const uchar*> plaatsen;
		kmp.zoek(plaatsen, T, t);
		
		assert(plaatsen.size() == aantal_gevonden);
		print(plaatsen, P, p, T, t);

	}
}


void testShakeSpeare() {
	std::cout << "Geef een zoekstring op: ";
	std::string naald;
	std::cin >> naald;
	std::cout << "Zoekstring wordt gezocht in het volledige werk van Shakespeare.\n";
	KnuthMorrisPratt kmp((uchar *)naald.c_str(), naald.size());
	std::ifstream file("Shakespeare.txt");
	std::string shakespeare(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	file.close();
	std::cout << shakespeare;

}

int main(void) {
	//testsuite();
	testShakeSpeare();
	/*
	std::string naald("ABACABAC");
	std::string hooiberg("ABACABAC");
	KnuthMorrisPratt kmp((uchar *)naald.c_str(), naald.size());
	std::queue<const uchar*> plaatsen;
	kmp.zoek(plaatsen, (uchar *)hooiberg.c_str(), hooiberg.size());
	*/
}