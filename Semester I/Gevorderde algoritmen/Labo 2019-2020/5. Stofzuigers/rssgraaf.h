#include "graaf.h"
#include "componentengraaf.h"
#include <stack>
#include <vector>
#include <algorithm>


class RSSGraaf : public GraafMetKnoopdata<GERICHT, int> {
public:
    using GraafMetKnoopdata<GERICHT, int>::GraafMetKnoopdata;

    // Geeft de langste lijst van gezinnen waaran een stofzuiger verkocht moet worden
    void geefOptimalePad(std::vector<int>& optimalePad) {
        // 1. Maak componentgraaf op.

        ComponentenGraaf componentenGraaf(this);
        return;
        /*
        int a = componentenGraaf.voegKnoopToe(5);
        int b = componentenGraaf.voegKnoopToe(2);
        int c = componentenGraaf.voegKnoopToe(0);

        componentenGraaf.voegVerbindingToe(c, a);
        componentenGraaf.voegVerbindingToe(c, b);
        componentenGraaf.voegVerbindingToe(b, a);

        componentenGraaf.teken("dot/componentengraaf.dot");*/
        
        // 2. Er wordt een map bijgehouden die een knoopnummer afbeeldt op een lijst van zijn inkomende verbindingen.
        std::vector<std::vector<int>> inkomendeVerbindingenPerKnoop(componentenGraaf.aantalKnopen());
       // std::map<int, std::vector<int>> knoopEnInkomendeVerbindingen;
        for(int i = 0; i < componentenGraaf.aantalKnopen(); i++){
            Burenlijst buren = componentenGraaf[i];
            Burenlijst::const_iterator burenIterator = buren.begin();
            while(burenIterator != buren.end()){
                int buur = burenIterator->first;
                inkomendeVerbindingenPerKnoop[buur].push_back(i);
                std::cout << "knoop " << buur << " heeft als inkomende verbinding " << i << "\n";
                burenIterator++;
            }
        }
        
        
        while(inkomendeVerbindingenPerKnoop.size() > 0) { // Zolang er nog componenten zijn:
            // 3. Er wordt altijd een (willekeurig) component zonder inkomende verbindingen gezocht.
            int componentKnoop = 0;
            while(componentKnoop < inkomendeVerbindingenPerKnoop.size() && inkomendeVerbindingenPerKnoop[componentKnoop].size() != 0){
                componentKnoop++;
            }

            std::cout << "Component " << componentKnoop << " wordt gekozen\n";
            //  4. Uit dit component wordt een willekeurg huis gekozen en maakt deel uit van het optimale pad.
            int gekozenGezin = *(componentenGraaf.geefKnoopdata(componentKnoop));
            optimalePad.push_back(gekozenGezin);
            std::cout << "Het bijhorende gezin is " << gekozenGezin << "\n";
            // 5. Dit 
            // de knoopnr nog verwijderen in de vector die de knoop als inkomende verbinding heeft
           
            for(int i = 0; i < inkomendeVerbindingenPerKnoop.size(); i++){      
                std::vector<int>& inkomendeVerbindingen = inkomendeVerbindingenPerKnoop[i];   
                inkomendeVerbindingen.erase(std::find(inkomendeVerbindingen.begin(), inkomendeVerbindingen.end(), gekozenGezin));
            }  
        }
    }

    // Geeft de kortste lijst van gezinnen die je moet contacteren zodat elk gezin het weet
    std::vector<int> verwittigGezinnen() {

    }
};