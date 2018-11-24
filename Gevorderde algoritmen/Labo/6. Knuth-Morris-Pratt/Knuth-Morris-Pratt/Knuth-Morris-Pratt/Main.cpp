#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "knuthmorrispratt.h"

void testSuite() {
	std::ifstream input("testset.csv");
	//mijnnaald mijnhooiberg 0 5 5
	std::string naald, hooiberg;
	int aantal, kmp_vergelijkingen, prefix_vergelijkingen;
	while (input >> naald, hooiberg, aantal, kmp_vergelijkingen, prefix_vergelijkingen) {
		std::cout << naald;
	}

	KnuthMorrisPratt kmp((uchar *)naald.c_str(), naald.size());
	std::queue<const uchar*> plaatsen;
	kmp.zoek(plaatsen, (uchar *)hooiberg.c_str(), hooiberg.size());
}


int main(void) {

	testSuite();
	/*
	std::string naald("anaxanax");
	KnuthMorrisPratt kmp((uchar *)naald.c_str(), naald.size());

	std::queue<const uchar*> q;
	std::string hooiberg("anaxananaxanax");
	kmp.zoek(q, (uchar *)hooiberg.c_str(), hooiberg.size());*/
}