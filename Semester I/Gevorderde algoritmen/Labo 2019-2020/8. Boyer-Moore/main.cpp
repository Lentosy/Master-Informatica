
#include <iostream>
#include <fstream>
#include <cstdio>
#include <map>
#include "BoyerMoore.h"
#include "BoyerMooreHorspool.h"
#include "BoyerMooreSunday.h"
#include "woordstroom.h"

#include <iostream>
#include <fstream>
#include <cstdio>
#include <map>
#include "BoyerMoore.h"
#include "woordstroom.h"

int main(void){


    std::ifstream bijbelStream("Bijbel.txt");
    std::string bijbel; // bevat de tekst van de bijbel, ZONDER spaties -> epic space effiency
     
    while(!bijbelStream.fail()){
        std::string woord;
        bijbelStream >> woord;
        bijbel += woord; 
    }

    
    std::map<std::string, int> reedsGevondenWoorden;
    Woordstroom kapitaal("Kapitaal.txt");
    remove("KapitaalOutput.txt");
    std::ofstream kapitaalOutput("KapitaalOutput.txt");
    bool isWoord = false;
    ZoekInformatie boyerMooreInformatie;
    ZoekInformatie boyerMooreHInformatie;
    ZoekInformatie boyerMooreSInformatie;
    
    int i = 0;
    while(!kapitaal.fail() && i < 100){
        
        std::string woord;
        kapitaal >> woord;
        if(isWoord){
            int aantal;
            BoyerMoore boyerMoore(woord);
            BoyerMooreHorspool boyerMooreH(woord);
            BoyerMooreSunday boyerMooreS(woord);
            std::queue<int> posities = boyerMoore.zoek(bijbel, boyerMooreInformatie);
            std::queue<int> positiesH = boyerMooreH.zoek(bijbel, boyerMooreHInformatie);
            std::queue<int> positiesS = boyerMooreS.zoek(bijbel, boyerMooreSInformatie);
            
            aantal = posities.size();
                
            
            kapitaalOutput << woord << " (" << aantal << ")";         
            i++;
        } else {
            kapitaalOutput << woord;
        }
        isWoord = !isWoord; // klasse woordstroom wisselt af tussen woorden en leestekens

    }

    std::cout << "Aantal tekstvergelijkingen (Boyer-Moore): " << boyerMooreInformatie.tekstVergelijkingen << "\n";
    std::cout << "Aantal tekstvergelijkingen (Boyer-Moore Horspool): " << boyerMooreHInformatie.tekstVergelijkingen << "\n";
    std::cout << "Aantal tekstvergelijkingen (Boyer-Moore Sunday): " << boyerMooreSInformatie.tekstVergelijkingen << "\n";
}





/*
int main(void){


    std::ifstream bijbelStream("Bijbel.txt");
    std::string bijbel; // bevat de tekst van de bijbel, ZONDER spaties -> epic space effiency
     
    while(!bijbelStream.fail()){
        std::string woord;
        bijbelStream >> woord;
        bijbel += woord; 
    }

    
    std::map<std::string, int> reedsGevondenWoorden;
    Woordstroom kapitaal("Kapitaal.txt");
    remove("KapitaalOutput.txt");
    std::ofstream kapitaalOutput("KapitaalOutput.txt");
    bool isWoord = false;
    ZoekInformatie boyerMoreInformatie;
    //ZoekInformatie bruteForceInformatie;
    while(!kapitaal.fail()){
        
        std::string woord;
        kapitaal >> woord;
        if(isWoord){
            int aantal;
            if(reedsGevondenWoorden.find(woord) == reedsGevondenWoorden.end()){
                BoyerMoore boyerMoore(woord);
                std::queue<int> posities = boyerMoore.zoek(bijbel, boyerMoreInformatie);
                aantal = posities.size();
                reedsGevondenWoorden[woord] = aantal;
            } 
            aantal = reedsGevondenWoorden[woord];
            kapitaalOutput << woord << " (" << aantal << ")";         
        } else {
            kapitaalOutput << woord;
        }
        isWoord = !isWoord; // klasse woordstroom wisselt af tussen woorden en leestekens
    }

    std::cout << "Aantal tekstvergelijkingen (Boyer-Moore): " << boyerMoreInformatie.tekstVergelijkingen;

}
*/