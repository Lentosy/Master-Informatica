#ifndef __EIEREN_H__
#define __EIEREN_H__
#include <vector>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include "zoekboom17.cpp"

void printMatrix(std::vector<std::vector<int>>& matrix){
    std::cout << std::setw(7) << "";
    for(int i = 0; i < matrix[0].size(); i++){
        std::cout << std::setw(3) << i;
    }
    std::cout << "\n";
    std::cout << std::setw(7) << "";
    
    for(int i = 0; i < matrix[0].size(); i++){
        std::cout << std::setw(3) << "---";
    }
    std::cout << "\n";
    
    for(int i = 0; i < matrix.size(); i++){
        std::cout << std::setw(4) <<  i << " | ";
        for(int j = 0; j < matrix[i].size(); j++){
            std::cout << std::setw(3) << matrix[i][j];
        }
        std::cout << "\n";
    }
}


class Eieren {
    public:
        Eieren(int e, int v) : eGezocht{e}, vGezocht{v} {};
        int geefGoedkoopsteOplossing() const;
    private:
        int eGezocht; // aantal eieren
        int vGezocht; // aantal verdiepingen
};

int Eieren::geefGoedkoopsteOplossing() const {
    std::vector<std::vector<int>> kostTabel(this->vGezocht + 1, std::vector<int>(this->eGezocht + 1));
    std::vector<std::vector<int>> wortelTabel(this->vGezocht + 1, std::vector<int>(this->eGezocht + 1));
    


    // Basisgeval: voor verdieping 0 zijn er geen pogingen nodig, voor verdieping 1 is er 1 poging nodig.
    for(int e = 1; e <= this->eGezocht; e++){
        kostTabel[0][e] = 0;
        kostTabel[1][e] = 1;
        wortelTabel[0][e] = 0;
        wortelTabel[1][e] = 1;
    }
    
    // Basisgeval: bij 1 ei is het aantal pogingen gelijk aan het aantal verdiepingen
    for(int v = 1; v <= this->vGezocht; v++){
        kostTabel[v][1] = v;
        wortelTabel[v][1] = v;
    }

    
    for(int e = 2; e <= this->eGezocht; e++){
        for(int v = 2; v <= this->vGezocht; v++){
            kostTabel[v][e] = INT_MAX;
            // Maak elke verdieping telkens tot wortel, en kies de beste hieruit
            for(int w = 1; w <= v; w++){
                int diepteGebroken = kostTabel[w - 1][e - 1]; // Beste diepte van de linkerdeelboom
                int diepteNietGebroken = kostTabel[v - w][e]; // Beste diepte van de rechterdeelboom
                int diepte = 1 + std::max(diepteGebroken, diepteNietGebroken);
                if(diepte < kostTabel[v][e]){
                    kostTabel[v][e] = diepte;
                    wortelTabel[v][e] = w;
                }        
            }
        }
    }

    printMatrix(kostTabel);
    std::cout << "\n";
    printMatrix(wortelTabel);
    Boom<int, int> oplossingBoom;

    int v = this->vGezocht;
    int e = this->eGezocht;
    int wortel = wortelTabel[v][e];
    oplossingBoom.voegtoe(wortel, 0);

    oplossingBoom.teken("eieren.dot");
    return kostTabel[this->vGezocht][this->eGezocht];
}


#endif