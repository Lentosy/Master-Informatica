#include "BellmanFord.h"
#include <iostream>


template<class Takdata>
class Johnson {
public:
    Johnson(GraafMetTakdata<GERICHT, Takdata>* graaf) : graaf{graaf} {};
    std::vector<std::vector<Takdata>> geefKortsteAfstanden() const;

private:
    GraafMetTakdata<GERICHT, Takdata>*  graaf;
};

template<class Takdata>
std::vector<std::vector<Takdata>> Johnson<Takdata>::geefKortsteAfstanden() const {
    std::vector<std::vector<Takdata>> afstanden(graaf->aantalKnopen(), std::vector<Takdata>(graaf->aantalKnopen()));
    GraafMetTakdata<GERICHT, Takdata> copyGraaf = *graaf;
    int s = copyGraaf.voegKnoopToe();
    for(int i = 0; i < graaf->aantalKnopen(); i++) {
        copyGraaf.voegVerbindingToe(s, i, 0);
    }

    BellmanFord<Takdata> bf(&copyGraaf); // iets mis met bellmanford
    std::vector<Takdata> bfAfstanden = bf.geefKortsteAfstanden(s);
    for(int i = 0; i < bfAfstanden.size(); i++){
        std::cout << bfAfstanden[i] << "\n";
    }





    return afstanden;
}