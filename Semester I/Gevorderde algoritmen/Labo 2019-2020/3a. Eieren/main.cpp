#include "eieren.cpp"
#include <iostream>


int main(void){
    Eieren eieren(2, 5);
    std::cout << "De goedkoopste oplossing bestaat uit " << eieren.geefGoedkoopsteOplossing()  << " pogingen.\n";  
    Boom<int, int> boom = eieren.geefBoom();
    boom.teken("dot/eieren.dot");
    system("dot -Tpng dot/eieren.dot -o dot/eieren.jpg");
    return 0;
}