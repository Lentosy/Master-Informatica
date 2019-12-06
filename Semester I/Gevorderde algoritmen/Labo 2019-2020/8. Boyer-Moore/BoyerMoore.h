#pragma once
#include "ZoekAlgoritme.h"
#include "PrefixFunctie.h"
#include <iostream>

/**********************************************************************

   Class: BoyerMoore

   beschrijving: 

***************************************************************************/

class BoyerMoore : public ZoekAlgoritme {
public:
    BoyerMoore(const std::string& patroon);
    std::queue<int> zoek(const std::string& tekst, ZoekInformatie& zoekInformatie) const;
protected:
    std::vector<int> MRPtabel;
};



BoyerMoore::BoyerMoore(const std::string& patroon) : ZoekAlgoritme(patroon), MRPtabel(256, -1) {
    for(int i = 0; i < patroon.size() - 1; i++){
        MRPtabel[(unsigned char) patroon[i]] = i;
    }
}


std::queue<int> BoyerMoore::zoek(const std::string& tekst, ZoekInformatie& zoekInformatie) const {
    std::queue<int> posities;

    int i = 0;
    while(i < tekst.size() - patroon.size()) {
        int j = patroon.size() - 1;
        zoekInformatie.tekstVergelijkingen++;
        while(j > 0 && patroon[j] == tekst[i + j]){
            zoekInformatie.tekstVergelijkingen++;
            j--;
        }
        if(j == 0){
            posities.push(i);
            i++;
        } else {
            int sprong = j - MRPtabel[tekst[i + j]];
            sprong = sprong < 0 ? 1 : sprong;
            i += sprong;
        }
    }
    return posities;
}