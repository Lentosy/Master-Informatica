#ifndef __MINHEAP_HPP
#define __MINHEAP_HPP

#include <vector>
using std::vector;
#include <utility>
using std::pair;

template <class Key, class Data>
class MinHeap
{
  public:
    MinHeap() = default;
    MinHeap(const int size) { heap = vector<pair<Key, Data>>(size); }
    MinHeap(vector<pair<Key,Data>>&& _data) : heap{move(_data)} {min_heapify_On(0);}
    virtual ~MinHeap() = default;
    MinHeap(const MinHeap<Key, Data> &) = default;
    MinHeap(MinHeap<Key, Data> &&) = default;
    MinHeap<Key, Data> &operator=(const MinHeap<Key, Data> &) = default;
    MinHeap<Key, Data> &operator=(MinHeap<Key, Data> &&) = default;

    void insert(Key &&, Data &&);
    void remove_root();
    void min_heapify_On(size_t root = 0);
    void min_heapify_Onlgn(vector<pair<Key, Data>> &&);
    void sift_up(size_t);
    void sift_down(size_t);

    // 0 indexed backing datastructure
    constexpr size_t parent(size_t node) const
    {
        return node > 0 ? (node - 1) / 2 : node;
    }

    constexpr size_t left(size_t parent) const
    {
        return 2 * parent + 1;
    }

    constexpr size_t right(size_t parent) const
    {
        return 2 * parent + 2;
    }

    constexpr size_t size() const
    {
        return heap.size();
    }

  private:
    vector<pair<Key, Data>> heap;
};

template <class Key, class Data>
void MinHeap<Key, Data>::insert(Key &&_k, Data &&_d)
{
    heap.emplace_back(std::make_pair<Key, Data>(move(_k), move(_d)));
    sift_up(size() - 1);
}

template <class Key, class Data>
void MinHeap<Key, Data>::remove_root()
{
    heap[0] = move(heap[size()-1]);
    sift_down(0);
}

template <class Key, class Data>
void MinHeap<Key, Data>::min_heapify_On(size_t root)
{
    if(root >= size()) return;
    int l = left(root);
    int r = right(root);
    min_heapify_On(l);
    min_heapify_On(r);
    sift_up(root);
}

template <class Key, class Data>
void MinHeap<Key, Data>::min_heapify_Onlgn(vector<pair<Key, Data>> &&data)
{
    for(auto &&x : data){
        insert(move(x.first),move(x.second));
    }
}

template <class Key, class Data>
void MinHeap<Key, Data>::sift_up(size_t node)
{
    if (node == 0 || node >= size())
        return;
    size_t p = parent(node);
    if (heap[node] < heap[p])
    {
        swap(heap[node], heap[p]);
        sift_up(p);
    }
}

template <class Key, class Data>
void MinHeap<Key, Data>::sift_down(size_t node)
{
    size_t l = left(node);
    size_t r = right(node);

    size_t lower = node;
    if (l <= size() && heap[l] < heap[lower])
    {
        lower = l;
    }
    if (r <= size() && heap[r] < heap[lower])
    {
        lower = r;
    }

    if (lower != node)
    {
        swap(heap[node], heap[lower]);
        sift_down(lower);
    }
}

#endif
