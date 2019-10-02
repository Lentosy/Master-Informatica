
#ifndef KDTREE_H
#define KDTREE_H

#include "punt2d.h"

#include <limits>
#include <memory>
#include <tuple>

enum class Dimensie
{
    X,
    Y
};

;

class KdTree
{
private:
    class Knoop2D;

public:
    void voeg_toe(const Punt2D& punt);
    std::tuple<Punt2D, int, int> zoek_dichtste_buur(const Punt2D& punt);
    bool is_leeg() const;

private:
    std::unique_ptr<Knoop2D>* zoek_locatie(const Punt2D& zoek_punt);
    std::tuple<std::unique_ptr<KdTree::Knoop2D>*, std::unique_ptr<KdTree::Knoop2D>*>
    geef_kind(const Punt2D& zoek_punt, Knoop2D& huidige_knoop, int diepte);
    void zoek_dichtste_buur_recursief(const Punt2D& zoek_punt,
                                      const std::unique_ptr<Knoop2D>& huidige_knoop,
                                      Punt2D& gevonden_dichtste_punt,
                                      int& kleinste_afstand,
                                      int& aantal_bezochte_knopen,
                                      int diepte);

    std::unique_ptr<Knoop2D> wortel;
};

class KdTree::Knoop2D
{
public:
    Knoop2D(const Punt2D& p);
    Knoop2D(const Knoop2D& p) = delete;
    Knoop2D(Knoop2D&& p) = default;
    Knoop2D& operator=(const Knoop2D& p) = delete;
    Knoop2D& operator=(Knoop2D&& p) = default;
    virtual ~Knoop2D() = default;

    Punt2D punt;
    std::unique_ptr<Knoop2D> links;
    std::unique_ptr<Knoop2D> rechts;
};

/******************************************************************************/

std::tuple<std::unique_ptr<KdTree::Knoop2D>*, std::unique_ptr<KdTree::Knoop2D>*>
KdTree::geef_kind(const Punt2D& zoek_punt, Knoop2D& huidige_knoop, int diepte)
{
    std::unique_ptr<Knoop2D>* volgende_knoop = nullptr;
    std::unique_ptr<Knoop2D>* andere_volgende_knoop = nullptr;

    if ((diepte % 2) == 0)
    {
        if (zoek_punt.x < huidige_knoop.punt.x)
        {
            volgende_knoop = &(huidige_knoop.links);
            andere_volgende_knoop = &(huidige_knoop.rechts);
        }
        else
        {
            volgende_knoop = &(huidige_knoop.rechts);
            andere_volgende_knoop = &(huidige_knoop.links);
        }
    }
    else
    {
        if (zoek_punt.y < (huidige_knoop.punt).y)
        {
            volgende_knoop = &(huidige_knoop.links);
            andere_volgende_knoop = &(huidige_knoop.rechts);
        }
        else
        {
            volgende_knoop = &(huidige_knoop.rechts);
            andere_volgende_knoop = &(huidige_knoop.links);
        }
    }

    return std::make_tuple(volgende_knoop, andere_volgende_knoop);
}

std::unique_ptr<KdTree::Knoop2D>* KdTree::zoek_locatie(const Punt2D& punt)
{
    std::unique_ptr<Knoop2D>* huidig_punt = &wortel;
    int diepte = 0;

    while (*huidig_punt && ((*huidig_punt)->punt != punt))
    {
        std::tie(huidig_punt, std::ignore) = geef_kind(punt, (**huidig_punt), diepte);

        diepte++;
    }

    return huidig_punt;
}

void KdTree::voeg_toe(const Punt2D& punt)
{
    std::unique_ptr<Knoop2D>* locatie = zoek_locatie(punt);

    if (!*locatie)
    {
        *locatie = std::make_unique<Knoop2D>(punt);
    }
}

bool KdTree::is_leeg() const
{
    return (wortel == nullptr);
}

std::tuple<Punt2D, int, int> KdTree::zoek_dichtste_buur(const Punt2D& zoek_punt)
{
    if (!wortel)
    {
        throw "Boom is leeg";
    }

    Punt2D gevonden_dichtste_punt;
    int kleinste_afstand = std::numeric_limits<int>::max();
    int aantal_bezochte_knopen = 0;

    zoek_dichtste_buur_recursief(
            zoek_punt, wortel, gevonden_dichtste_punt, kleinste_afstand, aantal_bezochte_knopen, 0);

    return std::make_tuple(gevonden_dichtste_punt, kleinste_afstand, aantal_bezochte_knopen);
}

void KdTree::zoek_dichtste_buur_recursief(const Punt2D& zoek_punt,
                                          const std::unique_ptr<Knoop2D>& huidige_knoop,
                                          Punt2D& gevonden_dichtste_punt,
                                          int& kleinste_afstand,
                                          int& aantal_bezochte_knopen,
                                          int diepte)
{
    if (!huidige_knoop)
    {
        return;
    }

    aantal_bezochte_knopen++;

    int huidige_afstand = (huidige_knoop->punt).afstand(zoek_punt);

    if (huidige_afstand < kleinste_afstand)
    {
        kleinste_afstand = huidige_afstand;
        gevonden_dichtste_punt = huidige_knoop->punt;
    }

    const auto [volgende_knoop, andere_volgende_knoop] = geef_kind(zoek_punt, (*huidige_knoop), diepte);

    zoek_dichtste_buur_recursief(zoek_punt,
                                 (*volgende_knoop),
                                 gevonden_dichtste_punt,
                                 kleinste_afstand,
                                 aantal_bezochte_knopen,
                                 (diepte + 1));

    int afstand_splitsing = 0;
    if ((diepte % 2) == 0)
    {
        afstand_splitsing = ((huidige_knoop->punt).x - zoek_punt.x);
    }
    else
    {
        afstand_splitsing = ((huidige_knoop->punt).y - zoek_punt.y);
    }
    afstand_splitsing *= afstand_splitsing;

    // /* sqrt( (x1 - x2)^2 + (y1 - y2)^2 ) < sqrt( (x1 - x2)^2 + (y1 - y1)^2 )
    //  * <=> sqrt( (x1 - x2)^2 + (y1 - y2)^2 ) < sqrt( (x1 - x2)^2 )
    //  * <=> (x1 - x2)^2 + (y1 - y2)^2 < (x1 - x2)^2
    //  * <=> kwadafstand < (x1 - x2)^2
    //  */

    if (afstand_splitsing < kleinste_afstand)
    {
        zoek_dichtste_buur_recursief(zoek_punt,
                                     (*andere_volgende_knoop),
                                     gevonden_dichtste_punt,
                                     kleinste_afstand,
                                     aantal_bezochte_knopen,
                                     (diepte + 1));
    }
}

KdTree::Knoop2D::Knoop2D(const Punt2D& punt) : punt{punt}
{
}

#endif