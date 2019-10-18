#include <vector>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include "zoekboom17.cpp"
#include "eieren.h"

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
}


int Eieren::geefGoedkoopsteOplossing() const {
    return this->kostTabel[this->vGezocht][this->eGezocht] - 1;
}


/*
* Construeert de strategieboom die toegepast kan worden met het opgegeven aantal eieren en verdiepingen.
*/
Boom<int, int> Eieren::geefBoom() const {
    Boom<int, int> strategieBoom;
    int wortel = this->wortelTabel[this->vGezocht][this->eGezocht];
    strategieBoom.voegtoe(wortel, 0);
    
    maakDeelbomen(strategieBoom, this->eGezocht, std::make_pair(1, wortel - 1), std::make_pair(wortel + 1, this->vGezocht));

    assert(strategieBoom.geefDiepte() == this->geefGoedkoopsteOplossing());
    return strategieBoom;
}

/*
* Deze methode maakt de knopen van de twee deelbomen van een wortel aan. De std::pair instanties bereikLinks en bereikRechts geven het bereik van verdiepingen aan waarvoor
* de wortel in de specifieke deelboom optimaal moet zijn.
*/
void Eieren::maakDeelbomen(Boom<int, int>& wortel, int huidigAantalEieren, std::pair<int, int>& bereikLinks, std::pair<int, int>& bereikRechts) const {

    /* Het bereik moet nuttig zijn, de verdieping in het begin van het bereik moet kleiner of gelijk zijn aan de verdieping op het einde van het bereik
        [1 - 7] is geldig
        [4 - 4] is geldig
        [9 - 8] is niet geldig alhoewel dit het equivalent kan zijn van [8 - 9], maar dit werd dan al eerder bepaald
    */
    if(bereikLinks.first > bereikLinks.second || bereikRechts.first > bereikRechts.second){
        return;
    }

    /* De wortel zoeken voor het bereik van verdiepingen [3 - 7] is equivalent met het opzoeken van de beste wortel voor het bereik [1 - 4], en daar dan 2 bij op te tellen,     want om van 3 naar 1 te gaan moet er 2 afgetrokken worden.
       Als het bereik al begint vanaf 1, is de offset gelijk aan 0
       Als het bereik begint vanaf een getal groter dan 1, is de offset gelijk aan dat getal - 1 
    */
    int linksOffset  = (bereikLinks.first  == 1 ) ? 0 : bereikLinks.first  - 1;
    int rechtsOffset = (bereikRechts.first == 1 ) ? 0 : bereikRechts.first - 1;


    /* De wortels kunnen nu gewoon opgezocht worden, eventueel met de offset bij te tellen */
    int linksWortel  = this->wortelTabel[bereikLinks.second  - linksOffset ][huidigAantalEieren - 1] + linksOffset;
    int rechtsWortel = this->wortelTabel[bereikRechts.second - rechtsOffset][huidigAantalEieren    ] + rechtsOffset;

    /* De knopen worden handmatig aangemaakt en niet met de toevoegfunctie, omdat we specifiek willen controleren wat er in de linker en rechter knoop komt te staan */
    (*wortel).links  = std::make_unique<Knoop<int, int>>(linksWortel , 0);
    (*wortel).rechts = std::make_unique<Knoop<int, int>>(rechtsWortel, 0);

    /* Nu kan hetzelfde toegepast worden op de linker- en rechterwortel, met aangepaste bereiken, en in de linkerdeelboom een ei minder*/
    /* Stel dat het oorspronkelijke bereik voor een linkerdeelboom 'a' [1 - 7] was, en de wortel is 4 
    *  Voor deze 'a' zijn er nu twee nieuwe deelbomen, waarvan het linkerbereik [1 - 3] is  en het rechterbereik [5 - 7]
    *  Dezelfde redenering kan toegepast worden op de rechterdeelboom, maar dan met hetzelfde aantal eieren
    * */
    this->maakDeelbomen((*wortel).links, huidigAantalEieren - 1, std::make_pair(bereikLinks.first , linksWortel - 1) , std::make_pair(linksWortel + 1, bereikLinks.second));
    this->maakDeelbomen((*wortel).rechts, huidigAantalEieren, std::make_pair(bereikRechts.first, rechtsWortel - 1), std::make_pair(rechtsWortel + 1, bereikRechts.second));
}
