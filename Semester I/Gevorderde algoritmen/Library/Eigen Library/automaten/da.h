
#include "thompsonna.h"

#include <vector>
#include <map>
#include <stack>

class DA {
public:
    DA(const ThompsonNA& na);
    
private:
    int beginstaat;
    std::vector<int> eindstaten;
    std::vector<std::vector<int>> overgangstabel;

    std::vector<int> eSluiting(std::vector<int> T); // bepaal de statenbits bereikbaar vanuit een verzameling statenbits T  
    void deelverzamelingconstructie(ThompsonNA& thompsonNA); // converteer de thompsonNA naar een DA
};



DA::DA(const ThompsonNA& na) {
    
}

std::vector<int> DA::eSluiting(std::vector<int> T) {
    std::vector<int> esluiting;
    std::stack<int> DEZstack;
    for(int i = 0; i < T.size(); i++) {
        int t = T[i];
        esluiting.emplace_back(t);
        DEZstack.push(t);
    }

    while(!DEZstack.empty()) {
        int bit = DEZstack.top(); DEZstack.pop();
        
    }    

    return esluiting;
}

void DA::deelverzamelingconstructie(ThompsonNA& thompsonNA) {
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