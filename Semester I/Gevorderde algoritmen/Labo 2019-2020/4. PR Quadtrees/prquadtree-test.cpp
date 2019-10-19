#include <iostream>
#include "prquadtree.cpp"
#include "csv.h"

void schrijftest() {
    PRQuadtree boom(10);
    std::cout << "\n\n---------------------\n\n";
    boom.schrijf(std::cout);
    std::cout << "\n\n---------------------\n\n";
    std::cout << "Voeg het punt (1, 4) toe:\n\n";
    boom.voegToe(1, 4);
    boom.schrijf(std::cout);
    std::cout << "\n\n---------------------\n\n";
    std::cout << "Voeg het punt (-1, 4) toe:\n\n";
    boom.voegToe(-1, 4);
    boom.schrijf(std::cout);
    std::cout << "\n\n---------------------\n\n";
    std::cout << "Voeg het punt (-3, 2) toe:\n\n";
    boom.voegToe(-3, 2);
    boom.schrijf(std::cout);
    std::cout << "\n\n---------------------\n\n";
}

int main(void){
    PRQuadtree boom(10);
    
    boom.voegToe(1, 4);
    boom.voegToe(-1, 4);
    boom.voegToe(-3, 2);
    std::cout << boom.geefDiepte();


    return 0;

}


