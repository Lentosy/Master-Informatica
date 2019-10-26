#include <iostream>
#include <cmath>
#include <algorithm>
#include "prquadtree.cpp"
#include "csv.h"

const double PI = 3.1415926;

void testSpiraal(){
    int maxElements = 16;
    int i = 1;
    while(i < maxElements){
        i *= 2;

        int maxcoordinaat = std::ceil(std::max(5* i * std::cos(i*0.25*PI), 5*i * std::sin(i*0.25*PI)));
        PRQuadtree boom(maxcoordinaat);
        for(int j = 1; j <= i; j++){
            int x = 5*j * std::cos(j*0.25*PI);
            int y = 5*j * std::sin(j*0.25*PI);
            boom.voegToe(x, y);
        }

        std::cout << "Diepte voor " << i << " elementen : " << boom.geefDiepte() << "\n";
    }
}

int main(void){
    
    PRQuadtree boom(10);
    boom.voegToe(7, 6);
    boom.voegToe(5, 4);
    boom.voegToe(-1, -1);    
    std::ofstream bestand("boom.dot");
    bestand << boom.dotCode().str();
    system("dot -Tpng boom.dot -o boom.jpg");
    return 0;

}


