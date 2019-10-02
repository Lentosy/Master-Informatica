#ifndef SHIFTAND_H
#define SHIFTAND_H

#include "bitpatroon.h"

#include <queue>

using uchar = unsigned char;

constexpr static int ALFABET_GROOTTE = 256; // 2^8

class ShiftAnd
{
public:
    ShiftAnd(const uchar* naald, uint _naaldlengte);
    std::queue<const uchar*> zoek_exact(const uchar* hooiberg, uint hooiberglengte, bool overlap = false);
    std::queue<const uchar*> zoek_1_vervanging(const uchar* hooiberg, uint hooiberglengte, bool overlap = false);

private:
    Bitpatroon locatie_letters_in_patroon[ALFABET_GROOTTE];
    const uchar* naald;
    uint naald_lengte;
};

ShiftAnd::ShiftAnd(const uchar* naald, uint naald_lengte) : naald{naald}, naald_lengte{naald_lengte}
{
    if (naald_lengte > patroonlengte)
    {
        throw "De naald lengte is te groot";
    }

    for (int i = 0; i < naald_lengte; i++)
    {
        locatie_letters_in_patroon[naald[i]] |= Bitpatroon::eenbit(i);
    }
}

std::queue<const uchar*> ShiftAnd::zoek_exact(const uchar* hooiberg, uint hooiberg_lengte, bool overlap)
{
    std::queue<const uchar*> gevonden;

    Bitpatroon huidig;

    for (int i = 0; i < hooiberg_lengte; i++)
    {
        huidig = huidig.shiftrechts(1);
        huidig |= Bitpatroon::eenbit(0);
        huidig &= locatie_letters_in_patroon[hooiberg[i]];

        if (huidig.en(Bitpatroon::eenbit(naald_lengte - 1)))
        {
            gevonden.push(hooiberg + i);

            if (!overlap)
            {
                huidig &= Bitpatroon{};
            }
        }
    }

    return gevonden;
}

std::queue<const uchar*> ShiftAnd::zoek_1_vervanging(const uchar* hooiberg, uint hooiberg_lengte, bool overlap)
{
    std::queue<const uchar*> gevonden;

    Bitpatroon huidig_zonder_fout;
    Bitpatroon huidig_1_vervanging;
    Bitpatroon schuif_huidig_zonder_fout;

    for (int i = 0; i < hooiberg_lengte; i++)
    {
        // Schuif(R^0_j)
        schuif_huidig_zonder_fout = huidig_zonder_fout.shiftrechts(1);
        schuif_huidig_zonder_fout |= Bitpatroon::eenbit(0);

        // Schuif(R^1_j EN S[T[j + 1]]
        huidig_1_vervanging = huidig_1_vervanging.shiftrechts(1);
        huidig_1_vervanging |= Bitpatroon::eenbit(0);
        huidig_1_vervanging &= locatie_letters_in_patroon[hooiberg[i]];

        // Schuif(R^0_j) OR (Schuif(R^1_j EN S[T[j + 1]])
        huidig_1_vervanging |= schuif_huidig_zonder_fout;

        // Schuif(R^0_j EN S[T[j + 1]]
        huidig_zonder_fout = huidig_zonder_fout.shiftrechts(1);
        huidig_zonder_fout |= Bitpatroon::eenbit(0);
        huidig_zonder_fout &= locatie_letters_in_patroon[hooiberg[i]];

        if (huidig_1_vervanging.en(Bitpatroon::eenbit(naald_lengte - 1)))
        {
            gevonden.push(hooiberg + i);

            if (!overlap)
            {
                huidig_zonder_fout &= Bitpatroon{};
                huidig_1_vervanging &= Bitpatroon{};
                schuif_huidig_zonder_fout &= Bitpatroon{};
            }
        }
    }

    return gevonden;
}

#endif
