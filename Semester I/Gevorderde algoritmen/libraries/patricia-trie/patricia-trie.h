#ifndef PATRICIA_TRIE_H
#define PATRICIA_TRIE_H

#include "../stringmetbits/stringmetbits.h"

#include <cassert>
#include <memory>

template <class Data>
class PBoom;

template <class Data>
class PKnoop;

template <class Data>
class PBoom
{
    friend class PKnoop<Data>;

public:
    PBoom<Data>();

    void voeg_toe(const StringMetBits& sleutel, const Data& data);
    Data geef_data(const StringMetBits& sleutel);

private:
    PKnoop<Sleutel> k;
};

template <class Data>
class PKnoop
{
    friend class Pboom<Data>;

protected:
    StringMetBits sl;
    Data data;

    int index;
    
    std::unique_ptr<PKnoop<Data>> links;
    std::unique_ptr<PKnoop<Data>> rechts;
};

#endif
