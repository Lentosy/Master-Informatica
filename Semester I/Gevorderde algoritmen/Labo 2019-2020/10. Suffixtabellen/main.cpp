#include "sais.h"
#include <iostream>
#include <string>
#include <iomanip>
int main(void){
    //std::string T("hottentottent");
    std::string T("GCAGAGCAG");
    SAIS suffixarray((unsigned char *)T.c_str(), T.size());

    suffixarray.print(std::cout, T);

    int verschuiving, lengte;
    suffixarray.besteVerwijzing(verschuiving, lengte, 12);
    std::cout << "\n\n(" << verschuiving << ", " << lengte << ")";
}