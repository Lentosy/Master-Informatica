#ifndef LANGPADZOEKER_H
#define LANGPADZOEKER_H

#include "../volgendpadzoeker.h"

#include <cassert>
#include <limits>

/**********************************************************************

   Class:Vergrotendpadzoeker

   beschrijving: Methodeklasse die, gegeven een stroomnetwerk,
                 en vergrotend pad teruggeeft.
                 van en verbruiker zijn de knoopnummers van bron en doel.


***************************************************************************/

template <class T>
class LangPadZoeker : public VolgendPadZoeker<T>
{
public:
    Pad<T> zoek_volgend_vergrotend_pad(const Stroomnetwerk<T>& stroomnetwerk) override;

protected:
    void zoek_pad_vanuit_knoop(int knoopnr,
                               int diepte,
                               const Stroomnetwerk<T>& stroomnetwerk,
                               std::vector<int>& voorlopers,
                               std::vector<bool>& is_knoop_bezocht,
                               Pad<T>& pad);

    T bepaal_capaciteit(const Stroomnetwerk<T>& stroomnetwerk, const Pad<T>& pad) const;
};

template <class T>
Pad<T> LangPadZoeker<T>::zoek_volgend_vergrotend_pad(const Stroomnetwerk<T>& stroomnetwerk)
{
    assert(stroomnetwerk.get_producent() != stroomnetwerk.get_verbruiker());

    Pad<T> pad;
    std::vector<int> voorlopers(stroomnetwerk.aantalKnopen());
    std::vector<bool> is_knoop_bezocht(stroomnetwerk.aantalKnopen(), false);

    zoek_pad_vanuit_knoop(stroomnetwerk.get_producent(), 0, stroomnetwerk, voorlopers, is_knoop_bezocht, pad);

    if (pad.size() <= 1)
    {
        return Pad<T>{};
    }

    pad.set_capaciteit(bepaal_capaciteit(stroomnetwerk, pad));

    return pad;
}

// Deze kortste pad zoeker is een niet-ideale zoeker. Het zoekt een lang pad, zodat er een grotere kans is dat eventuele
// fouten op terugverbindingen bij het restnetwerk bovenkomen.
template <class T>
void LangPadZoeker<T>::zoek_pad_vanuit_knoop(int knoopnr,
                                             int diepte,
                                             const Stroomnetwerk<T>& stroomnetwerk,
                                             std::vector<int>& voorlopers,
                                             std::vector<bool>& is_knoop_bezocht,
                                             Pad<T>& pad)
{
    is_knoop_bezocht[knoopnr] = true;
    for (const auto& it : stroomnetwerk[knoopnr])
    {
        int buurnr = it.first;
        int lengte_huidig_pad = (diepte + 2); // producent + tussenliggende knopen + verbruiker

        if (*stroomnetwerk.geefTakdata(knoopnr, buurnr) > 0)
        {
            if ((buurnr == stroomnetwerk.get_verbruiker()) && (lengte_huidig_pad >= pad.size()))
            // verbruiker gevonden en huidige pad is langer?
            {
                voorlopers[stroomnetwerk.get_verbruiker()] = knoopnr;
                pad.resize(lengte_huidig_pad);
                int nr = stroomnetwerk.get_verbruiker();
                int i = (diepte + 1);
                while (nr != stroomnetwerk.get_producent())
                {
                    pad[i] = nr;
                    i--;
                    nr = voorlopers[nr];
                }
                pad[0] = nr;
            }
            else if (buurnr != stroomnetwerk.get_verbruiker()
                     && !is_knoop_bezocht[buurnr]) // buurnr != verbruiker wegens kans op oneindige lussen
            {
                voorlopers[buurnr] = knoopnr;
                zoek_pad_vanuit_knoop(buurnr, (diepte + 1), stroomnetwerk, voorlopers, is_knoop_bezocht, pad);
            }
        }
    }
}

template <class T>
T LangPadZoeker<T>::bepaal_capaciteit(const Stroomnetwerk<T>& stroomnetwerk, const Pad<T>& pad) const
{
    T min_capaciteit = *stroomnetwerk.geefTakdata(pad[0], pad[1]);

    for (int i = 2; i < pad.size(); i++)
    {
        T capaciteit = *stroomnetwerk.geefTakdata(pad[i - 1], pad[i]);
        if (capaciteit < min_capaciteit)
        {
            min_capaciteit = capaciteit;
        }
    }

    return min_capaciteit;
}

#endif
