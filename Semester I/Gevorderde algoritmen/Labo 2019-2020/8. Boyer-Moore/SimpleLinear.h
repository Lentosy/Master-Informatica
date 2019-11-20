#pragma once
#include "ZoekAlgoritme.h"
#include "ZoekInformatie.h"
#include "PrefixFunctie.h"
#include <iostream>

class SimpleLinear : public ZoekAlgoritme {
public:
    SimpleLinear(const std::string& patroon);
    std::queue<int> zoek(const std::string& tekst, ZoekInformatie& zoekInformatie) const;
private:
    std::vector<int> prefixtabel;
};


SimpleLinear::SimpleLinear(const std::string& patroon) : ZoekAlgoritme(patroon) {
    prefixtabel = PrefixFunctie::geefPrefixTabel(patroon);
}

std::queue<int> SimpleLinear::zoek(const std::string& tekst, ZoekInformatie& zoekInformatie) const {
    
    std::queue<int> posities;
    int lengteVorigePrefix = 0;
    // komt eigenlijk overeen met het berekenen van de prefixfunctie, maar het patroon wordt vergeleken met de tekst ipv het patroon zelf
    for (int i = 1; i <= tekst.size() - patroon.size(); i++) {
        if(lengteVorigePrefix > 0) { // eerste karakter wordt zeker nog eens vergeleken als prefixlengte > 0, maar kan zijn dat we niet meer in while lus terechtkomen
            zoekInformatie.tekstVergelijkingen++;
        }
        
        while (lengteVorigePrefix > 0 && patroon[lengteVorigePrefix] != tekst[i - 1]) {
            zoekInformatie.tekstVergelijkingen++;
            lengteVorigePrefix = prefixtabel[lengteVorigePrefix];
        }
            
        lengteVorigePrefix++;
        if (lengteVorigePrefix == patroon.size()) {
            posities.push(i - patroon.size());	
        }        
    }
    return posities;
}