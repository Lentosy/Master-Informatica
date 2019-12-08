#include <memory>
using std::unique_ptr;
using std::make_unique;
using std::move;
#include <queue>
using std::queue;
#include <string>
using std::string;
#include <sstream>
using std::ostringstream;
#include <fstream>
using std::ofstream;
#include <iostream>
using std::cout;


#include "patriciatrie.h"


PatriciaTrie::PatriciaTrie() {
    *this = (unique_ptr<TrieKnoop>) std::make_unique<TrieNietBlad>(0);
}

PatriciaTrie::PatriciaTrie(unique_ptr<TrieKnoop>&& o) : unique_ptr<TrieKnoop>(move(o)) {};
PatriciaTrie& PatriciaTrie::operator=(unique_ptr<TrieKnoop>&& o) {
    unique_ptr<TrieKnoop>::operator=(move(o));
    return *this;
}

unique_ptr<TrieKnoop>* PatriciaTrie::zoek(const string& s) {
    unique_ptr<TrieKnoop>* huidig = this;
    while(*huidig && !(*huidig)->isBlad()) {
        TrieNietBlad* inwendigeKnoop = static_cast<TrieNietBlad*>(huidig->get());
        huidig = &(inwendigeKnoop->kinderen[s[inwendigeKnoop->testindex]]);
    }
    return huidig;
}

void PatriciaTrie::voegToe(const string& s) {   
    unique_ptr<TrieKnoop>* plaats = zoek(s);
    if(!*plaats){
        *plaats = (unique_ptr<TrieKnoop>) make_unique<TrieBlad>(s);
        cout << "blad aanmaken | " << (static_cast<TrieBlad*>(plaats->get()))->s << "\n";
    } else if(!(*plaats)->isBlad()) {
        cout << "inwendige knoop\n";
    }
}




void PatriciaTrie::teken(const char* bestandsnaam) const {
    ostringstream dotcode;
    dotcode << "digraph G {";

    std::queue<std::pair<TrieKnoop*, int>> BEqueue;
    int knoopteller = 0;
    BEqueue.emplace(this->get(), knoopteller);
    while(!BEqueue.empty()){
        std::pair<TrieKnoop*, int> f = BEqueue.front();
        TrieKnoop* huidig = f.first;
        int ouder = f.second;
        knoopteller++;
        if(ouder > 0){
            dotcode << "knoop" << ouder << " -> knoop" << knoopteller << "\n";
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
                unique_ptr<TrieKnoop>* kind = &huidigNietblad->kinderen[i];
                if(*kind){
                    BEqueue.emplace(std::make_pair(kind->get(), knoopteller));
                } else {
                    BEqueue.emplace(std::make_pair(nullptr, knoopteller));
                }
            }
        }
        BEqueue.pop();
    }

    dotcode << "\n}";
    ofstream output(bestandsnaam);
    output << dotcode.str();
    output.close();
}