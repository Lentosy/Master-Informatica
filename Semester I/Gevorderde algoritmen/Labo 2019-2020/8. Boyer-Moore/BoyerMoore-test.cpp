
#include "BoyerMoore.h"
#include <iostream>

int main(void) {
    BoyerMoore bm("GCAGAGCAG");
    ZoekInformatie zoekInformatie;
    std::queue<int> resultaten = bm.zoek("GCAGAGCAGAGCAGAGCAGAGCAGAGCAGAGCAGAGCAG", zoekInformatie);
    std::cout << resultaten.size() << " keer gevonden\n";

    bm.printTabellen(std::cout);
}