#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cassert>

class GaleShapley {
public:
    GaleShapley(std::vector<std::vector<int>> m, std::vector<std::vector<int>> v) : manVoorkeurslijst{m}, vrouwVoorkeurslijst{v} {
        assert(manVoorkeurslijst.size() == vrouwVoorkeurslijst.size());
    };
    std::vector<int> koppel() const;
    
private:
    std::vector<std::vector<int>> manVoorkeurslijst;
    std::vector<std::vector<int>> vrouwVoorkeurslijst;

    int GaleShapley::voorkeurVrouw(int vrouw, int man1, int man2) const;
};


int GaleShapley::voorkeurVrouw(int vrouw, int man1, int man2) const {
    int voorkeur = -1;

    std::vector<int>::const_iterator lijstIterator = vrouwVoorkeurslijst[vrouw].begin();
    while(lijstIterator != vrouwVoorkeurslijst[vrouw].end()) {

        // nagaan of huidige waarde één van de twee mannen is
        if(*lijstIterator == man1){
            voorkeur = man1;
        } else if(*lijstIterator == man2){
            voorkeur = man2;
        }

        if(voorkeur != -1){ // als de man gevonden werd
            lijstIterator = vrouwVoorkeurslijst[vrouw].end() - 1; // iterator op einde zetten zodat while lus stopt, moet wel -1 want we doen op het einde nog eens iterator++
        }
        lijstIterator++;
    } 

    return voorkeur;
}


/*
algorithm stable_matching is
    Initialize all m ∈ M and w ∈ W to free
    while ∃ free man m who still has a woman w to propose to do
        w = first woman on m's list to whom m has not yet proposed
        if w is free then
            (m, w) become engaged
        else some pair (m', w) already exists
            if w prefers m to m' then
                m' becomes free
                (m, w) become engaged 
            else
                (m', w) remain engaged
            end if
        end if
    repeat
*/
std::vector<int> GaleShapley::koppel() const {
    std::vector<int> koppeling(manVoorkeurslijst.size(), -1); // koppeling[i] geeft voor man i de vrouw die aan i gekoppeld werd

    std::vector<bool> vrouwVrij(vrouwVoorkeurslijst.size(), true); // houdt bij welke vrouwen er nog vrij zijn

    std::vector<int> volgendeAanzoek(manVoorkeurslijst.size()); // volgendeAanzoek[i] geeft voor man i de vrouw terug aan wie hij een aanzoek moet doen
    
    std::queue<int> mannenZonderPartner;
    for(int i = 0; i < manVoorkeurslijst.size(); i++){
        mannenZonderPartner.emplace(i);
    }
    
    while(!mannenZonderPartner.empty()){
        int manIndex = mannenZonderPartner.front();
        mannenZonderPartner.pop();

        int vrouwIndex = manVoorkeurslijst[manIndex][volgendeAanzoek[manIndex]];
        volgendeAanzoek[manIndex]++; // de man moet zijn volgende aanzoek doen aan de vrouw op de volgende positie in zijn lijst

        if(vrouwVrij[vrouwIndex]) {
            // (man, vrouw) worden verloofd
            koppeling[manIndex] = vrouwIndex;
            vrouwVrij[vrouwIndex] = false;
        } else { // (man', vrouw) bestaat
            int andereManIndex = 0;
            while(koppeling[andereManIndex] != vrouwIndex){
                andereManIndex++;
            }
            // als vrouw liever man heeft ipv man'
            if(voorkeurVrouw(vrouwIndex, manIndex, andereManIndex) == manIndex) {
                koppeling[andereManIndex] = -1;
                mannenZonderPartner.emplace(andereManIndex);
                koppeling[manIndex] = vrouwIndex;
                
            } else {
                mannenZonderPartner.emplace(manIndex);
            }
        }
    }
    return koppeling;
}