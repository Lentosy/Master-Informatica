#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <cassert>
#include "shiftand.h"

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
	int aantal_gevonden;


	// P = Patroon (naald)
	// p = Lengte van P
	// T = Tekst (hooiberg)
	// t = lengte van T
	while (testset >> naald >> hooiberg >> aantal_gevonden) {
		const uchar * P = (uchar *)naald.c_str();
		uint p = naald.size();
		const uchar * T = (uchar *)hooiberg.c_str();
		uint t = hooiberg.size();
		Shiftand sa(P, p);
		std::queue<const uchar*> plaatsen;
		sa.zoek(plaatsen, T, t);
		print(plaatsen, P, p, T, t);
	}

}

void hetKapitaal(){
	std::ifstream file("capital.txt");	
}

int main(void){
	hetKapitaal();
}
