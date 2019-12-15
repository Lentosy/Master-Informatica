#include "../graaf.h"
#include <iostream>
#include <vector>


class TransitieveSluiting {
public:
    TransitieveSluiting(Graaf<GERICHT> const * const graaf) : graaf{graaf} {};
    Graaf<GERICHT> bepaalTransitieveSluiting() const;
    

private:
    Graaf<GERICHT> const * const graaf;
};


Graaf<GERICHT> TransitieveSluiting::bepaalTransitieveSluiting() const {

    std::vector<std::vector<bool>> T(graaf->aantalKnopen(), std::vector<bool>(graaf->aantalKnopen(), false));
    // Initialisatie T0
    for(int i = 0; i < graaf->aantalKnopen(); i++){
        T[i][i] = true; // i = j
        Burenlijst buren = graaf->operator[](i);
        Burenlijst::const_iterator burenIterator = buren.begin();
        while(burenIterator != buren.end()){
            T[i][burenIterator->first] = true;  // g_{ij} < inf
            burenIterator++;
        }
    }

    for(int k = 1; k < graaf->aantalKnopen(); k++) {
        for(int i = 0; i < graaf->aantalKnopen(); i++) {
            for(int j = 0; j < graaf->aantalKnopen(); j++) {
                T[i][j] = T[i][j] | (T[i][k] & T[k][j]);
            }
        }
    }

    Graaf<GERICHT> transitieveSluiting(graaf->aantalKnopen());
    for(int i = 0; i < graaf->aantalKnopen(); i++) {
        for(int j = 0; j < graaf->aantalKnopen(); j++) {
            if(T[i][j] == true){
                transitieveSluiting.voegVerbindingToe(i, j);
            }
        }
    }
    
    return transitieveSluiting;
}