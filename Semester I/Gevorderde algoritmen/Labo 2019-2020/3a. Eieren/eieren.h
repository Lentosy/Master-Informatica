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
        Eieren(int e, int v) : eGezocht{e}, vGezocht{v}, kostTabel{this->vGezocht + 1, std::vector<int>(this->eGezocht + 1)}, wortelTabel{this->vGezocht + 1, std::vector<int>(this->eGezocht + 1)} {
            berekenTabellen();
        };
        int geefGoedkoopsteOplossing() const;
        Boom<int, int> geefBoom() const;
    private:
        int eGezocht; // aantal eieren
        int vGezocht; // aantal verdiepingen
        std::vector<std::vector<int>> kostTabel;
        std::vector<std::vector<int>> wortelTabel;
        void berekenTabellen();
        void maakDeelbomen(Boom<int, int>& wortel, int huidigAantalEieren, int aantalVerdiepingenLinks, int aantalVerdiepingenRechts) const;
};

void Eieren::berekenTabellen() {
  // Basisgeval: voor verdieping 0 zijn er geen pogingen nodig, voor verdieping 1 is er 1 poging nodig.
    for(int e = 1; e <= this->eGezocht; e++){
        this->kostTabel[0][e] = 0;
        this->kostTabel[1][e] = 1;
        this->wortelTabel[0][e] = 0;
        this->wortelTabel[1][e] = 1;
    }
    
    // Basisgeval: bij 1 ei is het aantal pogingen gelijk aan het aantal verdiepingen
    for(int v = 1; v <= this->vGezocht; v++){
        this->kostTabel[v][1] = v;
        this->wortelTabel[v][1] = v;
    }

    
    for(int e = 2; e <= this->eGezocht; e++){
        for(int v = 2; v <= this->vGezocht; v++){
            kostTabel[v][e] = INT_MAX;
            // Maak elke verdieping telkens tot wortel, en kies de beste hieruit
            for(int w = 1; w <= v; w++){
                int diepteGebroken = kostTabel[w - 1][e - 1]; // Beste diepte van de linkerdeelboom
                int diepteNietGebroken = kostTabel[v - w][e]; // Beste diepte van de rechterdeelboom
                int diepte = 1 + std::max(diepteGebroken, diepteNietGebroken); // We willen het slechtste geval berekenen, dus het maximum van de twee
                if(diepte < kostTabel[v][e]){
                    this->kostTabel[v][e] = diepte;
                    this->wortelTabel[v][e] =  w;
                }        
            }
        }
    }

    printMatrix(this->kostTabel);
    std::cout << "\n";
    printMatrix(this->wortelTabel);
}


int Eieren::geefGoedkoopsteOplossing() const {
    return this->kostTabel[this->vGezocht][this->eGezocht];
}


Boom<int, int> Eieren::geefBoom() const {
    Boom<int, int> boom;

    int wortel = this->wortelTabel[this->vGezocht][this->eGezocht];
    boom.voegtoe(wortel, 0);
    
    maakDeelbomen(boom, this->eGezocht, wortel - 1, this->vGezocht - wortel);

  //  assert(boom.geefDiepte() == this->geefGoedkoopsteOplossing());
    return boom;
}


void Eieren::maakDeelbomen(Boom<int, int>& wortel, int huidigAantalEieren, int aantalVerdiepingenLinks, int aantalVerdiepingenRechts) const {
    if(aantalVerdiepingenLinks <= 0){
        // dus een blad
        return;
    }

    if(aantalVerdiepingenRechts <= 0){
        // dus een blad
        return;
    }
    std::cout << aantalVerdiepingenLinks << " - " << aantalVerdiepingenRechts << "\n";

    // Stel dat het aantal verdiepingen links 3 is, dan zoeken we de beste wortel voor (1, 2, 3) met 1 ei minder
    int wortelLinks = this->wortelTabel[aantalVerdiepingenLinks][huidigAantalEieren - 1];
    (*wortel).links = std::make_unique<Knoop<int, int>>(wortelLinks, 0);
    (*wortel).links->ouder = &(*wortel);
    this->maakDeelbomen((*wortel).links, huidigAantalEieren - 1, wortelLinks - 1, (*wortel).sleutel - wortelLinks - 1);
    
    // Stel dat het aantal verdiepingen rechts 3 is, dan zoeken we de beste wortel voor ('wortel' + 1, 'wortel' + 2, 'wortel' + 3) met hetzelfde aantal eieren.
    // Gelukkig komt dit neer op het zoeken naar de beste wortel voor (1, 2, 3) en daarbij dan 'wortel' bij op te tellen
    int wortelRechts = this->wortelTabel[aantalVerdiepingenRechts][huidigAantalEieren] + (*wortel).sleutel;
    (*wortel).rechts = std::make_unique<Knoop<int, int>>(wortelRechts, 0);
    (*wortel).rechts->ouder = &(*wortel);
    this->maakDeelbomen((*wortel).rechts, huidigAantalEieren, wortelRechts - (*wortel).sleutel - 1, this->vGezocht - wortelRechts);

}

#endif