
#ifndef SPLAYBOOMBOTTOMUP_H
#define SPLAYBOOMBOTTOMUP_H

#include <cmath>

#include "../binaire-boom/binaireboom.h"

template <class Sleutel, class Data>
class SplayboomBottomUp : public BinaireBoom<Sleutel, Data>
{
public:
    using BinaireBoom<Sleutel, Data>::is_leeg;
    using BinaireBoom<Sleutel, Data>::zoek_plaats;

    std::tuple<BinaireBoom<Sleutel, Data>*, Knoop<Sleutel, Data>*> zoek(const Sleutel& sleutel);
    void voeg_toe(const Sleutel& sleutel, const Data& data);
    double potentiaal() const;

private:
    void splay(BinaireBoom<Sleutel, Data>*& plaats);
    void
    bereken_potentiaal(const BinaireBoom<Sleutel, Data>& splayboom, double& som_gewichten, int& aantal_knopen) const;
    BinaireBoom<Sleutel, Data>& vind_binaireboom_van_wortel(Knoop<Sleutel, Data>& knoop);
};

/******************************************************************************/

template <class Sleutel, class Data>
void SplayboomBottomUp<Sleutel, Data>::bereken_potentiaal(const BinaireBoom<Sleutel, Data>& splayboom,
                                                  double& som_gewichten,
                                                  int& aantal_knopen) const
{
    int aantal_knopen_links = 0;
    int aantal_knopen_rechts = 0;

    if (splayboom->geef_kind(Richting::LINKS))
    {
        bereken_potentiaal(splayboom->geef_kind(Richting::LINKS), som_gewichten, aantal_knopen_links);
    }

    if (splayboom->geef_kind(Richting::RECHTS))
    {
        bereken_potentiaal(splayboom->geef_kind(Richting::RECHTS), som_gewichten, aantal_knopen_rechts);
    }

    aantal_knopen = aantal_knopen_links + aantal_knopen_rechts + 1;
    som_gewichten += std::log2(aantal_knopen);
}

template <class Sleutel, class Data>
double SplayboomBottomUp<Sleutel, Data>::potentiaal() const
{
    int aantal_knopen = 0;
    double som_gewichten = 0;

    bereken_potentiaal(*this, som_gewichten, aantal_knopen);

    return som_gewichten;
}

template <class Sleutel, class Data>
std::tuple<BinaireBoom<Sleutel, Data>*, Knoop<Sleutel, Data>*> SplayboomBottomUp<Sleutel, Data>::zoek(const Sleutel& sleutel)
{
    if (is_leeg())
    {
        throw "Boom is leeg";
    }

    auto [plaats, ouder] = zoek_plaats(sleutel);

    if (!(*plaats))
    {
        if (!ouder)
        {
            throw "Er is geen ouder.";
        }

        plaats = &vind_binaireboom_van_wortel(*ouder);
    }

    splay(plaats);

    return std::make_tuple(plaats, ouder);
}

template <class Sleutel, class Data>
void SplayboomBottomUp<Sleutel, Data>::voeg_toe(const Sleutel& sleutel, const Data& data)
{
    auto [plaats, ouder] = zoek_plaats(sleutel);

    if (*plaats)
    {
        throw "De sleutel is al aanwezig in de boom.";
    }

    *plaats = BinaireBoom<Sleutel, Data>{sleutel, data};
    (*plaats)->zet_ouder(ouder);

    splay(plaats);
}

template <class Sleutel, class Data>
BinaireBoom<Sleutel, Data>& SplayboomBottomUp<Sleutel, Data>::vind_binaireboom_van_wortel(Knoop<Sleutel, Data>& knoop)
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

template <class Sleutel, class Data>
void SplayboomBottomUp<Sleutel, Data>::splay(BinaireBoom<Sleutel, Data>*& plaats)
{
    if (!plaats)
    {
        return;
    }

    while (plaats != this)
    {
        BinaireBoom<Sleutel, Data>& huidige_boom = *plaats;
        BinaireBoom<Sleutel, Data>& ouder_boom = vind_binaireboom_van_wortel(*(huidige_boom->geef_ouder()));

        if (ouder_boom.get() == this->get())
        {
            this->roteer(!(huidige_boom->is_linker_of_rechter_kind()));

            plaats = &ouder_boom;
        }
        else
        {
            BinaireBoom<Sleutel, Data>& grootouder_boom = vind_binaireboom_van_wortel(*(ouder_boom->geef_ouder()));

            if (huidige_boom->is_linker_of_rechter_kind() == ouder_boom->is_linker_of_rechter_kind())
            {
                grootouder_boom.roteer(!(ouder_boom->is_linker_of_rechter_kind()));

                grootouder_boom.roteer(!(huidige_boom->is_linker_of_rechter_kind()));
            }
            else
            {
                ouder_boom.roteer(!(huidige_boom->is_linker_of_rechter_kind()));

                grootouder_boom.roteer(!(ouder_boom->is_linker_of_rechter_kind()));
            }

            plaats = &grootouder_boom;
        }
    }
}

#endif