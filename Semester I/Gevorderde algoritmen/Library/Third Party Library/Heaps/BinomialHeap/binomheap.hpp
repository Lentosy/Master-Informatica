#ifndef __BINOMHEAP_HPP
#define __BINOMHEAP_HPP

#include <vector>
#include <memory>
using std::unique_ptr;

template <class Key, class Data>
class BinomHeapNode;

template <class Key, class Data>
class BinomHeap : public unique_ptr<BinomHeapNode<Key, Data>>
{
    using unique_ptr<BinomHeapNode<Key, Data>>::unique_ptr;

  public:
    BinomHeap() = default;
    virtual ~BinomHeap() = default;
    BinomHeap(BinomHeap<Key, Data> &&other) : unique_ptr<BinomHeapNode<Key, Data>>{std::move(other)} {}
    BinomHeap(BinomHeapNode<Key, Data> *other) : unique_ptr<BinomHeapNode<Key, Data>>{other} {}
    BinomHeap &operator=(BinomHeap<Key, Data> &&other)
    {
        unique_ptr<BinomHeapNode<Key, Data>>::operator=(std::move(other));
        return *this;
    }
    BinomHeap(const Key &_k, const Data &_d) : unique_ptr<BinomHeapNode<Key, Data>>{std::make_unique<BinomHeapNode<Key, Data>>(_k, _d)} {}

    void put(const Key &, const Data &);
    void merge(BinomHeap<Key, Data> &&b);
    Data &min();
    void erase_min();
    int get_subtree_order();
  private:
    
    void simple_merge(BinomHeap<Key, Data> &b);
    BinomHeap<Key, Data> *node_min();
};

template <class Key, class Data>
class BinomHeapNode
{
    friend class BinomHeap<Key, Data>;

  public:
    BinomHeapNode(const Key &sl, const Data &d) : key(sl), data(d) {}

  private:
    Key key;
    Data data;

    BinomHeap<Key, Data> left, brother;
};

template <class Key, class Data>
int BinomHeap<Key, Data>::get_subtree_order()
{
    if (!*this)
    {
        return -1;
    }
    return 1 + (*this)->left.get_subtree_order(); // you have to make sure that left is a valid object, even if it has no content
}

template <class Key, class Data>
void BinomHeap<Key, Data>::put(const Key &sl, const Data &d)
{
    merge(std::move(BinomHeap<Key, Data>{sl, d}));
}

template <class Key, class Data>
void BinomHeap<Key, Data>::merge(BinomHeap<Key, Data> &&b)
{
    simple_merge(b);

    BinomHeap<Key, Data> *x = this, *next = &(*this)->brother;
    while (*next != nullptr)
    {
        if (x->get_subtree_order() != next->get_subtree_order())
        {
            x = next, next = &(*next)->brother;
        }
        else
        {
            BinomHeap<Key, Data> hulp(std::move(*next));
            if ((*x)->key <= hulp->key)
                (*x)->brother.swap(hulp->brother);
            else
                x->swap(hulp);
            (*x)->left.swap(hulp);
            (*x)->left->brother.swap(hulp);
            next = &(*x)->brother;
        }
    }
}

template <class Key, class Data>
void BinomHeap<Key, Data>::simple_merge(BinomHeap<Key, Data> &b)
{
    if (!*this)
        this->swap(b);
    else
    {
        if (b)
        {
            if (get_subtree_order() >= b.get_subtree_order())
            {
                this->swap(b);
            }
            (*this)->brother.simple_merge(b);
        }
    }
}

template <class Key, class Data>
Data &BinomHeap<Key, Data>::min()
{
    return (*node_min())->data;
}

template <class Key, class Data>
BinomHeap<Key, Data> *BinomHeap<Key, Data>::node_min()
{
    BinomHeap<Key, Data> *min = this;
    for (BinomHeap<Key, Data> *walker = &(*min)->brother; *walker != nullptr; walker = &(*walker)->brother)
        if ((*walker)->key < (*min)->key)
            min = walker;
    return min;
}

template <class Key, class Data>
void BinomHeap<Key, Data>::erase_min()
{

    BinomHeap<Key, Data> *q = node_min();
    BinomHeap<Key, Data> old_min(std::move(*q));
    *q = std::move(old_min->brother);

    old_min = std::move(old_min->left);
    BinomHeap<Key, Data> rest;
    while (old_min != nullptr)
    {
        rest = std::move(old_min->brother);
        merge(old_min);
        old_min = std::move(rest);
    }
}

#endif