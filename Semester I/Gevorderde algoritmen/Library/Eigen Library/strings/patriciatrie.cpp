#include <memory>
#include <queue>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <tuple>


#include "patriciatrie.h"


PatriciaTrie::PatriciaTrie() {
    *this = (KnoopPtr) std::make_unique<TrieNietBlad>(0);
}

PatriciaTrie::PatriciaTrie(KnoopPtr&& o) : KnoopPtr(std::move(o)) {};
PatriciaTrie& PatriciaTrie::operator=(KnoopPtr&& o) {
    KnoopPtr::operator=(std::move(o));
    return *this;
}

KnoopPtr* TrieNietBlad::geefKind(char c) {
    return &kinderen[c - 'a'];
}


/*
* Zoeken eindigt altijd in een blad.
*/
KnoopPtr* PatriciaTrie::zoek(const std::string& s) {
    KnoopPtr* huidig = this;
    while(*huidig && !(*huidig)->isBlad()) {
        TrieNietBlad* inwendigeKnoop = static_cast<TrieNietBlad*>(huidig->get());
        huidig = inwendigeKnoop->geefKind(s[inwendigeKnoop->testindex]);
    }
    return huidig;
}

void PatriciaTrie::voegToe(const std::string& s) {   
    KnoopPtr* plaats = zoek(s);
    if(!*plaats){
        // Eenvoudigste geval: bij nullpointer kan je gewoon blad aanmaken met de string
        *plaats = (KnoopPtr) std::make_unique<TrieBlad>(s);
    } else if((*plaats)->isBlad()) {
        // Anderzijds zitten we in een blad
        TrieBlad* blad = static_cast<TrieBlad*>(plaats->get());
        std::string bladString = blad->s;

        int verschilindex = 0;
        int kleinste = std::min(bladString.size(), s.size());
        while(verschilindex < kleinste && bladString[verschilindex] == s[verschilindex]) {
            verschilindex++;
        }

        plaats->reset(); // blad moet een inwendige knoop worden
        *plaats = (KnoopPtr) std::make_unique<TrieNietBlad>(verschilindex);
        TrieNietBlad* nietBlad = static_cast<TrieNietBlad*>(plaats->get());
        *nietBlad->geefKind(bladString[verschilindex]) = (KnoopPtr) std::make_unique<TrieBlad>(bladString);
        *nietBlad->geefKind(s[verschilindex]) = (KnoopPtr) std::make_unique<TrieBlad>(s);
    }
}



















void PatriciaTrie::teken(const char* bestandsnaam) const {
    std::ostringstream dotcode;
    dotcode << "digraph G {";

    std::queue<std::tuple<TrieKnoop*, int, char>> BEqueue;
    int knoopteller = 0;
    BEqueue.emplace(this->get(), knoopteller, '0');
    while(!BEqueue.empty()){
        std::tuple<TrieKnoop*, int, char> f = BEqueue.front();
        TrieKnoop* huidig = std::get<0>(f);
        int ouder = std::get<1>(f);
        char uitgang = std::get<2>(f);
        knoopteller++;
        if(ouder > 0){
            dotcode << "knoop" << ouder << " -> knoop" << knoopteller << "[label=\"" <<  uitgang << "\"]\n";
        }
        
        if(!huidig){ // nullknoop
            dotcode << "knoop" << knoopteller << "[shape=point]\n" ;
        }
        else if(huidig->isBlad()){ // bladknoop
            TrieBlad* huidigBlad = static_cast<TrieBlad*>(huidig);
            dotcode << "knoop" << knoopteller << "[shape=square, label=\"" << huidigBlad->s << "\"]\n";           
        } else { // inwendigeknoop
            TrieNietBlad* huidigNietblad = static_cast<TrieNietBlad*>(huidig);
            dotcode << "knoop" << knoopteller << "[label=\"" << huidigNietblad->testindex << "\"]\n";
            // kinderen toevoegen aan de queue
            for(int i = 0; i < 26; i++){
                KnoopPtr* kind = huidigNietblad->geefKind(i + 'a');
                if(*kind){
                    BEqueue.emplace(std::make_tuple(kind->get(), knoopteller, i + 'a'));
                } else {
                    BEqueue.emplace(std::make_tuple(nullptr, knoopteller, i + 'a'));
                }
            }
        }
        BEqueue.pop();
    }

    dotcode << "\n}";
    std::ofstream output(bestandsnaam);
    output << dotcode.str();
    output.close();
}