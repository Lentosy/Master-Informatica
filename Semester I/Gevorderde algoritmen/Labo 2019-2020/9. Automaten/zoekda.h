#pragma once
#include <string>
#include <map>
#include <stack>
#include <set>
#include <vector>
#include "thompsonna.h"

class ZoekDA { // deterministische automaat
public:
    ZoekDA(ThompsonNA& thompsonNA) {
        construeerBloem(thompsonNA);
    }

    bool zoek(std::string& lijn);
private:
    void construeerBloem(ThompsonNA& thompsonNA);
    std::vector<int> eSluiting(std::vector<int> T); // bepaal de statenbits bereikbaar vanuit een verzameling statenbits T  
    void deelverzamelingconstructie(ThompsonNA& thompsonNA); // converteer de thompsonNA naar een DA
 
    
    int beginstaat;
    std::vector<int> eindstaten;
    std::vector<std::vector<int>> overgangstabel;
};

bool ZoekDA::zoek(std::string& lijn){
    bool gevonden = false;
    

   return gevonden;
}



void ZoekDA::construeerBloem(ThompsonNA& thompsonNA) {
    for(int i = 0; i < 26; i++){
        thompsonNA.verbind(0, 0, (unsigned char)i + 'a');
    }
    thompsonNA.teken("NA.dot");
}


void ZoekDA::deelverzamelingconstructie(ThompsonNA& thompsonNA) {
    typedef std::vector<int> Staat;
    int staatnummer = 0;
    std::map<Staat, int> volgnummer;
    std::stack<Staat> DEZstack;

    std::vector<int> startstaat = { 0 };
    Staat T = eSluiting(startstaat);
    volgnummer.emplace(T, staatnummer++);
    DEZstack.push(T);
    while(!DEZstack.empty()) {
        T = DEZstack.top();
        DEZstack.pop();
        for(int i = 0; i < 26; i++) {
            
        }
    }
}
 