#ifndef STROOMNETWERK_H
#define STROOMNETWERK_H

#include "../../libraries/graaf/graaf.h"
#include "vergrotendpad.h"
#include "volgendpadzoeker.h"

#include <cassert>
#include <sstream>
#include <string>

template <class T>
class VolgendPadZoeker;

template <class T> // T = takdata
class Stroomnetwerk : public GraafMetTakdata<GERICHT, T>
{
public:
    // Graaf<GERICHT>(gr) moet toegevoegd, anders roept de copyconstructor van GraafMetTakdata de defaultconstructor van
    // Graaf op en krijgen we een lege graaf.
    Stroomnetwerk<T>(const GraafMetTakdata<GERICHT, T>& graaf, int producent, int verbruiker);
    Stroomnetwerk<T>(const GraafMetTakdata<GERICHT, T>& graaf,
                     int producent,
                     int verbruiker,
                     VolgendPadZoeker<T>* padzoeker);
    // Geen unique_ptr voor padzoeker:
    // https://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters/ en
    // https://stackoverflow.com/questions/8114276/how-do-i-pass-a-unique-ptr-argument-to-a-constructor-or-a-function

    void updateStroomnetwerk(Stroomnetwerk<T>& stroomnetwerk, const Pad<T>& vergrotendpad);
    void updateRestnetwerk(Stroomnetwerk<T>& restnetwerk, const Pad<T>& vergrotendpad);
    int get_producent() const;
    int get_verbruiker() const;
    std::string genereer_dot_code() const;
    std::vector<bool> geef_minimale_snede() const;
    T geef_maximum_stroom() const;

protected:
    int producent;
    int verbruiker;
    T maximum_stroom;

    std::vector<bool> minimale_snede;

private:
    void voegStroomToe(int van, int naar, int stroom);
};

/* https://stackoverflow.com/questions/19453217/why-are-back-edges-required-in-the-ford-fulkerson-algorithm#19720139
 *
 * Back edges are necessary when doing the Ford-Fulkerson algorithm in case the path that you choose ends up not being a
 * part of the overall flow.
 * As an example where back edges are necessary, consider this flow network:
 *
 *     s
 *    / \
 *   a   b
 *    \ / \
 *     c   d
 *      \ /
 *       t
 *
 * Assume that all edges point down and that all edges have capacity 1 and that you want to find a flow from s to t.
 * Suppose on the first iteration of Ford-Fulkerson that you take the path s -> b -> c -> t. At this point, you've
 * pushed one unit of flow from s to t. If you don't add in any back edges, you're left with this:
 *
 *     s
 *    /
 *   a   b
 *    \   \
 *     c   d
 *        /
 *       t
 *
 * There are no more s-t paths, but that doesn't mean you have a max flow. You can push two units of flow from s to t by
 * sending one along the path s -> a -> c -> t and the other along the path s -> b -> d -> t. Without any back edges in
 * the residual flow network, you would never discover this other path.
 *
 * Hope this helps!
 */

template <class T>
Stroomnetwerk<T>::Stroomnetwerk(const GraafMetTakdata<GERICHT, T>& graaf, int producent, int verbruiker)
: Graaf<GERICHT>{graaf}, GraafMetTakdata<GERICHT, T>{graaf}, producent{producent}, verbruiker{verbruiker}
{
    // TODO, deze klass in 2 klassen trekken (stroomnetwerk en opgelost_stroomnetwerk of stroomnetwerk en stroomnetwerkoplosser) 
}

template <class T>
Stroomnetwerk<T>::Stroomnetwerk(const GraafMetTakdata<GERICHT, T>& graaf,
                                int producent,
                                int verbruiker,
                                VolgendPadZoeker<T>* padzoeker)
: Graaf<GERICHT>{graaf.aantalKnopen()},
  producent{producent},
  verbruiker{verbruiker},
  minimale_snede(graaf.aantalKnopen()),
  maximum_stroom{static_cast<T>(0)}
{
    // Los stroomnetwerk op

    Stroomnetwerk<T> restnetwerk{graaf, producent, verbruiker};

    Pad<T> vergrotendpad = padzoeker->zoek_volgend_vergrotend_pad(restnetwerk);
    while (!vergrotendpad.empty())
    {
        // += en -= hebben niets met elkaar te maken. Het een is voor het stroomnetwerk (enkel aanpassen takdata), het
        // ander voor het restnetwerk (aanpassen takdata en verbindingen). Je kan eventueel ook andere functienamen
        // gebruiken zoals updateStroomnetwerk en updateRestnetwerk
        //
        // restnetwerk -= vergrotendpad;
        // *this += vergrotendpad;
        //
        updateRestnetwerk(restnetwerk, vergrotendpad);
        updateStroomnetwerk(*this, vergrotendpad);
        vergrotendpad = padzoeker->zoek_volgend_vergrotend_pad(restnetwerk);
    }

    // Bepaal de snede

    std::vector<bool> is_al_bezocht(restnetwerk.aantalKnopen());
    std::stack<int> te_bezoeken;
    te_bezoeken.push(producent);

    while (!te_bezoeken.empty())
    {
        int knoop_nr = te_bezoeken.top();
        te_bezoeken.pop();

        if (!is_al_bezocht[knoop_nr])
        {
            minimale_snede[knoop_nr] = true;
            is_al_bezocht[knoop_nr] = true;

            for (const auto& verbinding : restnetwerk[knoop_nr])
            {
                te_bezoeken.push(verbinding.first);
            }
        }
    }

    // Bepaal maximum stroom

    for (const auto& it : (*this)[producent])
    {
        const T* stroom = this->geefTakdata(producent, it.first);

        if (stroom)
        {
            maximum_stroom += *stroom;
        }
    }
}

template <class T>
int Stroomnetwerk<T>::get_producent() const
{
    return producent;
}

template <class T>
int Stroomnetwerk<T>::get_verbruiker() const
{
    return verbruiker;
}

template <class T>
void Stroomnetwerk<T>::voegStroomToe(int van, int naar, int stroom)
{
    if (this->verbindingsnummer(van, naar) == -1)
    {
        this->voegVerbindingToe(van, naar, stroom);
    }
    else
    {
        *(this->geefTakdata(van, naar)) += stroom;
    }
}

template <class T>
void Stroomnetwerk<T>::updateStroomnetwerk(Stroomnetwerk<T>& stroomnetwerk, const Pad<T>& vergrotendpad)
{
    if (vergrotendpad.empty())
    {
        return;
    }

    for (int i = 1; i < vergrotendpad.size(); i++)
    {
        int van = vergrotendpad[i - 1];
        int naar = vergrotendpad[i];

        T toe_te_voegen_stroom = vergrotendpad.geef_capaciteit();

        if (this->verbindingsnummer(naar, van) == -1)
        {
            stroomnetwerk.voegStroomToe(van, naar, toe_te_voegen_stroom);
        }
        else
        {
            T* terugstroom = stroomnetwerk.geefTakdata(naar, van);

            if (*terugstroom >= toe_te_voegen_stroom)
            {
                *terugstroom -= toe_te_voegen_stroom;
            }
            else
            {
                toe_te_voegen_stroom -= *terugstroom;
                *terugstroom = 0;
                stroomnetwerk.voegStroomToe(van, naar, toe_te_voegen_stroom);
            }
        }
    }
}

template <class T>
void Stroomnetwerk<T>::updateRestnetwerk(Stroomnetwerk<T>& restnetwerk, const Pad<T>& vergrotendpad)
{
    if (vergrotendpad.empty())
    {
        return;
    }

    for (int i = 1; i < vergrotendpad.size(); i++)
    {
        int van = vergrotendpad[i - 1];
        int naar = vergrotendpad[i];

        assert(restnetwerk.verbindingsnummer(van, naar) != -1);

        T* heenstroom = restnetwerk.geefTakdata(van, naar);

        assert(*heenstroom >= vergrotendpad.geef_capaciteit());
        *heenstroom -= vergrotendpad.geef_capaciteit();

        if (*heenstroom == 0)
        {
            restnetwerk.verwijderVerbinding(van, naar);
        }

        restnetwerk.voegStroomToe(naar, van, vergrotendpad.geef_capaciteit());
    }
}

template <class T>
std::string Stroomnetwerk<T>::genereer_dot_code() const
{
    std::stringstream out;

    out << "digraph stroomnetwerk {" << std::endl;

    for (int i = 0; i < this->aantalKnopen(); i++)
    {
        const auto& knoop = (*this)[i];

        for (const auto& it : knoop)
        {
            out << "\t" << i << " -> " << it.first << " [label=\"" << *(this->geefTakdata(i, it.first)) << "\"];"
                << std::endl;
        }
    }

    out << "}" << std::endl;

    return out.str();
}

template <class T>
T Stroomnetwerk<T>::geef_maximum_stroom() const
{
    return maximum_stroom;
}

template <class T>
std::vector<bool> Stroomnetwerk<T>::geef_minimale_snede() const
{
    return minimale_snede;
}

#endif
