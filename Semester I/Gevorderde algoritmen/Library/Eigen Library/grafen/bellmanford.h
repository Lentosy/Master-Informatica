#include "graaf.h"


typedef std::map<int, int> Burenlijst;


template <class T>
class BellmanFord {
public:
    std::vector<int> geefKortstePad(const GraafMetTakdata<GERICHT, T> * graaf, int van, int naar) {
        
        std::vector<int> afstanden(graaf->aantalKnopen(), INT_MAX);
        afstanden[van] = 0;

        for(int k = 0; k < graaf->aantalKnopen(); k++) { //
            
        }
        

    }

};