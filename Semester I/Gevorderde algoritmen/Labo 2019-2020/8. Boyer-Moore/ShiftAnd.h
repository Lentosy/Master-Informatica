#pragma once
#include "ZoekAlgoritme.h"
#include "ZoekInformatie.h"
#include "Bitpatroon.h"



class ShiftAnd : public ZoekAlgoritme {
public:
    ShiftAnd(const std::string& patroon);

    std::queue<int> zoek(const std::string& tekst, ZoekInformatie& zoekInformatie) const;
private:
    Bitpatroon S[256]; // d = 256 (ascii waarden)
};

ShiftAnd::ShiftAnd(const std::string& patroon) : ZoekAlgoritme(patroon) { 
    for(int i = 0; i < patroon.size(); i++){
        Bitpatroon& bitpatroon = S[i];
        bitpatroon |= Bitpatroon::eenbit(i);
    }
}

std::queue<int> ShiftAnd::zoek(const std::string& tekst, ZoekInformatie& zoekInformatie) const {
        std::queue<int> posities;
        Bitpatroon R;
        Bitpatroon matchPatroon = Bitpatroon::eenbit(this->patroon.size() - 1);
        for(int i = 0; i < tekst.size(); i++){
            R = (R.shiftrechts(1) | Bitpatroon::eenbit(0)) & S[tekst[i]];
            zoekInformatie.tekstVergelijkingen++;
            if(R.en(matchPatroon)) {
                posities.push(i);
            }
        }
        return posities;
    };