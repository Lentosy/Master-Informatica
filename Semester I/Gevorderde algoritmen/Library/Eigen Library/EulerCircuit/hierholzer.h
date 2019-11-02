#pragma once

#include "graaf.h"
#include <map>
#include <stack>



typedef std::map<int, int> Burenlijst;
class Hierholzer {

public:
    // veronderstel dat graaf samenhangend is, en een eulergraaf is
    std::vector<int> construeerEulerCircuit(const Graaf<GERICHT>* eulergraaf) {
        std::vector<int> eulercircuit; // In deze vector komen de knoopnummers die in volgorde bezocht moeten worden om het eulercircuit te bekomen
        std::stack<int> huidigpad; // Deze stack houdt knopen bij die deel uitmaken van een lus, maar nog niet in het eulercircuit zitten
        std::vector<bool> gebruikteVerbindingen(eulergraaf->aantalVerbindingen(), false); // Deze vector houdt bij welke verbindingen reeds gebruikt zijn in het eulercircuit

        int startknoop = 0; // De startknoop van het eulercircuit
        int padknoop = 0;   // een padknoop is een knoop op het huidigpad
        huidigpad.push(startknoop);
        while(!huidigpad.empty()) {
            // Zoek een lus L
            do {
                const Burenlijst& buren = (*eulergraaf)[padknoop];
                Burenlijst::const_iterator burenIterator = buren.begin();
                // geef de eerste buurknoop waarvan de verbinding nog niet gebruikt is in het eulercircuit
                while(burenIterator != buren.end() && gebruikteVerbindingen[burenIterator->second]){
                    burenIterator++;
                }
                padknoop = burenIterator->first;
                gebruikteVerbindingen[burenIterator->second] = true;
                huidigpad.push(padknoop);

            } while(padknoop != startknoop);

            // Er is een lus L gevonden
            // wandel het omgekeerde pad af, en als een knoop geen verbindingen meer heeft, push dan in eulercircuit
            bool knoopHeeftNogBuren = false;
            while(!knoopHeeftNogBuren && !huidigpad.empty()) { // zolang we knopen hebben die geen bereikbare buren meer hebben
                int knoop = huidigpad.top();
                // zoek buren die nog niet op het pad liggen
                const Burenlijst& buren = (*eulergraaf)[knoop];
                Burenlijst::const_iterator burenIterator = buren.begin();
                while(burenIterator != buren.end() && gebruikteVerbindingen[burenIterator->second]) {
                    burenIterator++;
                }
                if(burenIterator == buren.end()) {
                    // de huidige knoop in het pad heeft geen bereikbare buren die nog niet op het pad liggen
                    eulercircuit.emplace_back(knoop);
                    huidigpad.pop();
                }  else {
                    knoopHeeftNogBuren = true;
                }
            }
            // bepalen volgende startknoop
            if(!huidigpad.empty()){
                startknoop = huidigpad.top();
                padknoop = startknoop;
            }
        }
        std::reverse(eulercircuit.begin(), eulercircuit.end()); 
        return eulercircuit;
    }
};