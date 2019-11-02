#ifndef __SORTINGMETHODS_HPP
#define __SORTINGMETHODS_HPP
#include "sortvector.hpp"
#include "chrono.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>
using std::cout;
using std::endl;
using std::move;
using std::swap;
#include <algorithm> // for STL sort
#include <iomanip>   // setw
#include <climits>   // INT_MAX

template <typename T>
class Sortingmethod
{
  public:
    // The function operator
    virtual void operator()(vector<T> &v) const = 0;

    // \fn measure(int shortest, int longest, ostream& os) writes an overview to output stream os
    // listing the execution times of the sorting method *this.
    // The first column of the output has the following sequence: shortest vector, 10*shortest vector, 100*shortest vector, ... as long as this number is below the longest argument
    // The other columns show how long it took for the algorithm to sort
    // (1) a random table (vector)
    // (2) an already sorted table (vector)
    // (3) an inversely sorted table (vector)

    void measure(int shortest, int longest, ostream &os);
};
template <typename T>
void Sortingmethod<T>::measure(int shortest, int longest, ostream &os)
{
    Chrono chron;
    os << setw(10) << "length" << setw(10) << "random" << setw(12) << "sorted" << setw(12) << "inverted" << endl;

    for (int i = shortest; i <= longest; i *= 10)
    {
        Sortvector<T> vec(i);

        os << setw(10) << i;

        vec.fill_random();
        chron.start();
        (*this)(vec);
        chron.stop();
        os << setw(10) << chron.elapsed();

        chron.start();
        (*this)(vec);
        chron.stop();
        os << setw(12) << chron.elapsed();

        vec.reverse();
        chron.start();
        (*this)(vec);
        chron.stop();
        os << setw(12) << chron.elapsed();
        os << endl;
    }
}

/** 
 * STL sort 
*/
template <typename T>
class STLSort : public Sortingmethod<T>
{
  public:
    void operator()(vector<T> &v) const;
};

template <typename T>
void STLSort<T>::operator()(vector<T> &v) const
{
    sort(v.begin(), v.end());
}

/** 
 *  InsertionSort
*/
template <typename T>
class InsertionSort : public Sortingmethod<T>
{
  public:
    void operator()(vector<T> &v) const;
};

template <typename T>
void InsertionSort<T>::operator()(vector<T> &v) const
{
    for (int i = 1; i < v.size(); i++)
    {
        T h;
        h = move(v[i]);
        int j = i - 1;
        while (j >= 0 && h < v[j])
        {
            v[j + 1] = move(v[j]);
            j--;
        }
        v[j + 1] = move(h);
    }
}

/** 
 * Selectionsort
*/

template <typename T>
class SelectionSort : public Sortingmethod<T>
{
  public:
    void operator()(vector<T> &v) const;
};

template <typename T>
void SelectionSort<T>::operator()(vector<T> &v) const
{
    for (int i = v.size() - 1; i > 0; i--)
    {
        int maxindex = i;
        T temporary = move(v[i]);
        for (int j = 0; j < i; j++)
        {
            if (v[maxindex] < v[j])
            {
                maxindex = j;
            }
        }
        v[i] = move(v[maxindex]);
        v[maxindex] = move(temporary);
    }
}

/** 
 * Shellsort
*/

template <typename T>
class ShellSort : public Sortingmethod<T>
{
  public:
    void operator()(vector<T> &v) const;
};

template <typename T>
void ShellSort<T>::operator()(vector<T> &v) const
{
    // k follows the Tokuda sequence k=ceil(9*(9/4)^i-4)/5)
    vector<int> increments;
    int u = 0;
    while (std::ceil((9 * std::pow(9.0 / 4, u) - 4) / 5) < v.size() / 2)
    {
        increments.push_back(std::ceil((9 * std::pow(9.0 / 4, u) - 4) / 5));
        u++;
    }

    int k = increments[--u];
    while (k >= 1)
    {
        for (int i = k; i < v.size(); i++)
        {
            T h = move(v[i]);
            int j = i - k;
            while (j >= 0 && h < v[j])
            {
                v[j + k] = move(v[j]);
                j -= k;
            }
            v[j + k] = move(h);
        }
        k = increments[--u];
    }
}

template <typename T>
class TDMergeSort : public Sortingmethod<T>
{
  private:
    void mergesort(vector<T> &, int, int, vector<T> &) const;
    void merge(vector<T> &, int, int, int, vector<T> &) const;
    void merge_less_memory_efficient(vector<T> &, int, int, int, vector<T> &) const;

  public:
    void operator()(vector<T> &v) const;
};

template <typename T>
void TDMergeSort<T>::operator()(vector<T> &v) const
{
    vector<T> h((v.size() + 1) / 2);
    mergesort(v, 0, v.size(), h);
}

template <typename T>
void TDMergeSort<T>::mergesort(vector<T> &v, int left, int right, vector<T> &temporary) const
{
    if (left < right - 1)
    {
        int middle = left + (right - left) / 2;
        mergesort(v, left, middle, temporary);
        mergesort(v, middle, right, temporary);
        merge(v, left, middle, right, temporary);
    }
}
// old merge
template <typename T>
void TDMergeSort<T>::merge_less_memory_efficient(vector<T> &v, int left, int middle, int right, vector<T> &temporary) const
{
    int j = left;
    int li = left;
    int ri = middle;
    while (li < middle && ri < right)
    {
        if (v[li] < v[ri])
        {
            temporary[j++] = v[li++];
        }
        else
        {
            temporary[j++] = v[ri++];
        }
    }

    while (li < middle)
    {
        temporary[j++] = v[li++];
    }
    while (ri < right)
    {
        temporary[j++] = v[ri++];
    }
    for (int i = left; i < right; i++)
    {
        v[i] = move(temporary[i]);
    }
}
template <typename T>
void TDMergeSort<T>::merge(vector<T> &v, int left, int middle, int right, vector<T> &temporary) const
{
    temporary = {v.begin() + left, v.begin() + middle};
    int j = left;
    int ri = middle;
    middle -= left;
    int li = 0;

    while (li < middle && ri < right)
    {
        if (temporary[li] <= v[ri])
        {
            v[j++] = temporary[li++];
        }
        else
        {
            v[j++] = v[ri++];
        }
    }

    while (li < middle)
    {
        v[j++] = temporary[li++];
    }
    while (ri < right)
    {
        v[j++] = v[ri++];
    }
}

template <typename T>
class BUMergeSort : public Sortingmethod<T>
{
  private:
    void mergesort(vector<T> &, int, int, vector<T> &) const;
    void merge(vector<T> &, int, int, int, vector<T> &) const;

  public:
    void operator()(vector<T> &) const;
};

template <typename T>
void BUMergeSort<T>::operator()(vector<T> &v) const
{
    vector<T> h(v.size());
    mergesort(v, 0, v.size(), h);
}

template <typename T>
void BUMergeSort<T>::merge(vector<T> &v, int left, int middle, int right, vector<T> &temporary) const
{
    int j = left;
    int li = left;
    int ri = middle;
    while (li < middle && ri < right)
    {
        if (v[li] < v[ri])
        {
            temporary[j++] = v[li++];
        }
        else
        {
            temporary[j++] = v[ri++];
        }
    }

    while (li < middle)
    {
        temporary[j++] = v[li++];
    }
    while (ri < right)
    {
        temporary[j++] = v[ri++];
    }
    for (int i = left; i < right; i++)
    {
        v[i] = temporary[i];
    }
}

template <typename T>
void BUMergeSort<T>::mergesort(vector<T> &v, int left, int right, vector<T> &temporary) const
{
    for (int width = 1; width < v.size(); width = 2 * width)
    {
        for (int i = 0; i < v.size(); i = i + 2 * width)
        {
            merge(v, i, std::min(i + width, (int)v.size()), std::min(i + 2 * width, (int)v.size()), temporary);
        }
    }
}

template <typename T>
class QuicksortLpiv : public Sortingmethod<T>
{
  private:
    void quicksort(vector<T> &, int, int) const;

  public:
    void operator()(vector<T> &) const;
};

template <typename T>
void QuicksortLpiv<T>::quicksort(vector<T> &v, int l, int r) const
{
    if (l < r)
    {
        if (r - l > 1)
        {
            // selection trick
            int mid = l + (r - l) / 2;
            if (v[mid] < v[r])
            {
                swap(v[mid], v[r]);
            }
            if (v[l] < v[r])
            {
                swap(v[l], v[r]);
            }
            if (v[mid] < v[l])
            {
                swap(v[mid], v[l]);
            }            
        }
        T pivot = v[l];
        int i = l;
        int j = r;

        while (v[j] > pivot)
            j--;
        while (i < j)
        {
            swap(v[i], v[j]);
            i++;
            while (v[i] < pivot)
                i++;
            //j--;
            while (v[j] > pivot)
                j--;
        }
        quicksort(v, l, j);
        quicksort(v, j + 1, r);
    }
}

template <typename T>
void QuicksortLpiv<T>::operator()(vector<T> &v) const
{
    quicksort(v, 0, v.size() - 1);
}

template <typename T>
class QuicksortRpiv : public Sortingmethod<T>
{
  private:
    void quicksort(vector<T> &, int, int) const;

  public:
    void operator()(vector<T> &) const;
};

template <typename T>
void QuicksortRpiv<T>::quicksort(vector<T> &v, int l, int r) const
{
    if (l < r)
    {
        if (r - l > 1)
        {
            // selection trick
            int mid = l + (r - l) / 2;
            if (v[mid] < v[l])
            {
                swap(v[mid], v[l]);
            }
            if (v[r] < v[l])
            {
                swap(v[r], v[l]);
            }
            if (v[mid] < v[r])
            {
                swap(v[mid], v[r]);
            }
        }
        T pivot = v[r];
        int i = l;
        int j = r;
        while (v[i] < pivot)
            i++;
        while (i < j)
        {
            swap(v[i], v[j]);
            j--;
            while (v[j] > pivot)
                j--;
            i++;
            while (v[i] < pivot)
                i++;
        }
        quicksort(v, l, i - 1);
        quicksort(v, i, r);
    }
}

template <typename T>
void QuicksortRpiv<T>::operator()(vector<T> &v) const
{
    quicksort(v, 0, v.size() - 1);
}

template <typename T>
class DualPivotQuicksort : public Sortingmethod<T>
{
  private:
    void quicksort(vector<T> &, int, int) const;

  public:
    void operator()(vector<T> &) const;
};

template <typename T>
void DualPivotQuicksort<T>::operator()(vector<T> &v) const
{
    quicksort(v, 0, v.size() - 1);
}

template <typename T>
void DualPivotQuicksort<T>::quicksort(vector<T> &v, int left, int right) const
{
    if (left < right)
    {
        if (v[left] > v[right])
            swap(v[left], v[right]);
        T lpiv = v[left];
        T rpiv = v[right];

        int l = left + 1;
        int k = l;
        int g = right - 1;

        while (k <= g)
        {
            if (v[k] < lpiv)
            {
                swap(v[k], v[l]);
                ++l;
            }
            else if (v[k] >= rpiv)
            {
                while (v[g] > rpiv && k < g)
                    --g;
                swap(v[k], v[g]);
                --g;
                if (v[k] < lpiv)
                {
                    swap(v[k], v[l]);
                    ++l;
                }
            }
            ++k;
        }
        --l;
        swap(v[left], v[l]);
        ++g;
        swap(v[right], v[g]);

        quicksort(v, left, l - 1);
        quicksort(v, l + 1, g - 1);
        quicksort(v, g + 1, right);
    }
}

class Countingsort : Sortingmethod<int>
{
  public:
    void operator()(vector<int> &) const;
};

void Countingsort::operator()(vector<int> &v) const
{
    int kl = INT_MAX;
    int gr = 0;

    for (int t : v)
    {
        if (t < kl)
            kl = t;
        else if (t > gr)
            gr = t;
    }

    vector<int> freq(gr + 1);

    for (int t : v)
    {
        freq[t] += 1;
    }

    vector<int> result;

    for (int i = 0; i < freq.size(); i++)
    {
        for (int j = 0; j < freq[i]; j++)
        {
            result.push_back(i);
        }
    }
    v = move(result);
}

class CountingSort2 : Sortingmethod<int>
{
  public:
    void operator()(vector<int> &) const;
};

void CountingSort2::operator()(vector<int> &v) const
{
    int kl = INT_MAX;
    int gr = 0;

    for (int t : v)
    {
        if (t < kl)
            kl = t;
        else if (t > gr)
            gr = t;
    }

    vector<int> freq(gr+1);
    for (int t : v)
    {
        freq[t]++;
    }

    for (int i = 1; i < freq.size(); i++)
    {
        freq[i] += freq[i - 1];
    }

    vector<int> tmp(v.size());
    for (int i = 0; i < v.size(); i++)
    {
        tmp[freq[v[i]]-1] = v[i];
        freq[v[i]] -= 1;
    }
    v = move(tmp);
}

#endif