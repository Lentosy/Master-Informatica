#include "BoyerMoore.h"


class BoyerMooreHorspool : public BoyerMoore {
public:
    using BoyerMoore::BoyerMoore;
    std::queue<int> zoek(const std::string& tekst, ZoekInformatie& zoekInformatie) const;
};


std::queue<int> BoyerMooreHorspool::zoek(const std::string& tekst, ZoekInformatie& zoekInformatie) const {
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
            i += patroon.size();
        } else {
            int sprong = patroon.size() - 1 - MRPtabel[tekst[i + patroon.size() - 1]];
            i += sprong;
        }
    }
    return posities;
}