#include "ZoekAlgoritme.h"
#include <cmath>
#include <iostream>

class KarpRabin : public ZoekAlgoritme {
public:
    KarpRabin(const std::string& patroon, int r, int d);
    std::queue<int> zoek(const std::string& tekst, ZoekInformatie& zoekInformatie) const;
private:
    int r;
    int d;
    int patroonFingerprint;
    int geefFingerprint(const std::string& s) const;
    bool controleerGelijkheid(const std::string& tekst, int i) const;
};

bool KarpRabin::controleerGelijkheid(const std::string& tekst, int i) const {
    int j = 0;
    while(j < patroon.size() && patroon[j] == tekst[j + i]){
        j++;
    }
    return j == patroon.size();
}

int KarpRabin::geefFingerprint(const std::string& s) const {
    int waarde = 0;
    for(int i = 0; i < patroon.size(); i++) {
                    //  (P[i] * d^{p - i - 1}) mod r
        waarde += (((int)s[i]) * (int)std::pow(d, patroon.size() - i - 1)) % r;
    }
    waarde %= r;
    return waarde;
}

KarpRabin::KarpRabin(const std::string& patroon, int r, int d) : ZoekAlgoritme(patroon), r{r}, d{d} {
    patroonFingerprint = geefFingerprint(patroon);
}

std::queue<int> KarpRabin::zoek(const std::string& tekst, ZoekInformatie& zoekInformatie) const {
    std::queue<int> posities;
    int tekstFingerprint = geefFingerprint(tekst);

    // kan zijn dat er al direct een match is
    if(patroonFingerprint == tekstFingerprint && controleerGelijkheid(tekst, 0)){
        posities.push(0);
    }

    int c1 = r*(d - 1);
    int c2 = 1;
    for(int i = 0; i < patroon.size() - 1; i++){
        c2 = (c2 * d) % r;
    }
    
    for(int i = 1; i < tekst.size() - patroon.size(); i++){
        tekstFingerprint = (((tekstFingerprint + c1 - tekst[i] * c2) %r ) * d + tekst[i + patroon.size()]) % r;
        if(patroonFingerprint == tekstFingerprint && controleerGelijkheid(tekst, i)){
            posities.push(i);
        }   
    }

    return posities;
}