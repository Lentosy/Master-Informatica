#include "graaf.h"
#include "componentengraaf.h"
#include <stack>
#include <vector>
#include <algorithm>


class RSSGraaf : public GraafMetKnoopdata<GERICHT, int> {
public:
    using GraafMetKnoopdata<GERICHT, int>::GraafMetKnoopdata;

    // Geeft de langste lijst van gezinnen waaran een stofzuiger verkocht moet worden
    std::vector<int> geefOptimalePad() {
        // 1. Maak componentgraaf op.
        ComponentenGraaf<int> componentenGraaf(this);
        
        // 2. Er wordt een map bijgehouden die een knoopnummer afbeeldt op een lijst van zijn inkomende verbindingen.
        std::map<int, std::vector<int>> knoopEnInkomendeVerbindingen;
        for(int i = 0; i < componentenGraaf.aantalKnopen(); i++){
            knoopEnInkomendeVerbindingen[i] = std::vector<int>();
            Burenlijst buren = componentenGraaf[i];
            Burenlijst::const_iterator burenIterator = buren.begin();
            while(burenIterator != buren.end()){
                int buur = burenIterator->first;
                knoopEnInkomendeVerbindingen[buur].push_back(i);
            }
        }
        
        
        std::vector<int> optimalePad;
        while(knoopEnInkomendeVerbindingen.size() > 0) { // Zolang er nog componenten zijn:
            // 3. Er wordt altijd een (willekeurig) component zonder inkomende verbindingen gezocht.
            std::map<int, std::vector<int>>::iterator it = knoopEnInkomendeVerbindingen.begin();

            while(it != knoopEnInkomendeVerbindingen.end() && it->second.size() != 0)
                it++;
            
            int componentKnoop = it->first;

            //  4. Uit dit component wordt een willekeurg huis gekozen en maakt deel uit van het optimale pad.
            int gekozenGezin = *(componentenGraaf.geefKnoopdata(componentKnoop));
            optimalePad.push_back(gekozenGezin);
            // 5. Dit 
            // de knoopnr nog verwijderen in de vector die de knoop als inkomende verbinding heeft
            it = knoopEnInkomendeVerbindingen.begin();
            while(it != knoopEnInkomendeVerbindingen.end()){
                std::vector<int>& inkomendeVerbindingen = it->second;
                inkomendeVerbindingen.erase(std::find(inkomendeVerbindingen.begin(), inkomendeVerbindingen.end(), gekozenGezin));
                it++;
            }
        }
        return optimalePad;
    }

    // Geeft de kortste lijst van gezinnen die je moet contacteren zodat elk gezin het weet
    std::vector<int> verwittigGezinnen() {

    }

private:
    // Een ongerichte graaf met per knoop het gezin dat gekozen moet worden
    GraafMetKnoopdata<GERICHT, int>& geefComponentenGraaf() {



        GraafMetKnoopdata<GERICHT, int>* componentenGraaf = new GraafMetKnoopdata<GERICHT, int>();
        componentenGraaf->voegKnoopToe(4);
        
        // keer graaf om    
        // zoek DEZ in omgekeerde graaf en nummer post-order
        // Zoek DEZ in originele, startend vanaf knoop met hoogste post-order nummer

        //resultaat is diepte-eerst bos, waarvan elke boom een component is (en zo kan de lijst van gezinnen opgesteld worden)
        return *componentenGraaf;
    }
};