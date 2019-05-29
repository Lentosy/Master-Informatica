#ifndef __PARTITIE__
#define __PARTITIE__

#include <vector>


// Klasse voor de opdeling van een verzameling in disjuncte verzamelingen
// Elementen worden voorgesteld door gehele getallen 0..aantalKlassen-1
// Methode: union-find. 
// Elke disjuncte verzameling wordt voorgesteld door een 'boompje'
// Elk element heeft een 'vertegewoordiger', i.e. de wortel van het boompje waartoe hij behoort.
class Partitie
{
public:
    // aantalKlassen is in het begin het aantal "objecten", genummerd 0..aantalKlassen-1
    Partitie(int n_);                                                  ;

    // zoek de vertegenwoordiger van knoop k (i.e. de wortel van het boompje dat k bevat)
    // = 'find'
    //geen const-functie wegens padcompressie
    int vertegenwoordiger(int k);

    // verenig de boompjes waar knopen k1 en k2 in zitten
    // geef 'true' indien er effectief een union plaatsvindt
    // = 2 x 'find' en 'union'
    bool verenig(int k1, int k2);
    // aantal disjuncte verzamelingen (boompjes)
    int geefAantalKlassen();
    int geefAantalElementen();
    //noot: huidige methode is O(n ln n). Dat kan beter, maar dan wordt union trager
    //De functie geeft een vector van vectoren terug, een voor elke klasse, met een gesorteerde lijst van knoopnummers
    vector<vector<int>> geefKlassen();
private:
    // verenig boompjes waarvan v1 en v2 wortel zijn
    // = 'union'
    void verenig_boompjes(int v1, int v2);

    std::vector<int> ouder;   // per knoop: ouderwijzer. zichzelf bij init.
    std::vector<int> grootte; // per wortel: aantal knopen in boompje;
    int              aantalKlassen;       // aantal boompjes
};
Partitie::Partitie(int n_) : ouder(n_), grootte(n_, 1), aantalKlassen(n_){
    for (int i=0; i<aantalKlassen; i++ ){
        ouder[i]=i;
    }
}

int Partitie::vertegenwoordiger(int k){
    // assert(isgeldig(k))
    int v = k;
    while (ouder[v]!=v)
        v = ouder[v];
    // path compression:
    while (k != v)
    {
        int t = ouder[k];
        ouder[k] = v;
        k = t;
    }
        
    return v;
}

bool Partitie::verenig(int k1,int k2){
    int v1 = vertegenwoordiger(k1);
    int v2 = vertegenwoordiger(k2);
    if (v1 != v2) {
        verenig_boompjes(v1, v2);
        return true;
    }
    else
        return false;
}

int Partitie::geefAantalKlassen(){
    return aantalKlassen;
}

int Partitie::geefAantalElementen(){
    return ouder.size();
}

vector<vector<int>> Partitie::geefKlassen(){
    vector<vector<int>> resultaat(aantalKlassen);
    std::map<int,int> vertegenwoordigerNaarKlassennummer;
    int klassennummer=0;
    for (int i=0; i<geefAantalElementen(); i++ ){
        int rep=vertegenwoordiger(i);
        if (vertegenwoordigerNaarKlassennummer.find(rep)==vertegenwoordigerNaarKlassennummer.end())
            vertegenwoordigerNaarKlassennummer[rep]=klassennummer++;
    }
    assert(klassennummer==aantalKlassen);
    for (int i=0; i<geefAantalElementen(); i++ ){
        resultaat[vertegenwoordigerNaarKlassennummer[vertegenwoordiger(i)]].emplace_back(i);
    };
    return resultaat;

}

void Partitie::verenig_boompjes(int v1,int v2){
    // assert (isgeldig(v1) && isgeldig(v2) && ouder[v1]==-1 && ouder[v2]==-1 && v1!=v2)
    
    // union-by-size:
    if (grootte[v1] > grootte[v2]){
        ouder[v2] = v1;
        grootte[v2] += grootte[v1];
    }
    else{
        ouder[v1] = v2;
        grootte[v1] += grootte[v2];
    }
    aantalKlassen--;
}




#endif
