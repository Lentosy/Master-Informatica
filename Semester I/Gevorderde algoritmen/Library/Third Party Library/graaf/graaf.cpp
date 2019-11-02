 
#include "graaf.h"

template <>
void Graaf<ONGERICHT>::voegVerbindingToeInDatastructuur(int van, int naar, int verbindingsnummer)
{
    knopen[van][naar] = verbindingsnummer;
    knopen[naar][van] = verbindingsnummer;
}

template <>
void Graaf<ONGERICHT>::verwijderVerbindingUitDatastructuur(int van, int naar)
{
    knopen[van].erase(naar);
    knopen[naar].erase(van);
}

template <>
std::string Graaf<GERICHT>::genereer_dot_code() const
{
    std::stringstream out;

    out << "digraph graaf {" << std::endl;

    for (int i = 0; i < aantalKnopen(); i++)
    {
        const auto& knoop = (*this)[i];

        for (const auto& it : knoop)
        {
            out << "\t" << i << " -> " << it.first << std::endl;
        }
    }

    out << "}" << std::endl;

    return out.str();
}

template <>
bool Graaf<ONGERICHT>::isGericht() const
{
    return false;
} // voor ongerichte graaf