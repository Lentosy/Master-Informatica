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
                    l(stroomnetwerk.aantalKnopen()), m(stroomnetwerk.aantalKnopen(),false){};
    Pad<T> geefVergrotendPad();
protected:
    virtual void zoekVergrotendPad(int huidigeKnoop, int x, Pad<T>& pad);
    const Stroomnetwerk<T>& stroomnetwerk;
    std::vector<int> l;
    std::vector<bool> m;
    int producent, verbruiker;
};


template <class T>
Pad<T> Vergrotendpadzoeker<T>::geefVergrotendPad(){
    for (int i = 0; i < m.size(); i++){
        m[i] = false;
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
    m[huidigeKnoop] = true;
    const typename GraafMetTakdata<GERICHT,T>::Burenlijst& buren = stroomnetwerk[huidigeKnoop];
    int padLengte = x + 1;
    for (typename GraafMetTakdata<GERICHT,T>::Burenlijst::const_iterator it = buren.begin(); it != buren.end() ; it++){
        int buurKnoop = it->first;
        if (*stroomnetwerk.geefTakdata(huidigeKnoop, buurKnoop) > 0){
            if (it->first == verbruiker && padLengte + 1 > pad.size()){
                l[verbruiker] = huidigeKnoop;
                pad.resize(padLengte + 1);
                int ychf = verbruiker;
                int i = padLengte;
                while (ychf != producent){
                    pad[i--] = ychf;
                    ychf = l[ychf];
                }
                pad[0] = ychf;
            }
            else if(buurKnoop != verbruiker && !m[buurKnoop]){
                l[buurKnoop] = huidigeKnoop;
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
    std::cout << "DIJKBOY\n";
    // basically dijkstra
    std::vector<int> afstanden(this->stroomnetwerk.aantalKnopen(), INT_MAX);
    std::vector<int> ouder(this->stroomnetwerk.aantalKnopen(), -1);
    afstanden[huidigeKnoop] = 0;
    std::set<int> knopenVerzameling;

    for(int i = 0; i < this->stroomnetwerk.aantalKnopen(); i++){
        knopenVerzameling.emplace(i);
    }

    while(!knopenVerzameling.empty()) {

        int kortste = *std::min_element(knopenVerzameling.begin(), knopenVerzameling.end());
        knopenVerzameling.erase(kortste);

        Burenlijst buren = this->stroomnetwerk[kortste];
        Burenlijst::const_iterator burenIterator = buren.begin();
        while(burenIterator !=  buren.end()) {
            int buur = burenIterator->first;
            int lengte = afstanden[kortste] + 1;
            if(lengte < afstanden[buur]) {
                afstanden[buur] = lengte;
                ouder[buur] = kortste;
            }
            burenIterator++;
        }
    }

    int knoop = verbruiker;
    if(ouder[knoop] || knoop == producent) {
        while(knoop) {
            pad.push_back(knoop);
            knoop = ouder[knoop];
        }
    }

    for(int i = 0; i < pad.size(); i++){
        std::cout << pad[i] << "\n";
    }

}