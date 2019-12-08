#pragma once
#include <memory>
#include <string>



class PatriciaTrie;
class TrieKnoop;
typedef std::unique_ptr<TrieKnoop> KnoopPtr;


/*
* Class TrieKnoop:   Elke knoop in de patriciatrie is een unique pointer naar een TrieKnoop. De klasse zelf is abstract en bevat geen eigenschappen.
*/
class TrieKnoop {
public:
    virtual bool isBlad() = 0;
};

/*
* Class TrieNietBlad:    Deze klasse stelt een inwendige knoop voor in de patriciatrie. Zo een knoop bevat steeds een testindex en een tabel van kindpointers voor elke uitgang in het alfabet
*/
class TrieNietBlad : public TrieKnoop {
public:
    TrieNietBlad(int testindex) : testindex{testindex} {}

    bool isBlad() { return false; }
    int testindex; // de te testen index
    KnoopPtr* geefKind(char c); // Geeft de pointer naar de knoop terug voor uitgangkarakter c
private:
    KnoopPtr kinderen[26]; // enkel alfabetische kleine letters momenteel
};


/*
* Class TrieBlad:     Deze klasse stelt een blad voor in de patriciatrie. Een blad bevat enkel de opgeslagen string.
*/
class TrieBlad : public TrieKnoop{
public:
    TrieBlad(const std::string& s) : s{s} {}

    bool isBlad() { return true; }
    std::string s;
};



/*
* Class PatriciaTrie:     Een patriciatrie is een gecomprimeerde versie van een meerwegstrie. De patriciatrie laat geen duplicate strings toe, en elke string moet voldoen aan de prefixvoorwaarde. 
*/
class PatriciaTrie : public KnoopPtr {
public:
    using KnoopPtr::unique_ptr;

    PatriciaTrie();
    PatriciaTrie(KnoopPtr&& o);
    PatriciaTrie& operator=(KnoopPtr&& o);

    void teken(const char* bestandsnaam) const; // maakt een visuele representatie van de patriciatrie in dot-formaat.
    void voegToe(const std::string& s);         // voegt de string toe aan de patriciatrie indien deze er nog niet in zit.

protected:
    KnoopPtr* zoek(const std::string& s);       // zoekt de string in de patriciatrie. De knoopptr is altijd een blad.
};






