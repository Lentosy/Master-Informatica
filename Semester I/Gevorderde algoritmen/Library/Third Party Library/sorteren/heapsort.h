#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "sorteermethode.h"

#include <random>
#include <vector>

template <typename T>
class HeapSort : public Sorteermethode<T>
{
public:
    void operator()(std::vector<T>& v) const;

private:
    int get_left_child_index(int i) const;
    int get_right_child_index(int i) const;
    void max_heapify(std::vector<T>& v, int i, int heap_size) const;
    void build_max_heap(std::vector<T>& v) const;
};

template <typename T>
void HeapSort<T>::operator()(std::vector<T>& v) const
{
    build_max_heap(v);

    for (int i = (v.size()-1); i > 0; i--)
    {
        std::swap(v[0], v[i]);
        max_heapify(v, 0, i);
    }
}

template <typename T>
int HeapSort<T>::get_left_child_index(int i) const
{
    return ((2 * i) + 1);
}

template <typename T>
int HeapSort<T>::get_right_child_index(int i) const
{
    return ((2 * i) + 2);
}

template <typename T>
void HeapSort<T>::max_heapify(std::vector<T>& v, int i, int heap_size) const
{
    const int l = get_left_child_index(i);
    const int r = get_right_child_index(i);
    int largest = i;

    if (l < heap_size && v[l] > v[largest])
    {
        largest = l;
    }

    if (r < heap_size && v[r] > v[largest])
    {
        largest = r;
    }

    if (largest != i)
    {
        std::swap(v[largest], v[i]);
        max_heapify(v, largest, heap_size);
    }
}

template <typename T>
void HeapSort<T>::build_max_heap(std::vector<T>& v) const
{
    const int largest_index_with_children = ((v.size() / 2) - 1);

    for (int i = largest_index_with_children; i >= 0; i--)
    {
        max_heapify(v, i, v.size());
    }
}

#endif
