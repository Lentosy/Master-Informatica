
#ifndef SPLAYBOOMBOTTOMUP_H
#define SPLAYBOOMBOTTOMUP_H

#include <cmath>

#include "../binaire-boom/binaireboom.h"

template <class Sleutel, class Data>
class SplayboomTopDown : public BinaireBoom<Sleutel, Data>
{
public:
    using BinaireBoom<Sleutel, Data>::is_leeg;
    using BinaireBoom<Sleutel, Data>::zoek_plaats;

    Data zoek(const Sleutel& sleutel);
    void voeg_toe(const Sleutel& sleutel, const Data& data);

private:
    void splay(BinaireBoom<Sleutel, Data>*& plaats);
    BinaireBoom<Sleutel, Data>& vind_binaireboom_van_wortel(Knoop<Sleutel, Data>& knoop);
};

/******************************************************************************/

template <class Sleutel, class Data>
Data SplayboomTopDown<Sleutel, Data>::zoek(const Sleutel& sleutel)
{
    if (is_leeg())
    {
        throw "Boom is leeg";
    }

    throw; // TODO
}

template <class Sleutel, class Data>
void SplayboomTopDown<Sleutel, Data>::voeg_toe(const Sleutel& sleutel, const Data& data)
{
}

template <class Sleutel, class Data>
BinaireBoom<Sleutel, Data>& SplayboomTopDown<Sleutel, Data>::vind_binaireboom_van_wortel(Knoop<Sleutel, Data>& knoop)
{
    if (&knoop == this->get())
    {
        return (*this);
    }
    else
    {
        if (!knoop.geef_ouder())
        {
            throw "De knoop heeft geen ouder";
        }

        return knoop.geef_ouder()->geef_kind(knoop.is_linker_of_rechter_kind());
    }
}

#endif