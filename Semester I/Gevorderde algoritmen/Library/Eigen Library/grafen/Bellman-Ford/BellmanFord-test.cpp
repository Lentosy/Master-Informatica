
#include "BellmanFord.h"



int main(void) {
    GraafMetTakdata<GERICHT, int> graaf;
    int A = graaf.voegKnoopToe();
    int B = graaf.voegKnoopToe();
    int C = graaf.voegKnoopToe();
    int D = graaf.voegKnoopToe();
    int E = graaf.voegKnoopToe();

    graaf.voegVerbindingToe(A, B, -1);
    graaf.voegVerbindingToe(A, C, 4);
    graaf.voegVerbindingToe(B, C, 3);
    graaf.voegVerbindingToe(B, E, 2);
    graaf.voegVerbindingToe(B, D, 2);
    graaf.voegVerbindingToe(D, B, 1);
    graaf.voegVerbindingToe(D, C, 5);
    graaf.voegVerbindingToe(E, D, -3);


    BellmanFord<int> bf(&graaf);
    std::vector<int> afstanden = bf.geefKortsteAfstanden(A);
    for(int i = 0; i < afstanden.size(); i++){
        std::cout << "Afstand van knoop A naar knoop " << (char)(i + 'A')  << ": " << afstanden[i] << "\n";
    }

}