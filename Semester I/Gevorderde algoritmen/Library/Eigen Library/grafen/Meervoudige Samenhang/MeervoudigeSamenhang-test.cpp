#include "../graaf.h"
#include "MeervoudigeSamenhang.h"


int main(void){
    Graaf<ONGERICHT> graaf(6);

    graaf.voegVerbindingToe(0,1);
    graaf.voegVerbindingToe(1,2);
    graaf.voegVerbindingToe(2,3);
    graaf.voegVerbindingToe(3,4);
    graaf.voegVerbindingToe(4,5);
    graaf.voegVerbindingToe(5,0);
    
    graaf.voegVerbindingToe(0, 2);
    graaf.voegVerbindingToe(3, 5);
    

    MeervoudigeSamenhang mvsh(&graaf);
    std::cout << mvsh.bepaalGraad() << "\n";


    Graaf<ONGERICHT> graaf2(6);

    graaf2.voegVerbindingToe(0,1);
    graaf2.voegVerbindingToe(1,2);
    graaf2.voegVerbindingToe(2,3);
    graaf2.voegVerbindingToe(3,4);
    graaf2.voegVerbindingToe(4,5);
    graaf2.voegVerbindingToe(5,0);
    
    graaf2.voegVerbindingToe(0, 2);
    graaf2.voegVerbindingToe(0, 4);
    graaf2.voegVerbindingToe(1, 3);
    graaf2.voegVerbindingToe(1, 5);
    graaf2.voegVerbindingToe(2, 4);
    graaf2.voegVerbindingToe(3, 5);
    
    MeervoudigeSamenhang mvsh2(&graaf2);
    std::cout << mvsh2.bepaalGraad() << "\n";

    
}