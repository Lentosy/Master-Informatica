#include "BoyerMoore.h"


class BoyerMooreSunday : public BoyerMoore {
public:
    BoyerMooreSunday(const std::string& patroon);
    std::queue<int> zoek(const std::string& tekst, ZoekInformatie& zoekInformatie) const;
};


BoyerMooreSunday::BoyerMooreSunday(const std::string& patroon) : BoyerMoore(patroon){
    for(int i = 0; i < patroon.size(); i++){
        MRPtabel[(unsigned char) patroon[i]] = i;
    }
}

std::queue<int> BoyerMooreSunday::zoek(const std::string& tekst, ZoekInformatie& zoekInformatie) const {
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
            int sprong = patroon.size()  - MRPtabel[tekst[i + patroon.size()]];
            i += sprong;
        }
    }
    return posities;
}