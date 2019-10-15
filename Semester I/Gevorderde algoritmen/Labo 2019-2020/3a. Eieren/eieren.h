#ifndef __EIEREN_H__
#define __EIEREN_H__
#include <vector>
#include "zoekboom17.h"


class Eieren {
    public:
        Eieren(int e, int v) : eGezocht{e}, vGezocht{v}, kostTabel{this->vGezocht + 1, std::vector<int>(this->eGezocht + 1)}, wortelTabel{this->vGezocht + 1, std::vector<int>(this->eGezocht + 1)} {
            berekenTabellen();
        };
        int geefGoedkoopsteOplossing() const;
        /*
        * Construeert de strategieboom die toegepast kan worden met het opgegeven aantal eieren en verdiepingen.
        */
        Boom<int, int> geefBoom() const;
    private:
        int eGezocht; // aantal eieren
        int vGezocht; // aantal verdiepingen
        std::vector<std::vector<int>> kostTabel;
        std::vector<std::vector<int>> wortelTabel;
        /*
        * Lost het probleem op en steekt de optimale wortels in de worteltabel
        */
        void berekenTabellen();
        /*
        * Deze methode maakt de knopen van de twee deelbomen van een wortel aan. De std::pair instanties bereikLinks en bereikRechts geven het bereik van verdiepingen aan waarvoor
        * de wortel in de specifieke deelboom optimaal moet zijn.
        */
        void maakDeelbomen(Boom<int, int>& wortel, int huidigAantalEieren, std::pair<int, int>& bereikLinks, std::pair<int, int>& bereikRechts) const;
};

#endif