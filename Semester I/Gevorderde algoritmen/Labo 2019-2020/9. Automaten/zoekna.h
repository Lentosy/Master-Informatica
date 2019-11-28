#pragma once
#include <string>
#include <stack>
#include <vector>
#include "thompsonna.h"


class ZoekNA { // deterministische auto
public:
    ZoekNA(const ThompsonNA& thompsonNA);
    bool zoek(std::string& lijn);
private:
    std::vector<std::vector<int>> overgangstabel;
    void construeerBloem(); // nieuwe verbindingen toevoegen aan b_0: elk karakter van het alfabet
    std::vector<int> eSluiting(const ThompsonNA& thompsonNA, std::vector<int> T);
};



std::vector<int> ZoekNA::eSluiting(const ThompsonNA& thompsonNA, std::vector<int> T) {
    std::vector<int> eSluiting;
    
    std::stack<int> DEZstack;
    for(int i = 0; i < T.size(); i++) {
        eSluiting.push_back(T[i]);
        DEZstack.push(T[i]);
    }

    while(!DEZstack.empty()){
        int statenbit = DEZstack.top();
        DEZstack.pop();
        //for(int i = 0; i < T.size(); i++){
        for(int i = 0; i < thompsonNA.geefAantalVerbindingen(); i++){
            ThompsonNA::Verbinding v = thompsonNA.overgang[i];
            if(v.geefBron() == statenbit && v.geefKarakter() == epsilon && !eSluiting[statenbit]){
                eSluiting.push_back(i);
                DEZstack.push(i);
            }
        }
    }

    return eSluiting;
}