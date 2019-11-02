
#ifndef MINIMALESNEDE_H
#define MINIMALESNEDE_H

#include "../../libraries/graaf/graaf.h"
#include "stroomnetwerk.h"

#include <vector>

// Minimale snede (P, V): geeft true als de knoop tot P behoort, false als die tot V behoort
class MinimaleSnede : public std::vector<bool>
{
public:
    // De constructor berekent de k-samenhangendheid van de opgegeven ongewogen gerichte graaf
    // en steekt een bijbehorende minimale snede in *this
    MinimaleSnede(const Graaf<GERICHT>& graaf, VolgendPadZoeker<int>* padzoeker);

    using std::vector<bool>::operator=;

    int geef_grootte() const; // Geeft het aantal verbindingen in de snede;

private:
    int grootte = 0;
};

MinimaleSnede::MinimaleSnede(const Graaf<GERICHT>& graaf, VolgendPadZoeker<int>* padzoeker) : std::vector<bool>(graaf.aantalKnopen(), true)
{
    GraafMetTakdata<GERICHT, int> verbindingsgraaf{graaf.aantalKnopen()};

    for (int knoop_nr = 0; knoop_nr < graaf.aantalKnopen(); knoop_nr++)
    {
        for (const auto& verbinding : graaf[knoop_nr])
        {
            int buur_nr = verbinding.first;

            verbindingsgraaf.voegVerbindingToe(knoop_nr, buur_nr, 1);
        }
    }

    grootte = std::numeric_limits<int>::max();

    for (int i = 0; i < (verbindingsgraaf.aantalKnopen() - 1); i++)
    {
        Stroomnetwerk<int> sn{verbindingsgraaf, i, (i + 1), padzoeker};
        int huidige_grootte = sn.geef_maximum_stroom();
        if (huidige_grootte < grootte)
        {
            grootte = huidige_grootte;
            (*this) = sn.geef_minimale_snede();
        }
    }

    Stroomnetwerk<int> sn{verbindingsgraaf, (verbindingsgraaf.aantalKnopen() - 1), 0, padzoeker};
    int huidige_grootte = sn.geef_maximum_stroom();
    if (huidige_grootte < grootte)
    {
        grootte = huidige_grootte;
        (*this) = sn.geef_minimale_snede();
    }
}

int MinimaleSnede::geef_grootte() const
{
    return grootte;
}

#endif
