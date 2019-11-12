#include "graaf.h"
#include <vector>
#include <algorithm>

typedef std::map<int, int> Burenlijst;
class DubbeleSamenhang { 
public:
    // Geeft een vector van verbindingsnummers terug die een brug zijn
    std::vector<int> zoekBruggen() {

    }

    // Geeft een vector van knoopnummers terug die een scharnierpunt zijn
    std::vector<int> zoekScharnierpunten(const Graaf<ONGERICHT>* graaf) {
        std::vector<bool> ontdekt(graaf->aantalKnopen(), false);
        std::vector<int> ouder(graaf->aantalKnopen(), -1);
        std::vector<int> preordernummering(graaf->aantalKnopen(), -1);
        std::vector<int> laagste(graaf->aantalKnopen(), -1);
        int preordernummer = 0;
        std::vector<int> scharnierpunten;

        // de graaf wordt samenhangend onderstelt
        zoekScharnierpuntenRecursief(0, graaf, ontdekt, ouder, preordernummer, preordernummering, laagste, scharnierpunten);
        return scharnierpunten;
    }

private:

    void zoekScharnierpuntenRecursief(int knoopnr, const Graaf<ONGERICHT>* graaf, std::vector<bool>& ontdekt, std::vector<int>& ouder, int& preordernummer, std::vector<int>& preordernummering, std::vector<int>& laagste, std::vector<int>& scharnierpunten) {
        ontdekt[knoopnr] = true;
        preordernummering[knoopnr] = preordernummer++;
        laagste[knoopnr] = preordernummering[knoopnr];
        Burenlijst buren = (*graaf)[knoopnr];
        Burenlijst::const_iterator burenIterator = buren.begin();
        while(burenIterator != buren.end()) {
            int buurnr = burenIterator->first;
            if(!ontdekt[buurnr]) {
                ouder[buurnr] = knoopnr;
                zoekScharnierpuntenRecursief(buurnr, graaf, ontdekt, ouder, preordernummer, preordernummering, laagste, scharnierpunten);
                if(laagste[buurnr] < laagste[knoopnr]) {
                    laagste[knoopnr] = laagste[buurnr];
                } else if(laagste[buurnr] >= preordernummering[knoopnr]){
                    std::cout << "Knoop " << knoopnr << " is een scharnierpunt voor " << buurnr << "\n";
                    //scharnierpunten.emplace_back(knoopnr);
                }
            } else {
                if(buurnr != ouder[knoopnr]) {
                    if(preordernummering[buurnr] < laagste[knoopnr]) {
                        laagste[knoopnr] = preordernummering[buurnr];
                    }
                }
            }
            burenIterator++;
        }
    }

};