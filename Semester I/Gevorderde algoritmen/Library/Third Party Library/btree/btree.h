
#ifndef BTREE_H
#define BTREE_H

#include "../schijf/schijf.h"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

// Betekenis m: zie cursus

template <class Sleutel, class Data, blokindex m>
class BTree
{
public:
    class iterator;

    // BKnoop is hier enkel public omdat het moet meegegeven worden met Schijf in onze simulatie.
    // Mocht dit niet nodig zijn, is dit best private zodat gewone gebruikers niet zien dat het bestaat
    // en het niet kunnen misbruiken
    class BKnoop;

public:
    BTree(Schijf<BKnoop>& schijf);
    BTree(const BTree& other) = default;
    BTree& operator=(const BTree& other) = default;
    BTree(BTree&& other) = default;
    BTree& operator=(BTree&& other) = default;
    virtual ~BTree() = default;

    std::optional<Data> zoek(const Sleutel& nieuwe_sleutel) const;
    void voegtoe(const Sleutel& nieuwe_sleutel, const Data&);

    iterator begin();
    iterator end();

    std::string dot_code() const;

private:
    Schijf<BKnoop>& schijf;
    BKnoop wortel;
    blokindex wortelindex;
};

template <class Sleutel, class Data, blokindex m>
class BTree<Sleutel, Data, m>::BKnoop
{
    // Public, want normaal zetten we BKnoop private in BTree, zodat gebruikers niet aan BKnoop kunnen
public:
    BKnoop();
    BKnoop(bool is_blad);
    BKnoop(blokindex linkerkind, const Sleutel& sl, const Data& d, blokindex rechterkind);
    BKnoop(const BKnoop& other) = default;
    BKnoop& operator=(const BKnoop& other) = default;
    BKnoop(BKnoop&& other) = default;
    BKnoop& operator=(BKnoop&& other) = default;
    virtual ~BKnoop();

    std::pair<bool, int> is_aanwezig(const Sleutel& nieuwe_sleutel) const;
    void voegtoe(const Sleutel& nieuwe_sleutel,
                 const Data& nieuwe_data,
                 blokindex nieuw_rechterkind = Schijf<BKnoop>::NULL_BLOKINDEX);
    bool is_vol() const;
    void splits_knoop(BKnoop& nieuwe_broer_knoop, Sleutel& middel_sleutel, Data& middel_data);

    Sleutel operator[](int index) const;
    std::string dot_code() const;

    // Opmerking: sleutel[0] en data[0] worden niet gebruikt, zodat indexen vanaf 1 lopen
    //
    // m = 4
    // ARRAY_SIZE = 5
    // sleutel[]   (0)   1   2   3   4      | 4 sleutels
    // data[]      (0)   1   2   3   4      | 4 data
    // index[]         0   1   2   3   4    | 5 indexes
    constexpr static int ARRAY_SIZE = m + 1;
    Sleutel sleutel[ARRAY_SIZE];
    Data data[ARRAY_SIZE];
    blokindex index[ARRAY_SIZE];
    int aantal_kinderen;
    bool is_blad;

    // Crashtest voorkomt dat er meer dan drie knopen in het 'geheugen' zitten (excusief de wortel).
    static int crashtest;
};

template <class Sleutel, class Data, blokindex m>
int BTree<Sleutel, Data, m>::BKnoop::crashtest = 0;

template <class Sleutel, class Data, blokindex m>
class BTree<Sleutel, Data, m>::iterator
{
public:
    using value_type = std::pair<Sleutel, Data>;
    using difference_type = std::ptrdiff_t;
    using pointer = std::pair<Sleutel, Data>*;
    using reference = std::pair<Sleutel, Data>&;
    using iterator_category = std::input_iterator_tag;

    friend void swap(iterator& first, iterator& second);

    iterator(blokindex wortelindex, const BKnoop& wortel, Schijf<BKnoop>& schijf, bool is_initialised);
    iterator& operator=(const iterator& andere);
    iterator(const iterator& andere);
    iterator(iterator&& andere) = delete;
    iterator& operator=(iterator&& andere) = delete;
    virtual ~iterator() = default;

    iterator& operator++();
    iterator operator++(int);
    reference operator*();
    pointer operator->();
    bool operator==(const iterator& andere) const;
    bool operator!=(const iterator& andere) const;

private:
    const blokindex wortelindex;
    const BKnoop& wortel;
    const Schijf<BKnoop>& schijf;

    std::stack<std::pair<blokindex, int>> te_bezoeken_blokken;
    blokindex huidig_blok_index;
    int huidig_sleutel_index;
    BKnoop huidig_blok;

    std::unique_ptr<value_type> huidige_waarde;
};

///////////////////////////////////////////////////////////////schijf{schijf}, /////////////////

template <class Sleutel, class Data, blokindex m>
BTree<Sleutel, Data, m>::BTree(Schijf<BKnoop>& schijf) : schijf{schijf}, wortel{true}
{
    wortelindex = schijf.schrijf(wortel);
}

template <class Sleutel, class Data, blokindex m>
std::optional<Data> BTree<Sleutel, Data, m>::zoek(const Sleutel& nieuwe_sleutel) const
{
    BKnoop huidige_knoop = wortel;
    blokindex huidige_index = wortelindex;

    while (!huidige_knoop.is_blad)
    {
        auto [is_aanwezig, sleutel_index] = huidige_knoop.is_aanwezig(nieuwe_sleutel);
        if (is_aanwezig)
        {
            return huidige_knoop.data[sleutel_index];
        }

        huidige_index = huidige_knoop.index[sleutel_index - 1];
        schijf.lees(huidige_knoop, huidige_index);
    }

    auto [is_aanwezig, sleutel_index] = huidige_knoop.is_aanwezig(nieuwe_sleutel);
    if (is_aanwezig)
    {
        return std::optional<Data>{huidige_knoop.data[sleutel_index]};
    }
    else
    {
        return std::nullopt;
    }
}

template <class Sleutel, class Data, blokindex m>
void BTree<Sleutel, Data, m>::voegtoe(const Sleutel& nieuwe_sleutel, const Data& nieuwe_data)
{
    blokindex huidige_index = wortelindex;
    BKnoop huidige_knoop = wortel;

    std::stack<blokindex> gebruikte_blokindexen;

    while (!huidige_knoop.is_blad)
    {
        gebruikte_blokindexen.push(huidige_index);

        auto [is_aanwezig, sleutel_index] = huidige_knoop.is_aanwezig(nieuwe_sleutel);
        if (is_aanwezig)
        {
            huidige_knoop.data[sleutel_index] = nieuwe_data;

            if (huidige_index == wortelindex)
            {
                wortel = huidige_knoop;
            }

            schijf.herschrijf(huidige_knoop, huidige_index);

            return;
        }

        huidige_index = huidige_knoop.index[sleutel_index - 1];
        schijf.lees(huidige_knoop, huidige_index);
    }

    auto [is_aanwezig, sleutel_index] = huidige_knoop.is_aanwezig(nieuwe_sleutel);
    if (is_aanwezig)
    {
        huidige_knoop.data[sleutel_index] = nieuwe_data;

        if (huidige_index == wortelindex)
        {
            wortel = huidige_knoop;
        }

        schijf.herschrijf(huidige_knoop, huidige_index);

        return;
    }

    huidige_knoop.voegtoe(nieuwe_sleutel, nieuwe_data);

    while (huidige_knoop.is_vol() && huidige_index != wortelindex && !gebruikte_blokindexen.empty())
    {
        Sleutel middel_sleutel;
        Data middel_data;
        BKnoop nieuwe_knoop;
        huidige_knoop.splits_knoop(nieuwe_knoop, middel_sleutel, middel_data);

        schijf.herschrijf(huidige_knoop, huidige_index);
        blokindex nieuwe_knoop_index = schijf.schrijf(nieuwe_knoop);

        huidige_index = gebruikte_blokindexen.top();
        gebruikte_blokindexen.pop();
        schijf.lees(huidige_knoop, huidige_index);

        huidige_knoop.voegtoe(middel_sleutel, middel_data, nieuwe_knoop_index);
    }

    if (huidige_index == wortelindex)
    {
        wortel = huidige_knoop;
    }

    if (!wortel.is_vol())
    {
        schijf.herschrijf(huidige_knoop, huidige_index);
    }
    else
    {
        Sleutel middel_sleutel;
        Data middel_data;
        BKnoop nieuwe_knoop;
        wortel.splits_knoop(nieuwe_knoop, middel_sleutel, middel_data);

        schijf.herschrijf(wortel, wortelindex);
        blokindex nieuwe_knoop_index = schijf.schrijf(nieuwe_knoop);

        wortel = BKnoop{wortelindex, middel_sleutel, middel_data, nieuwe_knoop_index};
        wortelindex = schijf.schrijf(wortel);
    }
}

// Noot: beetje inefficient: knopen worden twee keer ingelezen
template <class Sleutel, class Data, blokindex m>
std::string BTree<Sleutel, Data, m>::dot_code() const
{
    std::stringstream out;

    std::queue<std::pair<blokindex, std::string>> te_overlopen_paginas;

    out << "digraph {\n";

    if (!wortel.is_blad)
    {
        te_overlopen_paginas.emplace(wortelindex, wortel.dot_code());
    }

    out << "\"" << wortel.dot_code() << "\" [shape=rectangle] [label=\"" << wortel.dot_code() << "\"];\n";

    while (!te_overlopen_paginas.empty())
    {
        BKnoop ouder;
        schijf.lees(ouder, te_overlopen_paginas.front().first);
        std::string_view ouder_string = te_overlopen_paginas.front().second;

        for (int i = 0; i <= ouder.aantal_kinderen; i++)
        {
            BKnoop kind;
            schijf.lees(kind, ouder.index[i]);
            std::string kind_string = kind.dot_code();
            out << "\"" << kind_string << "\" [shape=rectangle] [label=\"" << kind_string << "\"];\n";
            out << "\"" << ouder_string << "\" -> \"" << kind_string << "\";\n";
            if (!kind.is_blad)
            {
                te_overlopen_paginas.emplace(ouder.index[i], kind_string);
            };
        }

        te_overlopen_paginas.pop();
    }

    out << "}\n";

    return out.str();
}

template <class Sleutel, class Data, blokindex m>
std::string BTree<Sleutel, Data, m>::BKnoop::dot_code() const
{
    std::stringstream out;
    // noot: voor debugdoelen is het vaak handig de indexen van de kinderen uit te schrijven
    // vervang dan volgende lijn door:
    // if (!isBlad){
    if (false)
    {
        out << "niet-blad: ";
        out << " (" << index[0] << ")";
        for (int i = 1; i <= aantal_kinderen; i++)
        {
            out << sleutel[i] << "(" << index[i] << ") ";
        }
    }
    else
    {
        out << "  ";
        for (int i = 1; i <= aantal_kinderen; i++)
        {
            out << sleutel[i] << "  ";
        }
    }

    return out.str();
}

template <class Sleutel, class Data, blokindex m>
BTree<Sleutel, Data, m>::BKnoop::BKnoop(bool is_blad) : aantal_kinderen{0}, is_blad{is_blad}
{
    crashtest++;

    // // Dit crasht als er een 4e knoop wordt aangemaakt
    // // Zie de limiet van 3 schijfknopen in het intern (RAM) geheugen in de opgave
    // int crashresult = 4 / (-4 + crashtest);

    if (crashtest > 3)
    {
        throw "Te veel knopen in het geheugen!";
    }
}

template <class Sleutel, class Data, blokindex m>
BTree<Sleutel, Data, m>::BKnoop::BKnoop() : BKnoop{true}
{
}

template <class Sleutel, class Data, blokindex m>
BTree<Sleutel, Data, m>::BKnoop::BKnoop(blokindex linkerkind, const Sleutel& sl, const Data& d, blokindex rechterkind)
: BKnoop{false}
{
    sleutel[1] = sl;
    data[1] = d;
    index[0] = linkerkind;
    index[1] = rechterkind;
    aantal_kinderen = 1;
}

template <class Sleutel, class Data, blokindex m>
BTree<Sleutel, Data, m>::BKnoop::~BKnoop()
{
    crashtest--;
}

template <class Sleutel, class Data, blokindex m>
std::pair<bool, int> BTree<Sleutel, Data, m>::BKnoop::is_aanwezig(const Sleutel& gezochte_sleutel) const
{
    int i = 1;

    while ((i <= aantal_kinderen) && (sleutel[i] != gezochte_sleutel) && (sleutel[i] < gezochte_sleutel))
    {
        i++;
    }

    return std::make_pair((sleutel[i] == gezochte_sleutel), i);
}

template <class Sleutel, class Data, blokindex m>
bool BTree<Sleutel, Data, m>::BKnoop::is_vol() const
{
    return (aantal_kinderen == m);
}

template <class Sleutel, class Data, blokindex m>
void BTree<Sleutel, Data, m>::BKnoop::voegtoe(const Sleutel& nieuwe_sleutel,
                                              const Data& nieuwe_data,
                                              blokindex nieuw_rechterkind)
{
    if (is_vol())
    {
        throw "Knoop zit al vol";
    }

    int i = aantal_kinderen;

    while (i > 0 && nieuwe_sleutel < sleutel[i])
    {
        sleutel[i + 1] = sleutel[i];
        data[i + 1] = data[i];
        index[i + 1] = index[i];

        i--;
    }
    i++;

    assert(sleutel[i] != nieuwe_sleutel);

    sleutel[i] = nieuwe_sleutel;
    data[i] = nieuwe_data;
    index[i] = nieuw_rechterkind; // linkerkind bestaat altijd al
    aantal_kinderen++;
}

template <class Sleutel, class Data, blokindex m>
void BTree<Sleutel, Data, m>::BKnoop::splits_knoop(BKnoop& nieuwe_broer_knoop,
                                                   Sleutel& middel_sleutel,
                                                   Data& middel_data)
{
    const int middel_pivot = static_cast<int>(std::ceil(static_cast<double>(aantal_kinderen) / 2));

    nieuwe_broer_knoop.is_blad = is_blad;

    middel_sleutel = sleutel[middel_pivot];
    middel_data = data[middel_pivot];

    if (!nieuwe_broer_knoop.is_blad)
    {
        nieuwe_broer_knoop.index[0] = std::move(index[middel_pivot]);
    }

    for (int i = middel_pivot + 1; i <= aantal_kinderen; i++)
    {
        nieuwe_broer_knoop.sleutel[i - middel_pivot] = std::move(sleutel[i]);
        nieuwe_broer_knoop.data[i - middel_pivot] = std::move(data[i]);

        if (!nieuwe_broer_knoop.is_blad)
        {
            nieuwe_broer_knoop.index[i - middel_pivot] = std::move(index[i]);
        }
    }

    nieuwe_broer_knoop.aantal_kinderen = (aantal_kinderen - middel_pivot);
    aantal_kinderen = (middel_pivot - 1);
}

template <class Sleutel, class Data, blokindex m>
typename BTree<Sleutel, Data, m>::iterator BTree<Sleutel, Data, m>::begin()
{
    return iterator{wortelindex, wortel, schijf, true};
}

template <class Sleutel, class Data, blokindex m>
typename BTree<Sleutel, Data, m>::iterator BTree<Sleutel, Data, m>::end()
{
    return iterator{wortelindex, wortel, schijf, false};
}

template <class Sleutel, class Data, blokindex m>
BTree<Sleutel, Data, m>::iterator::iterator(blokindex wortelindex,
                                            const BKnoop& wortel,
                                            Schijf<BKnoop>& schijf,
                                            bool is_initialised)
: wortelindex{wortelindex}, wortel{wortel}, schijf{schijf}, huidig_blok_index{wortelindex}, huidig_blok{wortel}
{
    if (is_initialised)
    {
        huidig_blok_index = wortelindex;
        huidig_blok = wortel;

        while (!huidig_blok.is_blad)
        {
            te_bezoeken_blokken.push(std::make_pair(huidig_blok_index, 0));
            huidig_blok_index = huidig_blok.index[0];
            schijf.lees(huidig_blok, huidig_blok_index);
        }

        huidig_sleutel_index = 1;

        huidige_waarde = std::make_unique<value_type>(huidig_blok.sleutel[huidig_sleutel_index],
                                                      huidig_blok.data[huidig_sleutel_index]);
    }
}
template <class Sleutel, class Data, blokindex m>
BTree<Sleutel, Data, m>::iterator::iterator(const iterator& andere)
: wortelindex{andere.wortelindex},
  wortel{andere.wortel},
  schijf{andere.schijf},
  te_bezoeken_blokken{andere.te_bezoeken_blokken},
  huidig_blok_index{andere.huidig_blok_index},
  huidig_sleutel_index{andere.huidig_sleutel_index},
  huidig_blok{andere.huidig_blok},
  huidige_waarde{std::make_unique<value_type>(value_type{*(andere.huidige_waarde)})}
{
}

template <class Sleutel, class Data, blokindex m>
typename BTree<Sleutel, Data, m>::iterator& BTree<Sleutel, Data, m>::iterator::operator++()
{
    if (huidig_blok.is_blad)
    {
        huidig_sleutel_index++;

        while (!te_bezoeken_blokken.empty() && (huidig_sleutel_index > huidig_blok.aantal_kinderen))
        {
            huidig_blok_index = te_bezoeken_blokken.top().first;
            huidig_sleutel_index = te_bezoeken_blokken.top().second;
            te_bezoeken_blokken.pop();

            if (huidig_blok_index == wortelindex)
            {
                huidig_blok = wortel;
            }
            else
            {
                schijf.lees(huidig_blok, huidig_blok_index);
            }

            huidig_sleutel_index++;
        }

        if (te_bezoeken_blokken.empty() && (huidig_sleutel_index > huidig_blok.aantal_kinderen))
        { // We zitten aan de wortel en die is volledig doorlopen
            huidige_waarde.reset();
            return (*this);
        }
    }
    else
    {
        te_bezoeken_blokken.push(std::make_pair(huidig_blok_index, huidig_sleutel_index));
        huidig_blok_index = huidig_blok.index[huidig_sleutel_index];

        if (huidig_blok_index == wortelindex)
        {
            huidig_blok = wortel;
        }
        else
        {
            schijf.lees(huidig_blok, huidig_blok_index);
        }

        while (!huidig_blok.is_blad)
        {
            te_bezoeken_blokken.push(std::make_pair(huidig_blok_index, 0));
            huidig_blok_index = huidig_blok.index[0];

            if (huidig_blok_index == wortelindex)
            {
                huidig_blok = wortel;
            }
            else
            {
                schijf.lees(huidig_blok, huidig_blok_index);
            }
        }

        huidig_sleutel_index = 1;
    }

    huidige_waarde = std::make_unique<value_type>(huidig_blok.sleutel[huidig_sleutel_index],
                                                  huidig_blok.data[huidig_sleutel_index]);

    return (*this);
}

template <class Sleutel, class Data, blokindex m>
typename BTree<Sleutel, Data, m>::iterator BTree<Sleutel, Data, m>::iterator::operator++(int)
{
    iterator tmp = (*this);
    ++*this;
    return tmp;
}

template <class Sleutel, class Data, blokindex m>
typename BTree<Sleutel, Data, m>::iterator::reference BTree<Sleutel, Data, m>::iterator::operator*()
{
    return (*huidige_waarde);
}

template <class Sleutel, class Data, blokindex m>
typename BTree<Sleutel, Data, m>::iterator::pointer BTree<Sleutel, Data, m>::iterator::operator->()
{
    return huidige_waarde.get();
}
template <class Sleutel, class Data, blokindex m>
bool BTree<Sleutel, Data, m>::iterator::operator==(const iterator& andere) const
{
    if (!huidige_waarde && !(andere.huidige_waarde))
    {
        // Both pointers don't exist
        return true;
    }
    else if (static_cast<bool>(huidige_waarde) != static_cast<bool>(andere.huidige_waarde))
    {
        // One of the two pointers doesn't exist
        return false;
    }
    else
    {
        // Both pointers exist
        return (*huidige_waarde == *(andere.huidige_waarde));
    }
}
template <class Sleutel, class Data, blokindex m>
bool BTree<Sleutel, Data, m>::iterator::operator!=(const iterator& andere) const
{
    return !((*this) == andere);
}

template <class Sleutel, class Data, blokindex m>
void swap(typename BTree<Sleutel, Data, m>::iterator& first, typename  BTree<Sleutel, Data, m>::iterator& second)
{
    using std::swap;

    swap(first.wortelindex, second.wortelindex);
    swap(first.wortel, second.wortel);
    swap(first.schijf, second.schijf);
    swap(first.te_bezoeken_blokken, second.te_bezoeken_blokken);
    swap(first.huidig_blok_index, second.huidig_blok_index);
    swap(first.huidig_sleutel_index, second.huidig_sleutel_index);
    swap(first.huidig_blok, second.huidig_blok);
    swap(first.huidige_waarde, second.huidige_waarde);
}

template <class Sleutel, class Data, blokindex m>
typename BTree<Sleutel, Data, m>::iterator& BTree<Sleutel, Data, m>::iterator::operator=(const iterator& andere)
{
    iterator temp(andere);
    swap(*this, temp);

    return (*this);
}

#endif