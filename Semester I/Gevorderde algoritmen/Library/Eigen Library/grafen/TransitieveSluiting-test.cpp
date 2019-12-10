#include "TransitieveSluiting.h"
#include "graaf.h"

int main(void){
    Graaf<GERICHT> graaf(6);

    graaf.voegVerbindingToe(0, 1);
    graaf.voegVerbindingToe(0, 2);
    graaf.voegVerbindingToe(1, 3);
    graaf.voegVerbindingToe(1, 5);
    graaf.voegVerbindingToe(5, 2);
    graaf.voegVerbindingToe(2, 4);
    graaf.voegVerbindingToe(5, 3);
    graaf.voegVerbindingToe(4, 2);

    TransitieveSluiting ts(&graaf);
    ts.bepaalTransitieveSluiting().teken("graaf.dot");

}