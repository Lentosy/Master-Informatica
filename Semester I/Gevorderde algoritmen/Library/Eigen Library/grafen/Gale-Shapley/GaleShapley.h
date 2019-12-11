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

    int geefEersteVrij(std::vector<bool>& lijst) const;
    int GaleShapley::voorkeurVrouw(int vrouw, int man1, int man2) const;
};

int GaleShapley::geefEersteVrij(std::vector<bool>& lijst) const {
    int i = 0;
    while(lijst[i] == false){
        i++;
    }
    
    return i;
}

int GaleShapley::voorkeurVrouw(int vrouw, int man1, int man2) const {
    int i = 0;
    while(vrouwVoorkeurslijst[vrouw][i] != man1 || vrouwVoorkeurslijst[vrouw][i] != man2){
        i++;
    }
    return i;
}

std::vector<int> GaleShapley::koppel() const {
    std::vector<int> koppeling(manVoorkeurslijst.size(), -1);

    std::vector<bool> manVrij(manVoorkeurslijst.size(), true);
    std::vector<bool> vrouwVrij(vrouwVoorkeurslijst.size(), true);
    std::vector<int> volgendeAanzoek(manVoorkeurslijst.size()); // deze vector bevat per man de index van de volgende vrouw in zijn voorkeurlijst die hij moet vragen
    
    int manIndex;
    while((manIndex = geefEersteVrij(manVrij)) != manVrij.size()) {
        int vrouwIndex = manVoorkeurslijst[manIndex][volgendeAanzoek[manIndex]];
        volgendeAanzoek[manIndex]++;
        if(vrouwVrij[vrouwIndex]) {
            // (man, vrouw) worden verloofd
            koppeling[manIndex] = vrouwIndex;
            manVrij[manIndex] = false;
            vrouwVrij[vrouwIndex] = false;
        } else { // (man', vrouw) bestaat
            int andereManIndex = 0;
            while(koppeling[andereManIndex] != vrouwIndex){
                andereManIndex++;
            }
            // als vrouw liever man heeft ipv man'
            if(voorkeurVrouw(vrouwIndex, manIndex, andereManIndex) == manIndex) {
                koppeling[andereManIndex] = -1;
                manVrij[andereManIndex] = true;
                koppeling[manIndex] = vrouwIndex;
                manVrij[manIndex] = false;
            }
        }
    }
    return koppeling;
}