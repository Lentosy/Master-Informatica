
#ifndef KMP_HPP
#define KMP_HPP

#include <cassert>
#include <iomanip>
 #include <iostream> // DEBUG
#include <limits>
#include <queue>
#include <sstream>
#include <vector>

class KnuthMorrisPratt
{
public:
    KnuthMorrisPratt() = delete;
    KnuthMorrisPratt(const std::string& naald);
    virtual ~KnuthMorrisPratt() = default;

    KnuthMorrisPratt(const KnuthMorrisPratt& andere) = default;
    KnuthMorrisPratt& operator=(const KnuthMorrisPratt& andere) = default;

    KnuthMorrisPratt(KnuthMorrisPratt&& andere) = default;
    KnuthMorrisPratt& operator=(KnuthMorrisPratt&& andere) = default;

    std::queue<int> zoek_prefixmethode(const std::string& hooiberg) const;
    std::queue<int> zoek_kmp(const std::string& hooiberg) const;

    std::string to_string() const;

private:
    std::queue<int> zoek(const std::string& hooiberg, std::vector<int> tabel) const;

    std::string naald;
    std::vector<int> prefix_tabel;
    std::vector<int> kmp_tabel;
};

KnuthMorrisPratt::KnuthMorrisPratt(const std::string& naald)
    : naald{naald}, prefix_tabel((naald.size() + 1), -1), kmp_tabel((naald.size() + 1), -1)
{
    assert(!naald.empty());

    int prefix_lengte = -1; // == prefix_tabel[0]
    for (size_t i = 1; i < prefix_tabel.size(); i++)
    {
        // on iteration 1 this path is never taken, instead we increase prefix_lengte to 0 and fill prefix_tabel[1] with 0
        // meaning we are using 1-indexed arrays and the first spot in the prefix table is always 0, since the pattern has no proper prefixes or suffixes at index 1
        while ((prefix_lengte >= 0) && (naald[i - 1] != naald[prefix_lengte]))
        {
            prefix_lengte = prefix_tabel[prefix_lengte];
        }

        prefix_lengte++;
        prefix_tabel[i] = prefix_lengte;
    }

    // Extra heuristiek in de cursus
    // Zie CLRS 32.4-6 op p. 1012 of Gusfield op p. 51
    for (size_t i = 1; i < kmp_tabel.size(); i++)
    {
        if (prefix_tabel[i] == 0)
        {
            kmp_tabel[i] = 0;
        }
        else if (naald[i] != naald[prefix_tabel[i]])
        {
            kmp_tabel[i] = prefix_tabel[i];
        }
        else
        {
            kmp_tabel[i] = kmp_tabel[prefix_tabel[i]];
        }
    }

    for(int i = 0; i < prefix_tabel.size(); i++){
        std::cout << prefix_tabel[i] << " | ";
    }
    std::cout << "\n";
        for(int i = 0; i < kmp_tabel.size(); i++){
        std::cout << kmp_tabel[i] << " | ";
    }
}

std::queue<int> KnuthMorrisPratt::zoek(const std::string& hooiberg, std::vector<int> tabel) const
{
    if (hooiberg.empty())
    {
        return std::queue<int>{};
    }

    // int aantal = 0; // DEBUG

    std::queue<int> gevonden;

    int prefix_lengte = 0;
    for (size_t i = 1; i <= hooiberg.size(); i++) // Let op de <= in de for-voorwaarde! bv. "aba" zoeken in "ababa"
    {
        while ((prefix_lengte >= 0) && (hooiberg[i - 1] != naald[prefix_lengte]))
        {
            prefix_lengte = tabel[prefix_lengte];
            // aantal++; // DEBUG
        }

        prefix_lengte++;

        assert(prefix_lengte <= std::numeric_limits<int>::max());
        if (prefix_lengte == static_cast<int>(naald.size()))
        {
            gevonden.push(i - naald.size());
            prefix_lengte = tabel[prefix_lengte]; // Is dit nodig? Zie CLRS
        }
    }

    // std::cout << "aantal:" << aantal << std::endl; // DEBUG

    return gevonden;
}

std::queue<int> KnuthMorrisPratt::zoek_prefixmethode(const std::string& hooiberg) const
{
    if (hooiberg.empty())
    {
        return std::queue<int>{};
    }

    return zoek(hooiberg, prefix_tabel);
}

std::queue<int> KnuthMorrisPratt::zoek_kmp(const std::string& hooiberg) const
{
    if (hooiberg.empty())
    {
        return std::queue<int>{};
    }

    return zoek(hooiberg, kmp_tabel);
}

std::string KnuthMorrisPratt::to_string() const
{
    std::stringstream out;
    constexpr int LEGENDE_BREEDTE = 16;
    constexpr int BREEDTE = 4;

    out << std::setw(LEGENDE_BREEDTE) << "Indexen";
    for (size_t i = 0; i < prefix_tabel.size(); i++)
    {
        out << std::setw(BREEDTE) << i;
    }
    out << std::endl;

    out << std::setw(LEGENDE_BREEDTE) << "Naald";
    for (const auto& c : naald)
    {
        out << std::setw(BREEDTE) << c;
    }
    out << std::endl;

    out << std::setw(LEGENDE_BREEDTE) << "Prefix tabel";
    for (const auto& prefix : prefix_tabel)
    {
        out << std::setw(BREEDTE) << prefix;
    }
    out << std::endl;

    out << std::setw(LEGENDE_BREEDTE) << "KMP tabel";
    for (const auto& prefix : kmp_tabel)
    {
        out << std::setw(BREEDTE) << prefix;
    }
    out << std::endl;

    return out.str();
}
#endif