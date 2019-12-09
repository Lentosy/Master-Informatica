#pragma once
#include "ZoekAlgoritme.h"
#include "PrefixFunctie.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

/**********************************************************************

   Class: BoyerMoore

   beschrijving: 

***************************************************************************/

class BoyerMoore : public ZoekAlgoritme {
public:
    BoyerMoore(const std::string& patroon); // Enigste constructor dat patroon verwacht. Zal de MRPtabel en de juisteSuffixTabel opstellen.
    std::queue<int> zoek(const std::string& tekst, ZoekInformatie& zoekInformatie) const; // Zoek het patroon in de tekst. 

    void printTabellen(std::ostream& os) const; // Print de MRPTabel en de juisteSuffixTabel uit
protected:
    std::vector<int> MRPtabel;          // tabel die de meeste rechtste positie van elk karakter in P bijhoudt. Wordt gebruikt bij de heuristiek van het verkeerde karakter
    std::vector<int> juisteSuffixTabel; // de verschuivingtabel gebruikt bij de heuristiek van het juiste suffix
};


void BoyerMoore::printTabellen(std::ostream& os) const {

    const int cellwidth = 3;
    const int rowHeaderWidth = 5;
    
    
    os << "Juiste Suffix Tabel (v[i])\n";
    os << std::setw(rowHeaderWidth) << "i";
    for(int i = 0; i < patroon.size(); i++){
        os << std::setw(cellwidth) << i;
    }
    os << "\n";
    os << std::setw(rowHeaderWidth) << "P[i]";
    for(int i = 0; i < patroon.size(); i++){
        os << std::setw(cellwidth) << patroon[i];
    }
    os << "\n";
    os << std::setw(rowHeaderWidth) << "v[i]";
    for(int i = 0; i < juisteSuffixTabel.size(); i++){
        os << std::setw(cellwidth) << juisteSuffixTabel[i];
    }

    os << "\n";
}



BoyerMoore::BoyerMoore(const std::string& patroon) : ZoekAlgoritme(patroon), MRPtabel(256, -1) {
    // Opstellen heuristiek van verkeerde karakter
    for(int i = 0; i < patroon.size() - 1; i++){
        MRPtabel[(unsigned char) patroon[i]] = i; 
    }

    // Opstellen heuristiek van juiste suffix

    // Eerst voorbereidend werk: suffixfunctie van het patroon bepalen
    // Is equivalent met de prefixfunctie bepalen van het omgekeerde (reverse) patroon, en de resulterende tabel dan terug om te draaien, zonder het 0-de element
    std::string reversePatroon = patroon;
    std::reverse(reversePatroon.begin(), reversePatroon.end());
    std::vector<int> suffixtabel = PrefixFunctie::geefPrefixTabel(reversePatroon);
    for(int i = 1; i < suffixtabel.size(); i++){
        suffixtabel[i - 1] = suffixtabel[i];
    }
    suffixtabel.resize(suffixtabel.size() - 1);
    std::reverse(suffixtabel.begin(), suffixtabel.end());

    // Elk element in de tabel op de grootste sprong zetten = p - s(0)
    int grootsteSprong = patroon.size() - suffixtabel[0];
    juisteSuffixTabel.resize(patroon.size(), grootsteSprong);
    
    // tabel opvullen: paragraaf in cursus dat begint met 'We kunnen echter ook de suffixtabel eenmaal overlopen' P 122
    for(int j = 0; j < patroon.size(); j++){
        int foutpositie = patroon.size() - suffixtabel[j] - 1;
        juisteSuffixTabel[foutpositie] = foutpositie + 1 - j;
    }
}


std::queue<int> BoyerMoore::zoek(const std::string& tekst, ZoekInformatie& zoekInformatie) const {
    std::queue<int> posities;

    int tekstIndex = 0;
    while(tekstIndex < tekst.size() - patroon.size()) {
        int patroonIndex = patroon.size() - 1;

        zoekInformatie.tekstVergelijkingen++;
        // patroon van achter naar voor overlopen
        while(patroonIndex > 0 && patroon[patroonIndex] == tekst[tekstIndex + patroonIndex]){
            zoekInformatie.tekstVergelijkingen++;
            patroonIndex--;
        }
        
        if(patroonIndex == 0){ // patroon gevonden
            posities.push(tekstIndex);
            tekstIndex++;
        } else { // ergens fout karakter tegengekomen in patroon
            // Bepaal de grootste sprong, gebruik makend van beide heuristieken.
            char fouteKarakter = tekst[tekstIndex + patroonIndex];
            int shiftFouteKarakter = patroonIndex - MRPtabel[fouteKarakter];
            int shiftJuisteSuffix = juisteSuffixTabel[patroonIndex];
            int shift = std::max(shiftFouteKarakter, shiftJuisteSuffix);
            tekstIndex += shift;
        }
    }
    return posities;
}