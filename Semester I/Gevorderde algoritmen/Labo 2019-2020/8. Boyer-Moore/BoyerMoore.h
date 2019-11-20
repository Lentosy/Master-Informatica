#pragma once
#include "ZoekAlgoritme.h"
#include "PrefixFunctie.h"


/**********************************************************************

   Class: BoyerMoore

   beschrijving: 

***************************************************************************/

class BoyerMoore : public ZoekAlgoritme {
public:

    using ZoekAlgoritme::ZoekAlgoritme;
    std::queue<int> zoek(const std::string& tekst, ZoekInformatie& zoekInformatie) const {
        std::queue<int> posities;
        return posities;
    }

};


