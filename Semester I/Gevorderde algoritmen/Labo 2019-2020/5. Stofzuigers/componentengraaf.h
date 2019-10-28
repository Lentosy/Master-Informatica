#include "graaf.h"
#include <algorithm>
#include <vector>
#include <stack>

typedef std::map<int, int> Burenlijst;
template <class T>
class ComponentenGraaf : public GraafMetKnoopdata<GERICHT, T> {
public:
    ComponentenGraaf(Graaf<GERICHT>* graaf) {
        // Keer graaf om
        Graaf<GERICHT>* omgekeerdeGraaf(graaf);
        keerGraafOm(omgekeerdeGraaf);
        omgekeerdeGraaf->teken("dot/omgekeerdeGraaf.dot");

        // Post order nummeren van knopen met diepte eerst zoeken
        std::vector<bool> reedsBezocht(omgekeerdeGraaf->aantalKnopen(), false);
        std::stack<int> knopenInPostOrder;
        //std::vector<std::pair<int, int>> post(omgekeerdeGraaf->aantalKnopen());
        for(int i = 0; i < omgekeerdeGraaf->aantalKnopen(); i++){
            if(!reedsBezocht[i]){
                nummerPostOrder(i, knopenInPostOrder, reedsBezocht, omgekeerdeGraaf);
            }   
        }

       // while(!knopenInPostOrder.empty()){
        //    std::cout << knopenInPostOrder.top() << "\n";
        //    knopenInPostOrder.pop();
       // }
 
        reedsBezocht = std::vector<bool>(omgekeerdeGraaf->aantalKnopen(), false);
        while(!knopenInPostOrder.empty()) {
            int knoop = knopenInPostOrder.top();
            knopenInPostOrder.pop();
            if(!reedsBezocht[knoop]){
                std::cout << "Nieuw boom in bos met wortel " << knoop << "\n";
                diepteEerstZoeken(knoop, reedsBezocht, graaf);
            }    
        }
    }

private:
    void keerGraafOm(Graaf<GERICHT>* graaf) const {
        std::vector<std::pair<int, int>> verbindingen;
        for(int i = 0; i < graaf->aantalKnopen(); i++){
            Burenlijst buren = (*graaf)[i];
            Burenlijst::const_iterator burenIterator = buren.begin();
            while(burenIterator != buren.end()) {
                int buur = burenIterator->first;
                verbindingen.push_back(std::make_pair(i, buur));  
                graaf->verwijderVerbinding(i, buur);   
                burenIterator++;
            }
        }
        // Het volgende mag niet in de burenIterator lus gebruikt worden, er kan een omgekeerde verbinding reeds bestaan
        for(int i = 0; i < verbindingen.size(); i++){
            graaf->voegVerbindingToe(verbindingen[i].second, verbindingen[i].first);
        }
    }

    void nummerPostOrder(int knoop, std::stack<int>& postOrdering, std::vector<bool>& reedsBezocht, Graaf<GERICHT>* graaf) const {
        reedsBezocht[knoop] = true;
        Burenlijst buren = graaf->operator[](knoop);
        Burenlijst::const_iterator burenIterator = buren.begin();
        while(burenIterator != buren.end()){
            int buur = burenIterator->first;
            if(!reedsBezocht[buur]){
                nummerPostOrder(buur, postOrdering, reedsBezocht, graaf);
            }
            burenIterator++;
        }
        postOrdering.push(knoop);
    }

    void diepteEerstZoeken(int knoop, std::vector<bool>& reedsBezocht, Graaf<GERICHT>* graaf) {
        
        reedsBezocht[knoop] = true;
        Burenlijst buren = graaf->operator[](knoop);
        Burenlijst::const_iterator burenIterator = buren.begin();
        while(burenIterator != buren.end()){
            int buur = burenIterator->first;
            if(!reedsBezocht[buur]){
                diepteEerstZoeken(buur, reedsBezocht, graaf);
            }
            burenIterator++;
        }
    }
};