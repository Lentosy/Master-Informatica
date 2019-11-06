#include "stroomnet.h"
#include "pad.h"
#include <vector>
#include <set>
#include <algorithm>
template<class T>
class Stroomnetwerk;


typedef std::map<int, int> Burenlijst;


/**********************************************************************
   Class:Vergrotendpadzoeker
   
   beschrijving: Methodeklasse die, gegeven een stroomnetwerk,
                 een vergrotend pad teruggeeft.
                 Vermits ze hoort bij Ford-Fulkerson zal een object van deze klasse
                 elke keer een ander pad geven als het stroomnetwerk opgegeven
                 in de constructor verandert.
***************************************************************************/
template <class T>
class Vergrotendpadzoeker {
public:
    Vergrotendpadzoeker(const Stroomnetwerk<T>& stroomnetwerk):
                    stroomnetwerk(stroomnetwerk), producent(stroomnetwerk.van), verbruiker(stroomnetwerk.naar),
                    ouder(stroomnetwerk.aantalKnopen()), ontdekt(stroomnetwerk.aantalKnopen(),false){};
    Pad<T> geefVergrotendPad();
protected:
    virtual void zoekVergrotendPad(int huidigeKnoop, int x, Pad<T>& pad);
    const Stroomnetwerk<T>& stroomnetwerk;
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
        T kleinsteCapaciteit = *stroomnetwerk.geefTakdata(pad[0], pad[1]);
        for (int i = 2; i < pad.size(); i++) {
            T huidigeCapaciteit = *stroomnetwerk.geefTakdata(pad[i-1],pad[i]);
            if (huidigeCapaciteit < kleinsteCapaciteit) 
                kleinsteCapaciteit = huidigeCapaciteit;
        }
        pad.zetCapaciteit(kleinsteCapaciteit);
    }
    
    return pad;
}

template <class T>
void Vergrotendpadzoeker<T>::zoekVergrotendPad(int huidigeKnoop, int x, Pad<T>& pad){
    ontdekt[huidigeKnoop] = true;
    const typename GraafMetTakdata<GERICHT,T>::Burenlijst& buren = stroomnetwerk[huidigeKnoop];
    int padLengte = x + 1;
    for (typename GraafMetTakdata<GERICHT,T>::Burenlijst::const_iterator it = buren.begin(); it != buren.end() ; it++){
        int buurKnoop = it->first;
        if (*stroomnetwerk.geefTakdata(huidigeKnoop, buurKnoop) > 0){
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
class Korstepadzoeker : public Vergrotendpadzoeker<T>{
public:
    using Vergrotendpadzoeker::Vergrotendpadzoeker;
protected:
    void zoekVergrotendPad(int huidigeKnoop, int x, Pad<T>& pad);
};



template <class T>
void Korstepadzoeker<T>::zoekVergrotendPad(int huidigeKnoop, int x, Pad<T>& pad) {
    // Breedte eerst zoeken
    ontdekt[huidigeKnoop] = true;
    Burenlijst buren = this->stroomnetwerk[huidigeKnoop];
    Burenlijst::const_iterator burenIterator = buren.begin();
    while(burenIterator != buren.end() && burenIterator->first != this->verbruiker) {
        int buurKnoop = burenIterator->first;
        if (*stroomnetwerk.geefTakdata(huidigeKnoop, buurKnoop) > 0){
            if(!ontdekt[buurKnoop]) {
                ouder[buurKnoop] = huidigeKnoop;
                zoekVergrotendPad(buurKnoop, x, pad);
            }
        }
        burenIterator++;
    }

    int padKnoop = verbruiker;
    while(ouder[padKnoop] != producent) {
        pad.push_back(padKnoop);
        padKnoop = ouder[padKnoop];
    }

    pad.push_back(producent);
    std::reverse(pad.begin(), pad.end());
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

}