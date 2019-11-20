#pragma once
#include "ZoekAlgoritme.h"
#include <iostream>

class BruteForce : public ZoekAlgoritme {
public:
    using ZoekAlgoritme::ZoekAlgoritme;
    std::queue<int> zoek(const std::string& tekst, ZoekInformatie& zoekInformatie) const;
};

std::queue<int> BruteForce::zoek(const std::string& tekst, ZoekInformatie& zoekInformatie) const {
    std::queue<int> posities;
    for(int i = 0; i <= tekst.size() - patroon.size(); i++) {
        
        zoekInformatie.tekstVergelijkingen++; // eerste karakter van patroon wordt zeker vergeleken, maar kan zijn dat we niet meer in while lus terechtkomen
        
        int j = 0;
        while(j < patroon.size() && patroon[j] == tekst[i + j]){
            zoekInformatie.tekstVergelijkingen++;
            j++;
        }

        if(j >= patroon.size()) {
            posities.push(i);
        }
        
    }
    return posities;
};