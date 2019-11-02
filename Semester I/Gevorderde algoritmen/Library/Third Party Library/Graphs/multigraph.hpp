#ifndef MULTIGRAPH_HPP
#define MULTIGRAPH_HPP
#include <vector>
#include <map>
#include <stack>
#include <iostream>

enum DirectionType
{
    DIRECTED,
    UNDIRECTED
};

class GraphException : public std::logic_error
{
  public:
    GraphException(const std::string &message_) : std::logic_error(message_)
    {
    }
};

std::ostream &operator<<(std::ostream &os, const GraphException &exc)
{
    return os << exc.what();
}
template <DirectionType RT>
class MultiGraph
{
    typedef std::map<int, std::vector<int>> Knoop; // beeldt knoopnummer (van buur) af op de verbindingsnummerS

  public:
    MultiGraph(int aantalKnopen);
    MultiGraph(const MultiGraph<RT> &graaf);
    bool isDirected() const;
    virtual int voegKnoopToe();
    virtual int voegVerbindingToe(int van, int naar);
    virtual void verwijderVerbinding(int van, int naar);
    int aantalKnopen() const;
    int aantalVerbindingen() const;
    const std::vector<int> &verbindingsnummers(int van, int naar) const;
    virtual void wis();

    const Knoop &operator[](int i) const { return knopen[i]; }
    Knoop &operator[](int i) { return knopen[i]; }

    virtual void schrijf(std::ostream &os) const;
    virtual void schrijfKnoop(std::ostream &os, int k) const;

  protected:
    void controleerKnoopnummer(int k) const; // throw indien k ongeldig
    void voegVerbindingToeInDatastructuur(int van, int naar, int verbindingsnummer);
    void verwijderVerbindingUitDatastructuur(int van, int naar);

  private:
    std::vector<Knoop> knopen;
    int hoogsteVerbindingsnummer;
    std::stack<int> vrijgekomenVerbindingsnummers;
};

//Overloaden van de output operator
template <DirectionType RT>
std::ostream &operator<<(std::ostream &os, const MultiGraph<RT> &g)
{
    g.schrijf(os);
    return os;
}

//Default Constructor
template <DirectionType RT>
MultiGraph<RT>::MultiGraph(int n) : knopen(n), hoogsteVerbindingsnummer(0) {}
//Copy constructor
template <DirectionType RT>
MultiGraph<RT>::MultiGraph(const MultiGraph<RT> &graaf) : knopen(graaf.knopen), hoogsteVerbindingsnummer(graaf.hoogsteVerbindingsnummer), vrijgekomenVerbindingsnummers(graaf.vrijgekomenVerbindingsnummers) {}
//Getter om na te gaan of de graaf DIRECTED of UNDIRECTED is
template <>
bool MultiGraph<DIRECTED>::isDirected() const { return true; }
template<>
bool MultiGraph<UNDIRECTED>::isDirected() const { return false; }
//Toevoegen van een knoop. Geeft de knoopnr terug.
template <DirectionType RT>
int MultiGraph<RT>::voegKnoopToe()
{
    int n = knopen.size();
    knopen.resize(n + 1); // default constructor voor nieuwe knoop wordt opgeroepen (hier lege map)
    return n;
}
//Toevoegen van een verbinding. Geeft de verbindingsnummer terug.
template <DirectionType RT>
int MultiGraph<RT>::voegVerbindingToe(int van, int naar)
{
    controleerKnoopnummer(van);
    controleerKnoopnummer(naar);

    int verbindingsnummer;
    if (!vrijgekomenVerbindingsnummers.empty())
    {
        verbindingsnummer = vrijgekomenVerbindingsnummers.top();
        vrijgekomenVerbindingsnummers.pop();
    }
    else
        verbindingsnummer = hoogsteVerbindingsnummer++;
    voegVerbindingToeInDatastructuur(van, naar, verbindingsnummer);
    return verbindingsnummer;

    return 0;
}
//Verwijderen van een verbinding.
template <DirectionType RT>
void MultiGraph<RT>::verwijderVerbinding(int van, int naar)
{
    controleerKnoopnummer(van);
    controleerKnoopnummer(naar);
    if (knopen[van].find(naar) != knopen[van].end())
    { //verbinding bestaat
        vrijgekomenVerbindingsnummers.push(knopen[van][naar][0]);
        verwijderVerbindingUitDatastructuur(van, naar);
    }
    // (geen exception indien verbinding niet bestaat)
}
//Getter van het aantal knopen
template <DirectionType RT>
int MultiGraph<RT>::aantalKnopen() const { return knopen.size(); }
//Getter van het aantal verbindingen
template <DirectionType RT>
int MultiGraph<RT>::aantalVerbindingen() const
{
    return hoogsteVerbindingsnummer - vrijgekomenVerbindingsnummers.size();
}
//Getter om de verbinding(en) tussen twee bepaalde knopen
template <DirectionType RT>
const std::vector<int> &MultiGraph<RT>::verbindingsnummers(int van, int naar) const
{
    controleerKnoopnummer(van);
    controleerKnoopnummer(naar);
    auto verbindingit = knopen[van].find(naar);

    if (verbindingit == knopen[van].end())
    {
        //knopen[van][naar] = std::vector<int>();
        //return knopen[van][naar];
        return std::vector<int>();
    }
    else
    {
        return verbindingit->second;
    }
}
//Maak de hele multigraaf leeg
template <DirectionType RT>
void MultiGraph<RT>::wis()
{
    knopen.clear();
    hoogsteVerbindingsnummer = 0;
    while (!vrijgekomenVerbindingsnummers.empty())
        vrijgekomenVerbindingsnummers.pop();
}
//Uitschrijven van de graaf
template <DirectionType RT>
void MultiGraph<RT>::schrijf(std::ostream &os) const
{
    os << "MultiGraph: " << aantalKnopen() << " knopen en "
       << aantalVerbindingen() << " verbindingen:" << std::endl;
    for (int k = 0; k < aantalKnopen(); k++)
        schrijfKnoop(os, k);
}
//Uitschrijven van een knoop
template <DirectionType RT>
void MultiGraph<RT>::schrijfKnoop(std::ostream &os, int k) const
{
    os << "knoop " << k << ":" << std::endl;
    for (auto it = knopen[k].begin(); it != knopen[k].end(); ++it)
    {
        os << "  ->" << it->first << " (" << it->second.size() << ") via ";
        for (int i = 0; i < it->second.size(); i++)
            os << (it->second)[i] << " ";
        os << std::endl;
    }
}
//Controleren van het knoopnummer
template <DirectionType RT>
void MultiGraph<RT>::controleerKnoopnummer(int k) const
{
    if (k < 0 || (size_t)k >= knopen.size())
        throw GraphException("ongeldig knoopnummer");
}

//Hulpfuncties die de verbinding ook effectief toevoegt/verwijdert in de datastructuur
template <>
void MultiGraph<DIRECTED>::voegVerbindingToeInDatastructuur(int van, int naar, int verbindingsnummer)
{
    knopen[van][naar].push_back(verbindingsnummer);
}

template <>
void MultiGraph<UNDIRECTED>::voegVerbindingToeInDatastructuur(int van, int naar, int verbindingsnummer)
{
    knopen[van][naar].push_back(verbindingsnummer);
    knopen[naar][van].push_back(verbindingsnummer);
}

template <>
void MultiGraph<DIRECTED>::verwijderVerbindingUitDatastructuur(int van, int naar)
{
    knopen[van][naar].pop_back(); //Maakt niet uit welke van de verbindingen je wegdoet
}

template <>
void MultiGraph<UNDIRECTED>::verwijderVerbindingUitDatastructuur(int van, int naar)
{
    knopen[van][naar].pop_back();
    knopen[naar][van].pop_back();
    if (knopen[van][naar].empty())
    {
        knopen[van].erase(naar);
        knopen[naar].erase(van);
    }
}

#endif