#pragma once
#include "ZoekAlgoritme.h"
#include "PrefixFunctie.h"


/**********************************************************************

   Class: KnuthMorrisPratt

   beschrijving: Het Knuth-Morris-Prattalgoritme maakt gebruikt van de algemene prefixfunctie.
                 Het algoritme verschuift het patroon met een sprong s = i - q(i) stappen als er een fout is tussen P[i] en T[j].
                 Deze sprong is echter enkel zinvol als het prefix van P met lengte q(i) een prefix is van P en P[q(i)] != P[i]
                 Er wordt een andere functie berekent, q', zodanig i - q'(i) de kleinste s-waarde geeft. 

***************************************************************************/

class KnuthMorrisPratt : public ZoekAlgoritme {
public:
    KnuthMorrisPratt(const std::string& patroon);
    std::queue<int> zoek(const std::string& tekst, ZoekInformatie& zoekInformatie) const;
private:
    std::vector<int> kmptabel;
};



KnuthMorrisPratt::KnuthMorrisPratt(const std::string& patroon) : ZoekAlgoritme(patroon) {
    std::vector<int> prefixtabel = PrefixFunctie::geefPrefixTabel(patroon);
    kmptabel = prefixtabel;
    for(int i = 2; i < prefixtabel.size(); i++) {
        if(kmptabel[i] > 0 && kmptabel[i + 1] == kmptabel[i] + 1) {
            kmptabel[i] = kmptabel[kmptabel[i]];
        }
    }
}
std::queue<int> KnuthMorrisPratt::zoek(const std::string& tekst, ZoekInformatie& zoekInformatie) const {
    std::queue<int> posities;
    int prefixLengte = 0;
    for(int i = 0; i <= tekst.size() - patroon.size(); i++) {
        if(prefixLengte > 0){
            zoekInformatie.tekstVergelijkingen++;
        }
        while((prefixLengte > 0) && (tekst[i - 1] != patroon[prefixLengte])) {
            zoekInformatie.tekstVergelijkingen++;
            prefixLengte = kmptabel[prefixLengte];
        }
        prefixLengte++;
        if(prefixLengte == patroon.size()){
            posities.push(i - patroon.size());
        }
    }
    return posities;
}