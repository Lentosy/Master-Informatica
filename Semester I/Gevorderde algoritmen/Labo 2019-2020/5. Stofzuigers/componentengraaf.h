#include "graaf.h"
#include <algorithm>
#include <vector>
#include <stack>

typedef std::map<int, int> Burenlijst;
class ComponentenGraaf : public GraafMetKnoopdata<GERICHT, int> {
public:
    ComponentenGraaf() {}
    ComponentenGraaf(Graaf<GERICHT>* graaf) {
        // de omgekeerde graaf
        keerGraafOm(graaf);
        // Post order nummeren van knopen met diepte eerst zoeken
        std::vector<bool> reedsBezocht(graaf->aantalKnopen(), false);
        std::stack<int> knopenInPostOrder;
        //std::vector<std::pair<int, int>> post(omgekeerdeGraaf->aantalKnopen());
        for(int i = 0; i < graaf->aantalKnopen(); i++){
            if(!reedsBezocht[i]){
                nummerPostOrder(i, knopenInPostOrder, reedsBezocht, graaf);
            }   
        }

        keerGraafOm(graaf); // terug de oorspronkelijke graaf
        reedsBezocht = std::vector<bool>(graaf->aantalKnopen(), false);
        std::vector<std::vector<int>> componenten; // houdt per component een lijst van knoopnrs in dat component bij
        while(!knopenInPostOrder.empty()) {
            int knoop = knopenInPostOrder.top();
            knopenInPostOrder.pop();
            if(!reedsBezocht[knoop]){
                int componentindex = componenten.size();
                componenten.resize(componenten.size() + 1);
                diepteEerstZoeken(knoop, componentindex, componenten, reedsBezocht, graaf);
                this->voegKnoopToe(knoop);     
            }    
        }

        // todo, verbindingen leggen -> fucking geen componentgraaf nodig, maar enkel met de vector van componenten had je ook al genoeg -> maar geen zin om dit aan te passen
        for(int i = 0; i < componenten.size(); i++){
            for(int j = 0; j < componenten[i].size(); j++){
                std::cout << componenten[i][j] << " - ";
            }
            std::cout << "\n";
        }
        this->teken("dot/componentengraaf.dot");
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

    void diepteEerstZoeken(int knoop, int componentindex, std::vector<std::vector<int>>& componenten, std::vector<bool>& reedsBezocht, Graaf<GERICHT>* graaf) {
        
        reedsBezocht[knoop] = true;
        componenten[componentindex].push_back(knoop);
        Burenlijst buren = graaf->operator[](knoop);
        Burenlijst::const_iterator burenIterator = buren.begin();
        while(burenIterator != buren.end()){
            int buur = burenIterator->first;
            if(!reedsBezocht[buur]){
                diepteEerstZoeken(buur, componentindex, componenten, reedsBezocht, graaf);
            }
            burenIterator++;
        }
    }
};