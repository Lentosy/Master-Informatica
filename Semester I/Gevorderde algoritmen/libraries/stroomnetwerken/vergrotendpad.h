#ifndef VERGROTENDPAD_H
#define VERGROTENDPAD_H

#include <sstream>
#include <string>
#include <vector>

template <class T>
class Pad : public std::vector<int>
{
public:
    T geef_capaciteit() const;
    void set_capaciteit(const T& capaciteit);
    std::string to_string() const;

protected:
    T capaciteit;
};

template <class T>
T Pad<T>::geef_capaciteit() const
{
    return capaciteit;
}

template <class T>
void Pad<T>::set_capaciteit(const T& capaciteit)
{
    this->capaciteit = capaciteit;
}

template <class T>
std::string Pad<T>::to_string() const
{
    std::stringstream out;

    if (!empty())
    {
        for (const T& knoopnr : (*this))
        {
            out << knoopnr << ", ";
        }
    }
    else
    {
        out << "leeg";
    }
    out << "(capaciteit: " << capaciteit << ")";

    return out.str();
}

#endif
