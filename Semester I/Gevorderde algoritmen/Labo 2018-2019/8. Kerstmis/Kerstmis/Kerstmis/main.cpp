
#include "suffixboom.h"
#include <fstream>
#include <string>
#include <streambuf>

void leesBestanden(Sboom& boom, std::vector<char>& sluitingstekens) {
	
	std::vector<std::string> bestanden = {
		"1","2","3","4","5","6","7","8","9"
	};


	int afsluitkarakter = 200; //range -1 -- -60
	for (int i = 0; i < bestanden.size(); i++) {
		
		std::ifstream input(bestanden[i]);
		std::string tekst((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
		boom.voegtoe(tekst, afsluitkarakter);
		sluitingstekens.push_back(afsluitkarakter);
		
		afsluitkarakter++;
	}

}

void LGD() {
	Sboom boom;
	std::vector<char> sluittekens;
	leesBestanden(boom, sluittekens);
	//boom is hier opgevuld
	

	std::string lgd = boom.geefLGD(sluittekens);
	std::cout << "langste gemeenschappelijke deelstring: " << lgd.size() << "\n";
	std::cout << lgd ;
}

int main(void) {
	LGD();
	/*
	Sboom boom;
	boom.voegtoe("AmijnBPLPMLJHFDmijnDA", 195);
	boom.voegtoe("CmijnD", 196);
	boom.voegtoe("EmijnHFOEHFOEFHEOIHmijFjhzoeuhozuemijnD", 197);
	std::vector<char> sluittekens;
	sluittekens.push_back(195); // todo, dynamisch
	sluittekens.push_back(196);
	sluittekens.push_back(197);
	std::string uit = boom.geefLGD(sluittekens);
	std::cout << uit;*/
	return 0;
}