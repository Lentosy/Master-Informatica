
#ifndef OPTIMIZED_MERGESORT_H
#define OPTIMIZED_MERGESORT_H

#include "sorteermethode.h"

template <typename T>
class OptimizedMergeSort : public Sorteermethode<T>
{
public:
    void operator()(std::vector<T>& v) const override;

private:
    void mergesort(std::vector<T>& v, int l, int r, std::vector<T>& h, bool copy_to_original) const;
    void merge(std::vector<T>& v, int l, int m, int r, std::vector<T>& h) const;
};

template <typename T>
void OptimizedMergeSort<T>::operator()(std::vector<T>& v) const
{
    std::vector<T> h(v.size());
    mergesort(v, 0, v.size(), h, true);
}

template <typename T>
void OptimizedMergeSort<T>::mergesort(std::vector<T>& v, int l, int r, std::vector<T>& h, bool copy_to_original) const
{
    if (l >= (r - 1))
    {
        if (!copy_to_original)
        {
            std::swap(v[l], h[l]);
        }

        return;
    }
    else
    {
        int m = (l + (r - l) / 2);

        mergesort(h, l, m, v, !copy_to_original);
        mergesort(h, m, r, v, !copy_to_original);

        merge(v, l, m, r, h);
    }
}

template <typename T>
void OptimizedMergeSort<T>::merge(std::vector<T>& v, int l, int m, int r, std::vector<T>& h) const
{
    int h_left_i = l;
    int h_right_i = m;
    int res_i = l;

    while (h_right_i < r && h_left_i < m)
    {
        if (h[h_left_i] <= h[h_right_i])
        {
            v[res_i] = std::move(h[h_left_i]);
            h_left_i++;
        }
        else
        {
            v[res_i] = std::move(h[h_right_i]);
            h_right_i++;
        }

        res_i++;
    }

    while (h_right_i < r)
    {
        v[res_i] = std::move(h[h_right_i]);
        h_right_i++;
        res_i++;
    }

    while (h_left_i < m)
    {
        v[res_i] = std::move(h[h_left_i]);
        h_left_i++;
        res_i++;
    }
}

#endif
