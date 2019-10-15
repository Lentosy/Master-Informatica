#include "eieren.h"
#include <iostream>


int main(void){
    Eieren eieren(2, 5);
    std::cout << "De goedkoopste oplossing bestaat uit " << eieren.geefGoedkoopsteOplossing()  << " pogingen.\n";  
    Boom<int, int> boom = eieren.geefBoom();
    boom.teken("eieren.dot");
    boom.schrijf(std::cout);
    return 0;
}