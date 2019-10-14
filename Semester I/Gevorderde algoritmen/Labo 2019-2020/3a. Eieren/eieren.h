#ifndef __EIEREN_H__
#define __EIEREN_H__
#include <vector>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>

void printMatrix(std::vector<std::vector<int>>& matrix){
    std::cout << std::setw(7) << "";
    for(int i = 0; i < matrix[0].size(); i++){
        std::cout << std::setw(3) << i + 1;
    }
    std::cout << "\n";
    std::cout << std::setw(7) << "";
    
    for(int i = 0; i < matrix[0].size(); i++){
        std::cout << std::setw(3) << "---";
    }
    std::cout << "\n";
    
    for(int i = 0; i < matrix.size(); i++){
        std::cout << std::setw(4) <<  i + 1 << " | ";
        for(int j = 0; j < matrix[i].size(); j++){
            std::cout << std::setw(3) << matrix[i][j];
        }
        std::cout << "\n";
    }
}


class Eieren {
    public:
        Eieren(int e, int v) : eGezocht{e}, vGezocht{v + 1} {};
        int geefGoedkoopsteOplossing() const;
    private:
        int eGezocht; // aantal eieren
        int vGezocht; // aantal verdiepingen
};

int Eieren::geefGoedkoopsteOplossing() const {
    std::vector<std::vector<int>> kostTabel(this->vGezocht, std::vector<int>(this->eGezocht));
    
    // Initialisatie rij
    for(int e = 0; e < this->eGezocht; e++){
        kostTabel[0][e] = 1;
    }
    
    // Initialisatie kolom
    for(int v = 0; v < this->vGezocht; v++){
        kostTabel[v][0] = v;
    }

    for(int e = 1; e < this->eGezocht; e++){
        for(int v = 1; v < this->vGezocht; v++){
            int besteDiepte = INT_MAX;
            for(int w = 1; w < v; w++){
                //std::cout << e << " - " << v << " - " << w << " \n";
                int diepte = std::max(kostTabel[w - 1][e-1], kostTabel[v - w][e]);
                if(diepte < besteDiepte){
                    besteDiepte = diepte;
                }
            }
            kostTabel[v][e] = besteDiepte;
        }
    }

    printMatrix(kostTabel);
    return kostTabel[this->vGezocht - 1][this->eGezocht - 1];
}


#endif