#include "eieren.h"
#include <iostream>


int main(void){
    Eieren eieren(20, 36);
    std::cout << eieren.geefGoedkoopsteOplossing();

    return 0;
}