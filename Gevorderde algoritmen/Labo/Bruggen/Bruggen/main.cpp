
#include "probleem.cpp"
#include <iostream>
#include <fstream>
#include <string>

int main(void) {

	std::ifstream bestand("simpelbrug.dat", std::ifstream::in);
	if (!bestand.fail() || !bestand.is_open()) {
		std::cout << "fout bestand\n";
	}



	Probleem p;
	int bedrag;
	int winkelnr;

	int aantal;
	bestand >> aantal;
	std::cout << aantal << "\n";

	int i = 0;
	while (!bestand.eof()) {
		bestand >> bedrag >> winkelnr;
		Verbinding v;
		v.bedrag = bedrag;
		v.winkelnr = winkelnr;
		p.verbindingen.push_back(v);
		std::cout << i++ << " ->(" << bedrag << ") " << winkelnr << "\n";
	}
	std::cin >> aantal;
	return 0;
}