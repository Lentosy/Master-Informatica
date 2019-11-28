
#include <string>
#include <queue>
#include <iostream>
#include <vector>

#include "BruteForce.h"
#include "SimpleLinear.h"
#include "KnuthMorrisPratt.h"
#include "BoyerMoore.h"
#include "BoyerMooreHorspool.h"
#include "BoyerMooreSunday.h"
#include "KarpRabin.h"

void print(const ZoekAlgoritme * zoekAlgoritme, const ZoekInformatie& zoekInformatie, std::queue<int>& posities, const std::string& patroon, const std::string& tekst) {

    std::cout << "Zoekalgoritme: " << zoekAlgoritme->naam() << "\n";
	std::cout << "\tDe zoekstring " << patroon << " werd " << posities.size() << " keer gevonden in " << tekst << " op volgende posities:\n";
    
	while (!posities.empty()) {
		int positie = posities.front();
		posities.pop();

		std::cout << "\t\t[" << positie << " -> " << positie + patroon.size() - 1 << "]\n";
	}
    std::cout << "\tAantal tekstvergelijkingen: " << zoekInformatie.tekstVergelijkingen << "\n";
    //std::cout << "\tAantal opschuivingen: " << zoekInformatie.opschuivingen << "\n";
}


int main(void){
    std::string patroon("GCAGAGAG");
	std::string tekst("GCATCGCAGAGAGTATACAGGCAGAGAGTACG");

    std::vector<ZoekAlgoritme*> zoekMethoden;
    zoekMethoden.push_back(new BruteForce(patroon));
    zoekMethoden.push_back(new SimpleLinear(patroon));
    zoekMethoden.push_back(new KnuthMorrisPratt(patroon));
    zoekMethoden.push_back(new BoyerMoore(patroon));
    zoekMethoden.push_back(new BoyerMooreHorspool(patroon));
    zoekMethoden.push_back(new BoyerMooreSunday(patroon));
    zoekMethoden.push_back(new KarpRabin(patroon, 257, 4));
    for(const ZoekAlgoritme * zoekMethode : zoekMethoden) {
        ZoekInformatie zoekInformatie;
        std::queue<int> posities = zoekMethode->zoek(tekst, zoekInformatie);
        print(zoekMethode, zoekInformatie, posities, patroon, tekst);
    }
    return 0;
}