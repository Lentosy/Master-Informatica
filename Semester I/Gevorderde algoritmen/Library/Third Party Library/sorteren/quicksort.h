#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "sorteermethode.h"

#include <random>
#include <vector>

template <typename T>
class QuickSort : public Sorteermethode<T>
{
public:
    void operator()(std::vector<T>& v) const;

protected:
    void sort_rec(std::vector<T>& v, int l, int r) const;
    int partition(std::vector<T>& v, int l, int r) const;
    static void place_pivot_left(std::vector<T>& v, int l, int r);
    static void place_median_of_3_left(std::vector<T>& v, int a, int b, int c);
};

template <typename T>
void QuickSort<T>::operator()(std::vector<T>& v) const
{
    sort_rec(v, 0, v.size());
}

template <typename T>
void QuickSort<T>::sort_rec(std::vector<T>& v, int l, int r) const
{
    if (l >= (r - 1))
    {
        return;
    }

    int q = partition(v, l, r);
    sort_rec(v, l, (q + 1));
    sort_rec(v, (q + 1), r);
}

template <typename T>
int QuickSort<T>::partition(std::vector<T>& v, int l, int r) const
{
    place_pivot_left(v, l, r);
    T pivot = v[l];

    int i = l;
    int j = (r - 1);

    while (v[j] > pivot)
    {
        j--;
    }

    while (i < j)
    {
        std::swap(v[i], v[j]);

        i++;
        while (v[i] < pivot)
        {
            i++;
        }

        j--;
        while (v[j] > pivot)
        {
            j--;
        }
    }

    return j;
}

template <typename T>
void QuickSort<T>::place_pivot_left(std::vector<T>& v, int l, int r)
{
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<int> dis{l, (r - 1)};

    int a = dis(rd);
    int b = dis(rd);
    int c = dis(rd);

    place_median_of_3_left(v, a, b, c);
}

template <typename T>
void QuickSort<T>::place_median_of_3_left(std::vector<T>& v, int a, int b, int c)
{
    if (v[a] > v[b])
    {
        std::swap(v[a], v[b]);
    }

    if (v[b] > v[c])
    {
        std::swap(v[b], v[c]);
    }

    if (v[a] > v[b])
    {
        std::swap(v[a], v[b]);
    }

    std::swap(v[a], v[b]);
}

#endif
