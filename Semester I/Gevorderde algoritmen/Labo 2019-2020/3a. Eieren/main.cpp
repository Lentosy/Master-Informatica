#include "eieren.h"
#include <iostream>


int main(void){
    Eieren eieren(8, 15);
    std::cout << eieren.geefGoedkoopsteOplossing();

    return 0;
}