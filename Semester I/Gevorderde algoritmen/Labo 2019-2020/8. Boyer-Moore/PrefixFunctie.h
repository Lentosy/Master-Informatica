#pragma once
#include <vector>
#include <string>


class PrefixFunctie {
public:
    static std::vector<int> geefPrefixTabel(const std::string& patroon) {
        std::vector<int> prefixtabel;
        prefixtabel.resize(patroon.size() + 1);
        prefixtabel[0] = -1;
        prefixtabel[1] = 0;

        for(int i = 2; i <= patroon.size(); i++) {
            int lengteVorigePrefix = prefixtabel[i - 1];
            while(lengteVorigePrefix > 0 && patroon[i - 1] != patroon[lengteVorigePrefix]) {
                lengteVorigePrefix = prefixtabel[lengteVorigePrefix];
            }
            if(patroon[i - 1]  == patroon[lengteVorigePrefix]) {
                lengteVorigePrefix++;
            }
            prefixtabel[i] = lengteVorigePrefix;
        } 
        return prefixtabel;
    }
};


