#ifndef __BTREE_HPP
#define __BTREE_HPP

#include "btnode.hpp"
#include <utility>
using std::move;

template <class Key, class Data>
class BTnode;

template <class Key, class Data>
class BTree
{
  public:
    BTree() = default;
    virtual ~BTree() = default;
    BTree(const BTree<Key, Data> &) = default;
    BTree(BTree<Key, Data> &&) = default;
    BTree<Key, Data> &operator=(const BTree<Key, Data> &) = default;
    BTree<Key, Data> &operator=(BTree<Key, Data> &&) = default;
    BTree(int _minimum_degree) : minimum_degree{_minimum_degree} {};
    void insert_bottom_up(const Key &, const Data &);

  private:
    int minimum_degree;
    BTnode<Key, Data> root;
};

template <class Key, class Data>
void BTree<Key, Data>::insert_bottom_up(const Key &key, const Data &data)
{
    if (root.empty())
    {
        root = BTnode<Key,Data>(true, this->minimum_degree);
        root.keys[0] = key;
        root.data[0] = data;
        root.current_nr_of_keys = 1;
    }
    else if (root.keys_full())
    {
        BTnode<Key,Data> new_root(false, this->minimum_degree);        
        new_root.children[0] = move(root);
        new_root.split_node(0, &new_root.children[0]);
        int i = 0;
        if (new_root.keys[0] < key)
        {
            i++;
        }
        new_root.children[i].insert_without_split(key, data);
        root = move(new_root);
    }
    else
    {
        root.insert_without_split(key, data);
    }
}
#endif