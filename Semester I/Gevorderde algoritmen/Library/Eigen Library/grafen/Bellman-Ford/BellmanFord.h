#include "graaf.h"
#include <iostream>
#include <queue>

template<class Takdata>
class BellmanFord {
public:
    BellmanFord(GraafMetTakdata<GERICHT, Takdata> const * const graaf) : graaf{graaf} {};
    std::vector<Takdata> geefKortsteAfstanden(int startKnoop) const;

private:
    GraafMetTakdata<GERICHT, Takdata> const * const graaf;
};



/*
* Bellman-Ford, eerste implementatie met wachtrij P.68
*/
template<class Takdata>
std::vector<Takdata> BellmanFord<Takdata>::geefKortsteAfstanden(int startKnoop) const {

    std::vector<Takdata> afstanden(graaf->aantalKnopen(), INT_MAX); // zet alle afstanden naar elke knoop op oneindig
    afstanden[startKnoop] = 0; // afstand van startknoop is 0


    std::queue<int> teBehandelenKnopen; // Deze knoop bevat de te behandelen knopen voor elke iteratie
    for(int i = 0; i < graaf->aantalKnopen(); i++){ // Initieël zijn dit alle knopen
        teBehandelenKnopen.emplace(i); 
    }

    for(int k = 1; k < graaf->aantalKnopen() - 1; k++) { // k verbindingen toelaten in het pad, = n iteraties
        std::queue<int> iteratieKnopen; // De knopen die voor deze iteratie onderzocht zullen worden
        std::swap(iteratieKnopen, teBehandelenKnopen); // Omdat de queue voor slechts 1 iteratie dient

        while(!iteratieKnopen.empty()){
            int vanKnoop = iteratieKnopen.front();
            iteratieKnopen.pop();

            Burenlijst buren = graaf->operator[](vanKnoop);
            Burenlijst::const_iterator burenIterator = buren.begin();

            while(burenIterator != buren.end()) {
                int naarKnoop = burenIterator->first;
                const Takdata* afstand = graaf->geefTakdata(vanKnoop, naarKnoop);
                if(afstand && afstanden[vanKnoop] + *afstand < afstanden[naarKnoop]){ 
                    afstanden[naarKnoop] = afstanden[vanKnoop] + *afstand;
                    teBehandelenKnopen.push(naarKnoop); // omdat de buur van een knoop werd aangepast, moet deze buur op de wachtrij geplaatst worden om dat zijn buren met de nieuwe afstand getest moeten worden
                }
                burenIterator++;
            }
        }
    }

    // Als de wachtrij niet ledig is na n iteraties zit er een negatieve lus in de graaf
    if(!teBehandelenKnopen.empty()) {
        std::cout << "Negatieve lus in de graaf\n";
        afstanden.clear();
    }

    return afstanden;
}