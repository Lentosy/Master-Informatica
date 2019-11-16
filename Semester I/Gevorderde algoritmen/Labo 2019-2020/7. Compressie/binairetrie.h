#ifndef __BINAIRETRIE_H__
#define __BINAIRETRIE_H__
#include "bincode.h"
#include <functional>
#include <memory>
using std::cerr;
/**********************************************************************

   Class: BinaireTrie, met hulpklassen van knopen
   
   beschrijving: Huffmantries, geschikt voor byte-alfabet
   letters zijn 0-255, plus afsluitingsteken 256.
   Een lege Huffmantrie is zinloos, ook als deeltrie
   Alleen bij opbouw zijn er zo'n tries mogelijk.
   Vandaar dat de parameterloze constructor protected is
   
***************************************************************************/
using std::cout;
class Trieknoop;

class BinaireTrie : public std::unique_ptr<Trieknoop>{
friend class TrieNietblad;
public:
    BinaireTrie(const Bincode&);
    BinaireTrie(const BinaireTrie&);
    BinaireTrie& operator=(std::unique_ptr<Trieknoop>&& a){
        std::unique_ptr<Trieknoop>::operator=(move(a));
        return *this;
    };
    BinaireTrie& operator=(BinaireTrie&& a){
        std::unique_ptr<Trieknoop>::operator=(move(a));
        return *this;
    };
protected:
    BinaireTrie() : std::unique_ptr<Trieknoop>(){};
    BinaireTrie( std::unique_ptr<Trieknoop>&& a) : std::unique_ptr<Trieknoop>(move(a)){};
//hulpfunctie voor constructor uitgaande van Bincode
    void voegToe(const Varbitpatroon& vb, int karakter);
};

class Trieknoop {
public:
    virtual bool isBlad() = 0;
};

class TrieBlad : public Trieknoop {
public:
    TrieBlad(int karakter) : karakter{karakter}{};
    virtual bool isBlad(){ return true;}
    int karakter;
};

class TrieNietblad : public Trieknoop{
public:
    TrieNietblad(){};
    TrieNietblad(BinaireTrie&& l, BinaireTrie&& r) : links(move(l)), rechts(move(r)){};
    virtual bool isBlad(){ return false;}
    BinaireTrie& geefKind(bool rechterkind){
        return (rechterkind ? rechts : links);
    };
    BinaireTrie links, rechts;
};

BinaireTrie::BinaireTrie(const Bincode& bincode){
    // 257 = aantal codewoorden VOORLOPIG TODO FIX BUG POSSIBLE ERROR NUCLEAR 
    for(int i = 0; i < 257; i++) {
        this->voegToe(bincode[i], i);
    }
}

void BinaireTrie::voegToe(const Varbitpatroon& vb, int karakter) {
    // aangezien de code een huffmancodering is, is geen enkel codewoord het prefix van een andere codewoord
    std::cout << "Voegtoe: " << karakter << "[" << vb << "]\n";
    BinaireTrie* huidig = this;
    for(int i = 0; i < vb.geeflengte(); i++){
        if(!*huidig){
            *huidig = std::make_unique<TrieNietblad>();
        }
        
        huidig = &(static_cast<TrieNietblad*>(huidig->get()))->geefKind(vb.geefbit(i));
        
    }    
    *huidig = std::make_unique<TrieBlad>(karakter);
    std::cout << karakter << " in blad\n";
}

#endif