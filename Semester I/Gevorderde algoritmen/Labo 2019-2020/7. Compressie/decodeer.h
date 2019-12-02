#include <iostream>
#include <fstream>
#include <string>
#include "binairetrie.h"
#include "bitstream.h"
#include "bincode.h"


class Decodeer {
public:

    // Constructor die 'vanBestand' decodeert, met behulp van 'codeBestand', naar 'naarBestand'
    Decodeer(const char * vanBestand, const char * naarBestand, const char * codeBestand) {
        
        Bincode bincode(codeBestand); // stel de code op 
        BinaireTrie huffmanTrie(bincode); // maak een huffmantrie met de bijhorende code

        BinaireTrie* huidig = &huffmanTrie; // deze pointer naar de trie zal dienen om af te dalen in de trie
        ibitstream invoer(vanBestand); 
        std::ofstream uitvoer(naarBestand);
        while(!invoer.fail()) { // het hele bestand inlezen, bit per bit
            bool bit = invoer.leesbit();
            
            if(!(*huidig)->isBlad()){ // zolang de pointer niet naar een blad wijst, moeten we naar links of naar rechts afdalen, afhankelijk van het bit
                TrieNietblad* nietBlad = static_cast<TrieNietblad*>(huidig->get());
                huidig = &(nietBlad->geefKind(bit));
            } 

            if((*huidig)->isBlad()) { // kan zijn dat door de vorige if statement, we nu wel al in een blad zitten
                TrieBlad* blad = static_cast<TrieBlad*>(huidig->get());
                uitvoer << char(blad->karakter);
                huidig = &huffmanTrie;
            }
        }
        invoer.close();
        uitvoer.close();
    }

};









// Bijkomende opgave:   zorg ervoor dat code.dat met minder bytes opgeslagen wordt
// mogelijkheden
// 1) doe alsof het een gewoon een bestand is en codeer met huffmantrie