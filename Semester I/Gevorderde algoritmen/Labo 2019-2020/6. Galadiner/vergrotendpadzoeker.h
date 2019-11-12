#include "stroomnet.h"
#include "pad.h"
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
template<class T>
class Stroomnetwerk;


typedef std::map<int, int> Burenlijst;


/**********************************************************************
   Class:Vergrotendpadzoeker
   
   beschrijving: Methodeklasse die, gegeven een Stroomnetwerk,
                 een vergrotend pad teruggeeft.
                 Vermits ze hoort bij Ford-Fulkerson zal een object van deze klasse
                 elke keer een ander pad geven als het restnetwerk opgegeven
                 in de constructor verandert.
***************************************************************************/
template <class T>
class Vergrotendpadzoeker {
public:
    Vergrotendpadzoeker(const Stroomnetwerk<T>& restnetwerk):
                    restnetwerk(restnetwerk), producent(restnetwerk.van), verbruiker(restnetwerk.naar),
                    ouder(restnetwerk.aantalKnopen()), ontdekt(restnetwerk.aantalKnopen(),false){};
    Pad<T> geefVergrotendPad();
protected:
    virtual void zoekVergrotendPad(int huidigeKnoop, int x, Pad<T>& pad);
    const Stroomnetwerk<T>& restnetwerk;
    std::vector<int> ouder;
    std::vector<bool> ontdekt;
    int producent, verbruiker;
};


template <class T>
Pad<T> Vergrotendpadzoeker<T>::geefVergrotendPad(){
    for (int i = 0; i < ontdekt.size(); i++){
        ontdekt[i] = false;
    }
    
    Pad<T> pad;
    assert(producent != verbruiker);
    zoekVergrotendPad(producent, 0, pad);
    assert(pad.size() != 1);
    
    // Bepaal het minimum van de capaciteiten
    
    if (pad.size() > 1){
        T kleinsteCapaciteit = *restnetwerk.geefTakdata(pad[0], pad[1]);
        for (int i = 2; i < pad.size(); i++) {
            T huidigeCapaciteit = *restnetwerk.geefTakdata(pad[i-1],pad[i]);
            if (huidigeCapaciteit < kleinsteCapaciteit) 
                kleinsteCapaciteit = huidigeCapaciteit;
        }
        pad.zetCapaciteit(kleinsteCapaciteit);
    }


    // EIGEN GLUE CODE, IF CAPACITEIT VAN EEN PAD 0 IS, IS ER TOCH GEEN PAD
    if(pad.geefCapaciteit() == 0) {
        pad.clear();
    }
    
    return pad;
}

template <class T>
void Vergrotendpadzoeker<T>::zoekVergrotendPad(int huidigeKnoop, int x, Pad<T>& pad){
    ontdekt[huidigeKnoop] = true;
    const typename GraafMetTakdata<GERICHT,T>::Burenlijst& buren = restnetwerk[huidigeKnoop];
    int padLengte = x + 1;
    for (typename GraafMetTakdata<GERICHT,T>::Burenlijst::const_iterator it = buren.begin(); it != buren.end() ; it++){
        int buurKnoop = it->first;
        if (*restnetwerk.geefTakdata(huidigeKnoop, buurKnoop) > 0){
            if (it->first == verbruiker && padLengte + 1 > pad.size()){
                ouder[verbruiker] = huidigeKnoop;
                pad.resize(padLengte + 1);
                int ychf = verbruiker;
                int i = padLengte;
                while (ychf != producent){
                    pad[i--] = ychf;
                    ychf = ouder[ychf];
                }
                pad[0] = ychf;
            }
            else if(buurKnoop != verbruiker && !ontdekt[buurKnoop]){
                ouder[buurKnoop] = huidigeKnoop;
                zoekVergrotendPad(buurKnoop, padLengte, pad);
            }
        }
    }
}




/**********************************************************************
   Class:Korstepadzoeker
   
   beschrijving: Deze geeft een vergrotend pad terug dat zo kort mogelijk is.
***************************************************************************/
template <class T>
class Kortstepadzoeker : public Vergrotendpadzoeker<T>{
public:
    using Vergrotendpadzoeker::Vergrotendpadzoeker;
protected:
    void zoekVergrotendPad(int huidigeKnoop, int x, Pad<T>& pad);
};



template <class T>
void Kortstepadzoeker<T>::zoekVergrotendPad(int huidigeKnoop, int x, Pad<T>& pad) {
    // Breedte eerst zoeken
    // BUG: er worden ook paden aangemaakt waarbij de capaciteit toch nul is. Wordt opgelost door de capaciteit te checken, en het pad te verwijderen als de capaciteit nul is
    std::queue<int> BEqueue; 
    BEqueue.push(huidigeKnoop);
    ontdekt[huidigeKnoop] = true;
    
    while(!BEqueue.empty() && !ontdekt[this->verbruiker]) {
        int knoop = BEqueue.front();
        BEqueue.pop();
        const Burenlijst& buren = this->restnetwerk[knoop];
        Burenlijst::const_iterator burenIterator = buren.begin();

        while(burenIterator != buren.end()) {
            int buur = burenIterator->first; 
            if(!this->ontdekt[buur] && *this->restnetwerk.geefTakdata(knoop, buur) > 0) {
                BEqueue.push(buur);
                this->ouder[buur] = knoop;
                this->ontdekt[buur] = true;
            }           
            burenIterator++; 
        }
    }

    std::stack<int> padKnopen;
    int padKnoop = this->verbruiker;
    while(padKnoop != this->producent) {
        padKnopen.push(padKnoop);
        padKnoop = ouder[padKnoop];
    }
    // producent is nu nog niet toegevoegd aan padKnopen
    pad.push_back(this->producent);
    while(!padKnopen.empty()) {
        pad.push_back(padKnopen.top());
        padKnopen.pop();    
    }
}


/**********************************************************************
   Class: Grootstecapaciteitszoeker
   
   beschrijving: Deze geeft een vergrotend pad met maximale capaciteit. 
***************************************************************************/
template <class T>
class Grootstecapaciteitszoeker : public Vergrotendpadzoeker<T>{
public:
    using Vergrotendpadzoeker::Vergrotendpadzoeker;
protected:
    void zoekVergrotendPad(int huidigeKnoop, int x, Pad<T>& pad);
};


template <class T>
void Grootstecapaciteitszoeker<T>::zoekVergrotendPad(int huidigeKnoop, int x, Pad<T>& pad) {
    std::vector<int> hoogste_cap(this->restnetwerk.aantalKnopen(), INT_MIN); // kost om tot bepaalde knoop te geraken
    hoogste_cap[huidigeKnoop] = 0;

/*Tip: als je voor een gegeven knoop c, M(c) de maximale capaciteit noemt van een pad van de producentknoop naar c dan kan je M zoeken voor alle mogelijke knopen (en dus ook voor de verbruiker) met een methode die zeer goed lijkt op het algoritme van Dijkstra.*/
    std::queue<int> BEqueue;
    BEqueue.push(huidigeKnoop);
    while(!BEqueue.empty()){
        int knoop = BEqueue.front();
        BEqueue.pop();
        const Burenlijst& buren = this->restnetwerk[knoop];
        Burenlijst::const_iterator burenIterator = buren.begin();
        while(burenIterator != buren.end()){
            int buur = burenIterator->first;
            int minCap = std::min(hoogste_cap[knoop] , *this->restnetwerk.geefTakdata(knoop, buur));
            if(hoogste_cap[buur] < minCap){ //enkel (her)pushen indien iets veranderd was aan zijn huidige beste afstand
                ouder[buur] = knoop;
                hoogste_cap[buur] = minCap;
                BEqueue.push(buur);
            }
            burenIterator++;
        }
    }

    std::stack<int> padKnopen;
    int padKnoop = this->verbruiker;
    while(padKnoop != this->producent) {
        padKnopen.push(padKnoop);
        padKnoop = ouder[padKnoop];
    }
    // producent is nu nog niet toegevoegd aan padKnopen
    pad.push_back(this->producent);
    while(!padKnopen.empty()) {
        pad.push_back(padKnopen.top());
        padKnopen.pop();    
    }

}