
#include "Johnson.h"



int main(void) {
    GraafMetTakdata<GERICHT, int> graaf;
    int w = graaf.voegKnoopToe();
    int x = graaf.voegKnoopToe();
    int y = graaf.voegKnoopToe();
    int z = graaf.voegKnoopToe();

    graaf.voegVerbindingToe(w, z, 2);
    graaf.voegVerbindingToe(z, y, -3);
    graaf.voegVerbindingToe(y, w, 4);

    graaf.voegVerbindingToe(z, x, -7);
    
    graaf.voegVerbindingToe(y, z, 5);
    
    graaf.voegVerbindingToe(x, w, 6);
    graaf.voegVerbindingToe(x, y, 3);

    Johnson<int> johnson(&graaf);
    std::vector<std::vector<int>> afstanden = johnson.geefKortsteAfstanden();
   /* for(int i = 0; i < afstanden.size(); i++){
        std::cout << "Afstand van knoop A naar knoop " << (char)(i + 'A')  << ": " << afstanden[i] << "\n";
    }*/

}