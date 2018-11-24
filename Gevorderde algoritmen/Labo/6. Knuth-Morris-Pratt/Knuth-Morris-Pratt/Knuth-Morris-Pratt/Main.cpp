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

int main(void) {
	testsuite();

	/*
	const uchar naald[] = { 'a','n','a','x','a','n','a','x'};
	int naaldlengte = sizeof(naald) / sizeof(uchar);
	const uchar hooiberg[] = { 'a','n','a','x','a','n','a','n','a','x','a','n','a','x' };
	int hooiberglengte = sizeof(hooiberg) / sizeof(uchar);
		zoek(naald.c_str(), naaldlengte, hooiberg, hooiberglengte);
	*/

	/*
	std::string naald("dolor");

	std::string hooiberg("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");

	zoek((uchar * )naald.c_str(), naald.size(), (uchar *)hooiberg.c_str(), hooiberg.size());
	*/
}