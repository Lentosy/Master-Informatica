#include "saisclass.h"
#include <vector>
#include <iomanip>


/**********************************************************************

   Class: SAIS
   
   beschrijving: SAIS wordt de _S_uffix _A_rray d.m.v. _I_nduced _S_orting
   van de string T van lengte len gegeven in de constructor.
   
***************************************************************************/
class SAIS : public std::vector<int>{
public:
    SAIS(const unsigned char* T, int len) : vector<int>(len), LCPtabel(len){
        saisxx_private::saisxx(T, begin(), len);

        std::vector<int>& SA = *this; // voor eenvoudigere notatie

        // Eerst wordt de LGPtabel geconstrueerd. Deze wordt daarna omgevormd naar de LCPtabel
        std::vector<int> LGPtabel(SA.size());

        // Geinverteerde suffixtabel bijhouden, om gemakkelijk 'j' op te sporen
        std::vector<int> invertedSA(SA.size());
        for(int i = 0; i < invertedSA.size(); i++){
            invertedSA[SA[i]] = i;
        }

        int l = 0;
        for(int i = 0; i < SA.size(); i++) {
            int j = invertedSA[i];
            
            int opvolger = SA[j + 1];
            if(j + 1 < len){  

                while(T[i + l] == T[opvolger + l])
                    l++;

                LGPtabel[i] = l;
                std::cout << i << ", " << j << ", " << opvolger << ", " << l << "\n";

                if(l > 0) //staart(suff_i) = suff_(i + 1), dus prefix van lengte l - 1 gemeenschappelijk
                    l-= 1; // staartprincipe: volgende suffix heeft minimum lengte l - 1
            
            }
        }


        std::cout << "\n" << std::setw(10) << std::left << "LGP[i]" << std::setw(3) << "|";
        for(int i = 0; i < SA.size(); i++){
            std::cout << std::setw(3) << LGPtabel[i];
        
            this->LCPtabel[i] = LGPtabel[SA[i]];
        }
    };


    void besteVerwijzing(int& verschuiving, int& lengte, int lokatie) {
        int positie = this->operator[](lokatie);

    }

    void print(std::ostream& os, std::string& T) const {
        os << "\n" << std::setw(10) << std::left << "i" << std::setw(3) << "|";
        for(int i = 0; i < this->size(); i++) {
            os << std::setw(3) << i;
        }
        os << "\n" << std::setw(10) << std::left << "T[i]" << std::setw(3) << "|";
        for(int i = 0; i < T.size(); i++){
            os << std::setw(3) << T[i];
        }
        os << "\n" << std::setw(10) << std::left << "--------" << std::setw(3) << "|";
        for(int i = 0; i < this->size(); i++) {
            os  << "---";
        }
        
        os << "\n" << std::setw(10) << std::left << "SA[i]" << std::setw(3) << "|";
        for(int i = 0; i < this->size(); i++) {
            os << std::setw(3) << this->operator[](i);
        }
        os << "\n" << std::setw(10) << std::left << "T[SA[i]]" << std::setw(3) << "|";
        for(int i = 0; i < this->size(); i++) {
            os << std::setw(3) << T[this->operator[](i)];
        }
        os << "\n" << std::setw(10) << std::left << "LCP[i]" << std::setw(3) << "|";
        
        
        for(int i = 0; i < this->size(); i++) {
            os << std::setw(3) << LCPtabel[this->operator[](i)];
        }
    }

private:
    std::vector<int> LCPtabel;
};
