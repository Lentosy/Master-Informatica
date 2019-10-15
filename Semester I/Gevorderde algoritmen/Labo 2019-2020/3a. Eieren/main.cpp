#include "eieren.h"
#include <iostream>


int main(void){
    Eieren eieren(20, 36);
    std::cout << "De goedkoopste oplossing bestaat uit " << eieren.geefGoedkoopsteOplossing()  << " pogingen.\n";  
    Boom<int, int> boom = eieren.geefBoom();
    boom.teken("eieren.dot");

    return 0;
}