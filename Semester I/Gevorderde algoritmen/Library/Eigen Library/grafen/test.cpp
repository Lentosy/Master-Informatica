
#include "stroomnet.h"
#include "graaf.h"
#include <iostream>


int main(void) {
    GraafMetTakdata<GERICHT, int> graaf(8);
    
    graaf.voegVerbindingToe(0, 2, 10);
    graaf.voegVerbindingToe(2, 1, 3);
    graaf.voegVerbindingToe(2, 3, 5);
    graaf.voegVerbindingToe(2, 5, 6);
    graaf.voegVerbindingToe(3, 6, 6);
    graaf.voegVerbindingToe(3, 0, 2);
    graaf.voegVerbindingToe(6, 5, 2);
    graaf.voegVerbindingToe(6, 7, 7);

    graaf.voegVerbindingToe(0, 1, 7);
    graaf.voegVerbindingToe(1, 4, 4);
    graaf.voegVerbindingToe(4, 5, 6);
    graaf.voegVerbindingToe(5, 7, 8);

    graaf.voegVerbindingToe(7, 4, 1);


    Stroomnetwerk<int> sn(graaf, 0, 7);
    std::cout << sn.geefStroom().geefCapaciteit();
    sn.teken("graaf.dot");


}