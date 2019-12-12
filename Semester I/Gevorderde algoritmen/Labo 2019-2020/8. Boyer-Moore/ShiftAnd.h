#pragma once
#include "ZoekAlgoritme.h"
#include "ZoekInformatie.h"
#include "Bitpatroon.h"
#include <iostream>


const int SHIFTAND_VERWIJDERING = 1;
const int SHIFTAND_INLASSING = 2;
const int SHIFTAND_VERVANGING = 4;

void printsubstring(const std::string& tekst, int van, int tot) {
    for(int i = van; i <= tot; i++){
        std::cout << tekst[i];
    }
}


class ShiftAnd : public ZoekAlgoritme {
public:
    ShiftAnd(const std::string& patroon);

    std::queue<int> zoek(const std::string& tekst, ZoekInformatie& zoekInformatie) const;
    std::queue<int> zoek(const std::string& tekst, ZoekInformatie& ZoekInformatie, int flags) const;
    
private:
    Bitpatroon S[256]; // d = 256 (ascii waarden)
};

ShiftAnd::ShiftAnd(const std::string& patroon) : ZoekAlgoritme(patroon) { 
    for(int i = 0; i < patroon.size(); i++){
        Bitpatroon& bitpatroon = S[patroon[i]];
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
        if(R.en(matchPatroon))
            posities.push(i - patroon.size() + 1);
        
    }
    return posities;
};

std::queue<int> ShiftAnd::zoek(const std::string& tekst, ZoekInformatie& ZoekInformatie, int flags) const {
    std::queue<int> posities;
    
    bool verwijdering = flags & SHIFTAND_VERWIJDERING;
    bool inlassing = flags & SHIFTAND_INLASSING;
    bool vervanging = flags & SHIFTAND_VERVANGING;

    Bitpatroon R;
    Bitpatroon Rverwijdering;
    Bitpatroon Rinlassing;
    Bitpatroon Rvervanging;
    Bitpatroon matchPatroon = Bitpatroon::eenbit(this->patroon.size() - 1);
    for(int i = 0; i < tekst.size(); i++){

        // Vervanging en inlassing maken gebruik van vorige R tabel
        if(inlassing) {
            Rinlassing = (Rinlassing.shiftrechts(1) | Bitpatroon::eenbit(0)) & S[tekst[i]];
            Rinlassing |= R; 
        }

        if(vervanging) {
            Rvervanging = (Rvervanging.shiftrechts(1) | Bitpatroon::eenbit(0)) & S[tekst[i]];
            Rvervanging |= (R.shiftrechts(1) | Bitpatroon::eenbit(0));
        }

        R = (R.shiftrechts(1) | Bitpatroon::eenbit(0)) & S[tekst[i]];

        // Weglating gebruikt volgende R tabel
        if(verwijdering) {
            Rverwijdering = (Rverwijdering.shiftrechts(1) | Bitpatroon::eenbit(0)) & S[tekst[i]];
            Rverwijdering |= (R.shiftrechts(1) | Bitpatroon::eenbit(0));
        }


        if(R.en(matchPatroon)) {
            std::cout << "ShiftAnd: patroon gevonden op positie " << i - patroon.size() + 1 << " -> " << i << " ";
            printsubstring(tekst, i - patroon.size() + 1, i); 
            std::cout << "\n";     
        }

        if(Rinlassing.en(matchPatroon)) {
            std::cout << "ShiftAnd [inlassing]: patroon gevonden op positie " << i - patroon.size() << " -> " << i << " ";
            printsubstring(tekst, i - patroon.size(), i); 
            std::cout << "\n";             
        }

        if(Rvervanging.en(matchPatroon)) {
            std::cout << "ShiftAnd [vervanging]: patroon gevonden op positie " << i - patroon.size() + 1 << " -> " << i << " ";
            printsubstring(tekst, i - patroon.size() + 1, i); 
            std::cout << "\n";     
        }        

        if(Rverwijdering.en(matchPatroon)) {
            std::cout << "ShiftAnd [verwijdering]: patroon gevonden op positie " << i - patroon.size() + 2 << " -> " << i << " ";
            printsubstring(tekst, i - patroon.size() + 2, i); 
            std::cout << "\n";     
        }   
    }

    return posities;
}
