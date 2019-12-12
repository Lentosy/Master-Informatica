#include "ShiftAnd.h"
#include <iostream>


int main(void){
    ShiftAnd sa("naald");
    ZoekInformatie zoekInformatie;
    
    std::queue<int> posities = sa.zoek("de naald in de hooiberg. De naalt in de hooiberg. De napald in de hooiberg.", zoekInformatie, SHIFTAND_INLASSING | SHIFTAND_VERVANGING | SHIFTAND_VERWIJDERING);
    while(!posities.empty()){
        int pos = posities.front();
        posities.pop();
        std::cout << pos << "\n";
    } 

}