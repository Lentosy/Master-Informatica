#ifndef KORTSTEPADZOEKER_H
#define KORTSTEPADZOEKER_H

#include "../volgendpadzoeker.h"

#include <algorithm>
#include <queue>
#include <vector>

template <class T>
class KortstePadZoeker : public VolgendPadZoeker<T>
{
public:
    Pad<T> zoek_volgend_vergrotend_pad(const Stroomnetwerk<T>& stroomnetwerk) override;

protected:
    T bepaal_capaciteit(const Stroomnetwerk<T>& stroomnetwerk, const Pad<T>& pad) const;
};

template <class T>
Pad<T> KortstePadZoeker<T>::zoek_volgend_vergrotend_pad(const Stroomnetwerk<T>& stroomnetwerk)
{
    std::vector<bool> is_knoop_bezocht(stroomnetwerk.aantalKnopen(), false);
    std::vector<int> voorlopers(stroomnetwerk.aantalKnopen(), -1);
    std::queue<int> te_bezoeken_knopen;

    te_bezoeken_knopen.push(stroomnetwerk.get_producent());

    bool is_verbruiker_gevonden = false;
    while (!te_bezoeken_knopen.empty() && !is_verbruiker_gevonden)
    {
        int huidige_knoopnr = te_bezoeken_knopen.front();
        te_bezoeken_knopen.pop();

        if (huidige_knoopnr == stroomnetwerk.get_verbruiker())
        {
            is_verbruiker_gevonden = true;
        }
        else if (!is_knoop_bezocht[huidige_knoopnr])
        {
            is_knoop_bezocht[huidige_knoopnr] = true;

            for (const auto& it : stroomnetwerk[huidige_knoopnr])
            {
                int buur_knoopnr = it.first;

                if (!is_knoop_bezocht[buur_knoopnr])
                {
                    voorlopers[buur_knoopnr] = huidige_knoopnr;
                    te_bezoeken_knopen.push(buur_knoopnr);
                }
            }
        }
    }

    if (!is_verbruiker_gevonden)
    {
        return Pad<T>{};
    }

    Pad<T> pad;

    int huidige_knoopnr = stroomnetwerk.get_verbruiker();
    while (huidige_knoopnr != stroomnetwerk.get_producent())
    {
        pad.push_back(huidige_knoopnr);
        huidige_knoopnr = voorlopers[huidige_knoopnr];
    }

    pad.push_back(stroomnetwerk.get_producent());
    std::reverse(pad.begin(), pad.end());

    pad.set_capaciteit(bepaal_capaciteit(stroomnetwerk, pad));

    return pad;
}

template <class T>
T KortstePadZoeker<T>::bepaal_capaciteit(const Stroomnetwerk<T>& stroomnetwerk, const Pad<T>& pad) const
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
