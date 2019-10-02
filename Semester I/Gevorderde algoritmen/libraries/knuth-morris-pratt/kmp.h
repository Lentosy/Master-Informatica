
#ifndef KMP_H
#define KMP_H

#include <cassert>
#include <queue>
#include <string_view>
#include <vector>

class KnuthMorrisPratt
{
public:
    KnuthMorrisPratt(const std::string_view& naald);

    std::queue<int> zoek(const std::string_view& hooiberg, bool gebruik_prefix = false) const;
    std::vector<int> geef_prefix_tabel() const;
    std::vector<int> geef_kmp_tabel() const;

    std::string to_string() const;

private:
    std::string_view naald;
    std::vector<int> prefix_tabel;
    std::vector<int> kmp_tabel;
};

KnuthMorrisPratt::KnuthMorrisPratt(const std::string_view& naald)
: naald{naald}, prefix_tabel((naald.size() + 1), -1), kmp_tabel(prefix_tabel)
{
    assert(!naald.empty());

    prefix_tabel[1] = 0;
    for (size_t i = 2; i < prefix_tabel.size(); ++i)
    {
        int prefix_lengte = prefix_tabel[i - 1];

        while ((prefix_lengte >= 0) && (naald[i - 1] != naald[prefix_lengte]))
        {
            prefix_lengte = prefix_tabel[prefix_lengte];
        }

        prefix_tabel[i] = prefix_lengte + 1;
    }

    kmp_tabel = prefix_tabel;

    // Extra heuristiek in de cursus
    // Zie CLRS 32.4-6 op p. 1012 of Gusfield op p. 51
    for (int i = 2; i < naald.size(); ++i)
    {
        if (kmp_tabel[i] > 0 && kmp_tabel[i + 1] == kmp_tabel[i] + 1)
        {
            kmp_tabel[i] = kmp_tabel[kmp_tabel[i]];
        }
    }
}

std::queue<int> KnuthMorrisPratt::zoek(const std::string_view& hooiberg, bool gebruik_prefix) const
{
    if (hooiberg.empty())
    {
        return std::queue<int>{};
    }

    std::vector<int> tabel;

    if (gebruik_prefix)
    {
        tabel = prefix_tabel;
    }
    else
    {
        tabel = kmp_tabel;
    }

    std::queue<int> gevonden;

    int prefix_lengte = 0;
    for (int i = 1; i <= (hooiberg.size() - naald.length()); i++)
    // Let op de <= in de for-voorwaarde! bv. "aba" zoeken in "ababa"
    {
        while ((prefix_lengte >= 0) && (hooiberg[i - 1] != naald[prefix_lengte]))
        {
            prefix_lengte = tabel[prefix_lengte];
        }
        prefix_lengte++;

        if (prefix_lengte == naald.size())
        {
            gevonden.push(i - naald.size());
        }
    }

    return gevonden;
}

std::vector<int> KnuthMorrisPratt::geef_prefix_tabel() const
{
    return prefix_tabel;
}

std::vector<int> KnuthMorrisPratt::geef_kmp_tabel() const
{
    return kmp_tabel;
}

#endif
