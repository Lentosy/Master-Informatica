#ifndef __SORTVECTOR_HPP
#define __SORTVECTOR_HPP
/**
 * A Sortvector class, a templated vector meant to be sorted
 * with operations to fill, reverse, test or show it * 
 * */
#include <iostream>
using std::cout;
using std::endl;
using std::istream;
using std::move;
using std::ostream;
using std::swap;
#include <iomanip>
using std::setw;
#include <cstdlib>
#include <vector>
using std::vector;
#include <map>
using std::map;

template <class T>
class Sortvector : public vector<T>
{
  public:
    // The constructor takes a size argument, the vector will be randomly filled
    Sortvector(int);

    // Constructor inheritance from vector is required if you want to be able to write expressions like
    // Sortvector(int size): vector<T>(size)
    using vector<T>::vector;

    // We only ever intend to create and sort a vector, no copying or moving them
    Sortvector(const Sortvector<T> &v) = delete;
    Sortvector<T> &operator=(const Sortvector<T> &v) = delete;
    Sortvector<T> &operator=(Sortvector<T> &&v) = delete;
    Sortvector(Sortvector<T> &&v) = delete;

    // fill_sequential fills all available slots of the vector with values, by calling this constructor sequence
    // T(0)..T(size()-1)
    void fill_sequential();
    void reverse();
    void fill_reverse();
    // Knuth-Fisher-Yates shuffle strategy
    void shuffle();

    void fill_random_no_duplicates();
    void fill_random();

    bool is_sorted() const;
    // is_sequential checks whether *this looks like the result of calling fill_sequential(), meaning for every i (*this)[i]==T(i)
    bool is_sequential() const;

    friend ostream &operator<<(ostream &os, const Sortvector<T> &s)
    {
        s.print(os);
        return os;
    }

  private:
    void print(ostream &os) const;
};

template <class T>
Sortvector<T>::Sortvector(int grootte) : vector<T>(grootte)
{
    fill_sequential();
}

template <class T>
void Sortvector<T>::fill_sequential()
{
    for (int i = 0; i < this->size(); i++)
    {
        this->at(i) = T(i);
    }
}

template <class T>
void Sortvector<T>::reverse()
{
    for (int i = 0; i < this->size() / 2; i++)
    {
        swap(this->at(i), this->at(this->size() - 1 - i));
    }
}

template <class T>
void Sortvector<T>::fill_reverse()
{
    for (int i = this->size() - 1; i >= 0; i--)
    {
        this->at(i) = T(i);
    }
}

template <class T>
void Sortvector<T>::shuffle()
{
    /// \fn -- To shuffle an array a of n elements (indices 0..n-1):
    /// for i from n−1 downto 1 do
    ///     j ← random integer such that 0 ≤ j ≤ i
    ///     exchange a[j] and a[i]
    int j;
    for (int i = this->size() - 1; i >= 1; i--)
    {
        j = rand() % i;
        swap(this->at(i), this->at(j));
    }
}

template <class T>
void Sortvector<T>::fill_random()
{
    for (int i = 0; i < this->size(); i++)
    {
        this->at(i) = T(rand());
    }
}

template <class T>
void Sortvector<T>::fill_random_no_duplicates()
{
    map<int, bool> present;
    int tmp;
    for (int i = 0; i < this->size(); i++)
    {
        tmp = rand() % this->size();
        while (present.find(tmp) != present.end())
        {
            tmp = rand() % this->size();
        }
        this->at(i) = T(tmp);
        present[tmp] = true;
    }
}

template <class T>
bool Sortvector<T>::is_sorted() const
{
    bool is_sorted = true;
    for (int i = 0; is_sorted && i < this->size() - 1; i++)
    {
        if ((*this)[i] > (*this)[i + 1])
            is_sorted = false;
    }
    return is_sorted;
}

template <class T>
bool Sortvector<T>::is_sequential() const
{
    bool is_sequential = true;
    for (int i = 0; is_sequential && i < this->size(); i++)
    {
        if ((*this)[i] != T(i))
            is_sequential = false;
    }
    return is_sequential;
}

template <class T>
void Sortvector<T>::print(ostream &os) const
{
    for (const auto &t : *this)
    {
        os << t << " ";
    }
    os << "\n";
}
#endif