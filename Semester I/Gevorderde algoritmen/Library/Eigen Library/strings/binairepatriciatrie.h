

/*
* Bij een normale patriciatrie zijn er (3) gevallen die zich kunnen voordoen bij het toevoegen:
*    (1) We zitten in een explicite knoop en testindex = verschilindex  ->  blad toevoegen voor het karakter gegeven door woord[verschilindex] 
*    (2) We zitten in een explicite knoop en testindex > verschilindex  ->  expliciete knoop toevoegen met testindex = verschilindex met als twee kinderen: oude expliciete knoop en nieuw blad
*    (3) We zitten in een blad            en testindex = oneindig       ->  geval (2)
*
*
*
*
* Bij een binaire patriciatrie heeft elke expliciete inwendige knoop twee kinderen, zodat geval (1) uit het toevoegscenario niet kan voorkomen.
* We moeten dus altijd zowel een blad als een expliciete inwendige knoop toevoegen. 
* Men smelt deze samen in één structuur, zodat de noodzaak van bladpointers verdwijnt.
*/

#include <memory>
#include <string>
#include "varbitpatroon.h"
class TrieKnoop;
class BinairePatriciaTrie : std::unique_ptr<TrieKnoop> {
public:
    using std::unique_ptr<TrieKnoop>::unique_ptr;
    void voegToe(const Varbitpatroon& woord);
    std::unique_ptr<TrieKnoop>* zoek(const Varbitpatroon& woord);
};



class TrieKnoop {
public:
    TrieKnoop(int testindex, const Varbitpatroon& woord) : testindex{testindex}, woord{woord} {}
    int testindex;
    Varbitpatroon woord;

    BinairePatriciaTrie& geefKind(bool rechts) { // als bit 1 is, willen we naar rechts
        if (rechts){
            return this->rechts;
        } 
        return this->links;
    }
    BinairePatriciaTrie links, rechts;
};


/*
* Men moet dus, bij zoeken en toevoegen, onderscheid maken tussen:
    (1) een lege boom (de wortel heeft twee nulpointers en is een inwendige knoop, of de wortel is afwezig). Bij een boom met één sleutel is de wortel een blad met testindex -1.
    (2) een niet-lege boom. 
    
*/
void BinairePatriciaTrie::voegToe(const Varbitpatroon& woord) {
    std::unique_ptr<TrieKnoop>* plaats = zoek(woord);
    if(!plaats || (!(*plaats)->links) && !(*plaats)->rechts) {
        // lege boom
        *plaats = std::make_unique<TrieKnoop>(-1, woord);
    } else {
        // boom is niet leeg

        // soms kan het voorkomen dat knopen die versmelt zitten niet meer rechtstreeks onder elkaar zitten -> crazy shit

    }
}

std::unique_ptr<TrieKnoop>* BinairePatriciaTrie::zoek(const Varbitpatroon& woord) {
    BinairePatriciaTrie* huidig = this;
    if(!huidig || (!(*huidig)->links) && !(*huidig)->rechts) {
        // lege boom, niets doen
    } else {
        // boom is niet leeg
        int testindex = (*huidig)->testindex;
        bool bit = (*huidig)->woord.geefbit(testindex);
        huidig = &(*huidig)->geefKind(bit);  
    }

    return huidig;

}