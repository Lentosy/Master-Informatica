#include "eieren.cpp"
#include <iostream>


int main(int argc, char* argv[]){
    if(argc != 3){
        std::cerr << "Geef het aantal eieren en het aantal verdiepingen op\n";
        exit(1);
    }
    int e = std::stoi(argv[1]);
    int v = std::stoi(argv[2]);
    Eieren eieren(e, v); 
    Boom<int, int> boom = eieren.geefBoom();
    boom.teken("dot/eieren.dot");
    system("dot -Tpng dot/eieren.dot -o dot/eieren.jpg");
    
    std::cout << "De goedkoopste oplossing voor " << e << " eieren en " << v << " verdiepingen bestaat uit " << eieren.geefGoedkoopsteOplossing()  << " pogingen.\n"; 
    return 0;
}