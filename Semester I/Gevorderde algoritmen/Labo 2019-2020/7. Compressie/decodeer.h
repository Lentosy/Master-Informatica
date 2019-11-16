#include <iostream>
#include <string>
#include "binairetrie.h"
#include "bitstream.h"
#include "bincode.h"


class Decodeer {
public:

//decodeer TimErweten.cps naar TimErweten.txt, gebruik makend van code.dat
    //Decodeer("TimErweten.cps", "TimErweten.txt", "code.dat");
    Decodeer(const char * van, const char * naar, const char * codeBestand) {
        
        Bincode bincode(codeBestand);
        BinaireTrie huffmanTrie(bincode);
       
        /*ibitstream input(van);
        while(!input.fail()) {
            std::cout << input.leesbit();
        }
        input.close();*/



    }

private:
};