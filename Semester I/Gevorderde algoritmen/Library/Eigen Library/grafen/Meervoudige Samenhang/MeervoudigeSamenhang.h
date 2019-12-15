#include "../stroomnet.h"
#include "../graaf.h"

#include <iostream>
class MeervoudigeSamenhang {
public:
    MeervoudigeSamenhang(const Graaf<GERICHT>* graaf);
    MeervoudigeSamenhang(const Graaf<ONGERICHT>* graaf);


    int bepaalGraad();

private:
    Stroomnetwerk<int> stroomnet;
};

MeervoudigeSamenhang::MeervoudigeSamenhang(const Graaf<GERICHT>* graaf) : stroomnet(graaf->aantalKnopen(), 0, 1) {
    for(int van = 0; van < graaf->aantalKnopen(); van++){
        Burenlijst buren = graaf->operator[](van);
        Burenlijst::const_iterator burenIterator = buren.begin();
        while(burenIterator != buren.end()) {
            int naar = burenIterator->first;
            stroomnet.voegVerbindingToe(van, naar, 1);
            burenIterator++;
        }
    }
}

MeervoudigeSamenhang::MeervoudigeSamenhang(const Graaf<ONGERICHT>* graaf) : stroomnet(graaf->aantalKnopen(), 0, 1) {
    for(int van = 0; van < graaf->aantalKnopen(); van++){
        Burenlijst buren = graaf->operator[](van);
        Burenlijst::const_iterator burenIterator = buren.begin();
        while(burenIterator != buren.end()) {
            int naar = burenIterator->first;
            if(naar > van) {   // voorkomen dat verbindingen twee keer toegevoegd worden in latere iteratie
                stroomnet.voegVerbindingToe(van, naar, 1);
                stroomnet.voegVerbindingToe(naar, van, 1);
            }
            burenIterator++;
        }
    }
}

int MeervoudigeSamenhang::bepaalGraad() {
    int min = stroomnet.geefStroom().geefCapaciteit();
    for(int i = 0; i < stroomnet.aantalKnopen() - 1; i++){ // moeten slechts stroomnetwerken van opeenvolgende knopenparen oplossen -> P 82 laatste paragraaf 
        Stroomnetwerk<int> volgendStroomnet(stroomnet, i, i + 1);
        int waarde = volgendStroomnet.geefStroom().geefCapaciteit();
        if(waarde < min)
            min = waarde;
    }
    return min; 
}