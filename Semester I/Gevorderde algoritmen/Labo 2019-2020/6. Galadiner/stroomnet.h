#ifndef __STROOMNETOPGELOST_H
#define __STROOMNETOPGELOST_H
#include "graaf.h"
#include "pad.h"
#include "vergrotendpadzoeker.h"
#include <cassert>
#include <iostream>
#include <functional>
using std::vector;
using std::function;
using std::ostream;
using std::cerr;

template<class T>
class Vergrotendpadzoeker;


/**********************************************************************

   Class: Stroomnetwerk
   
   beschrijving: Een stroomnetwerk gaat uit van een gewogen gerichte graaf
                 die in de constructor wordt opgegeven
   
***************************************************************************/

template <class T> //T = takdata
class Stroomnetwerk : public GraafMetTakdata<GERICHT, T>{
public:
//leeg netwerk; alleen aantal knopen en van en naar gegeven.
Stroomnetwerk(int grootte, int _van, int _naar);
//Copyconstructor. Let op: Graaf<GERICHT>(gr) moet toegevoegd,
//anders roept de copyconstructor van GraafMetTakdata de defaultconstructor
//van Graaf op en krijgen we een lege graaf.
//Stroomnetwerk(const GraafMetTakdata<GERICHT, T>& gr):
//                    Graaf<GERICHT>(gr),GraafMetTakdata<GERICHT, T>(gr),van(0),naar(1){};
Stroomnetwerk(const GraafMetTakdata<GERICHT, T>& gr, int _van, int _naar);
Stroomnetwerk(const Stroomnetwerk<T>& gr);
Stroomnetwerk(Stroomnetwerk<T>&& gr);

void wijzigVerbinding(int van, int naar, T wijziging);

Stroomnetwerk<T>& operator+=(const Pad<T>& pad);
Stroomnetwerk<T>& operator-=(const Pad<T>& pad);

Stroomnetwerk<T> geefStroom();
T geefCapaciteit();

    int van,naar;
virtual void teken(const char* bestandsnaam) const;
protected:
    virtual std::string knooplabel(int i) const;
};
template <class T>
Stroomnetwerk<T>::Stroomnetwerk(int grootte, int _van, int _naar):
                    Graaf<GERICHT>(grootte), GraafMetTakdata<GERICHT, T>(grootte),van(_van),naar(_naar){}

template <class T>
Stroomnetwerk<T>::Stroomnetwerk(const GraafMetTakdata<GERICHT ,T>& gr,int _van,int _naar):
                    Graaf<GERICHT>(gr), GraafMetTakdata<GERICHT, T>(gr), van(_van), naar(_naar){}

template <class T>
Stroomnetwerk<T>::Stroomnetwerk(const Stroomnetwerk<T>& gr):
                    Graaf<GERICHT>(gr), GraafMetTakdata<GERICHT, T>(gr), van(gr.van), naar(gr.naar){}

template <class T>
Stroomnetwerk<T>::Stroomnetwerk(Stroomnetwerk<T>&& gr):Stroomnetwerk(0,0,0){
    swap(this->burenlijsten,gr.burenlijsten);
    swap(this->vrijgekomenVerbindingsnummers, gr.vrijgekomenVerbindingsnummers);
    std::swap(this->hoogsteVerbindingsnummer, gr.hoogsteVerbindingsnummer);
    swap(this->takdatavector, gr.takdatavector);
    std::swap(this->van, gr.van);
    std::swap(this->naar, gr.naar);
}

template <class T>
Stroomnetwerk<T> Stroomnetwerk<T>::geefStroom(){
    Stroomnetwerk<T> oplossing(this->aantalKnopen(), van, naar);
    Stroomnetwerk<T> restnetwerk(*this);
    Grootstecapaciteitszoeker<T> vg(restnetwerk);
    Pad<T> vergrotendpad = vg.geefVergrotendPad();
    while(vergrotendpad.size() != 0){
        restnetwerk -= vergrotendpad;
        oplossing += vergrotendpad;
        vergrotendpad = vg.geefVergrotendPad();
    }
    return oplossing;
}

template <class T>
void Stroomnetwerk<T>::wijzigVerbinding(int van, int naar, T wijziging) {
    int verbindingsnummer = this->verbindingsnummer(van, naar);
    if(verbindingsnummer == -1) {
        this->voegVerbindingToe(van, naar, wijziging);
    } else {
        this->takdatavector[verbindingsnummer] += wijziging;
    }
}

template <class T>
Stroomnetwerk<T>& Stroomnetwerk<T>::operator+=(const Pad<T>& pad) {
    T capaciteit = pad.geefCapaciteit();
    for(int i = 0; i < pad.size() - 1; i++) {
        this->wijzigVerbinding(pad[i], pad[i + 1], capaciteit);
    }
    return *this;
}

template <class T>
Stroomnetwerk<T>& Stroomnetwerk<T>::operator-=(const Pad<T>& pad) {
    T capaciteit = pad.geefCapaciteit();
    for(int i = 0; i < pad.size() - 1; i++) {
        this->wijzigVerbinding(pad[i], pad[i + 1], -capaciteit);
        this->wijzigVerbinding(pad[i + 1], pad[i],  capaciteit);
    }
    return *this;
}

template <class T>
T Stroomnetwerk<T>::geefCapaciteit(){
    T som = 0;
    typename GraafMetTakdata<GERICHT, T>::Burenlijst::const_iterator burenIterator = this->burenlijsten[van].begin();
    while(burenIterator != this->burenlijsten[van].end()) {
        som += this->takdatavector[burenIterator->second];
        burenIterator++;

    }
    return som;
}

template <class T>
void Stroomnetwerk<T>::teken(const char* bestandsnaam) const{
    std::ofstream uit(bestandsnaam);
    assert(uit);
    std::string pijl;
        uit<<"digraph {\n";
        pijl="->";
    uit<<"{ rank=source; "<<knooplabel(van)<<" }\n";
    uit<<"{ rank=sink; "<<knooplabel(naar)<<" }\n";
    for (int k=0; k<this->aantalKnopen(); k++){
        if (this->burenlijsten[k].empty())
            uit<<knooplabel(k)<<";\n";
        else{
        for (auto& p: this->burenlijsten[k])
                uit<<knooplabel(k)<<" "<<pijl<<" "
                   <<knooplabel(p.first)<<this->taklabel(p.second)<<";\n";
        };
    };
    uit<<"}";
    uit.close();
}

template <class T>
std::string Stroomnetwerk<T>::knooplabel(int i) const{
    std::ostringstream uit;
    if (i==van)
        uit<<'"'<<i<<":P\"";
    else if (i==naar)
        uit<<'"'<<i<<":V\"";
    else
        uit<<i;
    return uit.str();
}

#endif
