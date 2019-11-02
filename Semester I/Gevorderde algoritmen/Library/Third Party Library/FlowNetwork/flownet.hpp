#ifndef FLOWNET_HPP
#define FLOWNET_HPP

#include <cassert>
#include <sstream>
#include <string>

#include "../Graphs/graph.hpp"
#include "vergrotendpad.hpp"
#include "volgendpadzoeker.hpp"

/**********************************************************************
   Class: Stroomnetwerk
   beschrijving: Een stroomnetwerk gaat uit van een gewogen gerichte graaf
                 die in de constructor wordt opgegeven
***************************************************************************/

template <class T> // T = takdata
class Stroomnetwerk : public GraphWithEdgeData<DIRECTED, T>
{
public:
    // Graph<DIRECTED>(gr) moet toegevoegd, anders roept de copyconstructor van GraphWithEdgeData de defaultconstructor van
    // Graph op en krijgen we een lege graaf.
    Stroomnetwerk<T>(const GraphWithEdgeData<DIRECTED, T>& graaf);
    Stroomnetwerk<T>(const GraphWithEdgeData<DIRECTED, T>& graaf,
                     int producent,
                     int verbruiker,
                     VolgendPadZoeker<T>* padzoeker);
    // Geen unique_ptr voor padzoeker:
    // https://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters/ en
    // https://stackoverflow.com/questions/8114276/how-do-i-pass-a-unique-ptr-argument-to-a-constructor-or-a-function

    Stroomnetwerk<T>() = delete;
    virtual ~Stroomnetwerk<T>() = default;

    Stroomnetwerk<T>(const Stroomnetwerk<T>& ander) = default;
    Stroomnetwerk<T>& operator=(const Stroomnetwerk<T>& ander) = default;

    Stroomnetwerk<T>(Stroomnetwerk<T>&& ander) = default;
    Stroomnetwerk<T>& operator=(Stroomnetwerk<T>&& ander) = default;

    void updateStroomnetwerk(Stroomnetwerk<T>& stroomnetwerk, const Pad<T>& vergrotendpad);
    void updateRestnetwerk(Stroomnetwerk<T>& restnetwerk, const Pad<T>& vergrotendpad);

    std::string genereer_dot_code() const;
    T geef_capaciteit() const;

protected:
    int producent;
    int verbruiker;

private:
    void voegStroomToe(int van, int naar, int stroom);
};

template <class T>
Stroomnetwerk<T>::Stroomnetwerk(const GraphWithEdgeData<DIRECTED, T>& graaf)
    : Graph<DIRECTED>{graaf}, GraphWithEdgeData<DIRECTED, T>{graaf}
{
}

template <class T>
Stroomnetwerk<T>::Stroomnetwerk(const GraphWithEdgeData<DIRECTED, T>& graaf,
                                int producent,
                                int verbruiker,
                                VolgendPadZoeker<T>* padzoeker)
    : Graph<DIRECTED>{graaf.numberOfVertices()}, producent{producent}, verbruiker{verbruiker}
{
    Stroomnetwerk<T> restnetwerk{graaf};

    Pad<T> vergrotendpad = padzoeker->zoek_volgend_vergrotend_pad(restnetwerk, producent, verbruiker);
    while (vergrotendpad.size() > 0)
    {
        // += en -= hebben niets met elkaar te maken. Het een is voor het stroomnetwerk (enkel aanpassen takdata), het
        // ander voor het restnetwerk (aanpassen takdata en verbindingen). Je kan eventueel ook andere functienamen
        // gebruiken zoals updateStroomnetwerk en updateRestnetwerk
        //
        // restnetwerk -= vergrotendpad;
        // *this += vergrotendpad;
        updateRestnetwerk(restnetwerk, vergrotendpad);
        updateStroomnetwerk(*this, vergrotendpad);
        vergrotendpad = padzoeker->zoek_volgend_vergrotend_pad(restnetwerk, producent, verbruiker);
    }
}

template <class T>
void Stroomnetwerk<T>::voegStroomToe(int van, int naar, int stroom)
{
    if (this->edgeNumber(van, naar) == -1)
    {
        this->insertEdge(van, naar, stroom);
    }
    else
    {
        *(this->getEdgeData(van, naar)) += stroom;
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

        if (this->edgeNumber(naar, van) == -1)
        {
            stroomnetwerk.voegStroomToe(van, naar, toe_te_voegen_stroom);
        }
        else
        {
            T* terugstroom = stroomnetwerk.getEdgeData(naar, van);

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

        assert(restnetwerk.edgeNumber(van, naar) != -1);

        T* heenstroom = restnetwerk.getEdgeData(van, naar);

        assert(*heenstroom >= vergrotendpad.geef_capaciteit());
        *heenstroom -= vergrotendpad.geef_capaciteit();

        if (*heenstroom == 0)
        {
            restnetwerk.removeEdge(van, naar);
        }

        restnetwerk.voegStroomToe(naar, van, vergrotendpad.geef_capaciteit());
    }
}

template <class T>
std::string Stroomnetwerk<T>::genereer_dot_code() const
{
    std::stringstream out;

    out << "digraph stroomnetwerk {" << std::endl;

    for (int i = 0; i < this->numberOfVertices(); i++)
    {
        const auto& knoop = (*this)[i];

        for (const auto& it : knoop)
        {
            out << "\t" << i << " -> " << it.first << " [label=\"" << *(this->getEdgeData(i, it.first)) << "\"];"
                << std::endl;
        }
    }

    out << "}" << std::endl;

    return out.str();
}

template <class T>
T Stroomnetwerk<T>::geef_capaciteit() const
{
    T som_capaciteiten = static_cast<T>(0);

    for (const auto& it : (*this)[producent])
    {
        const T* capaciteit = this->getEdgeData(producent, it.first);

        if (capaciteit)
        {
            som_capaciteiten += *capaciteit;
        }
    }

    return som_capaciteiten;
}

#endif