#ifndef __BTNODE_HPP
#define __BTNODE_HPP

#include "btree.hpp"
#include <functional>
using std::function;
#include <vector>
using std::vector;
#include <utility>
using std::move;

template <class Key, class Data>
class BTree;

template <class Key, class Data>
class BTnode
{
    friend class BTree<Key, Data>;

  public:
    BTnode() { current_nr_of_keys = 0; };
    virtual ~BTnode() = default;
    BTnode(const BTnode<Key, Data> &) = default;
    BTnode<Key, Data> &operator=(const BTnode<Key, Data> &) = default;
    BTnode(BTnode<Key, Data> &&) = default;
    BTnode<Key, Data> &operator=(BTnode<Key, Data> &&) = default;
    BTnode(bool _is_leaf, int _minimum_degree) : is_leaf{_is_leaf}, minimum_degree{_minimum_degree}
    {
        current_nr_of_keys = 0;
        keys = vector<Key>(2 * minimum_degree - 1);
        data = vector<Data>(2 * minimum_degree - 1);
        if (!is_leaf)
        {
            children = vector<BTnode<Key, Data>>(2 * minimum_degree);
        }
    }

    void traverse(function<void(const BTnode<Key, Data> &)> &);
    BTnode<Key, Data> *search(const Key &);
    void insert_without_split(const Key &, const Data &);
    void split_node(int, BTnode<Key, Data> *);
    void remove_bottom_up(const Key &);
    bool empty() const;
    bool keys_full() const;

  private:
    bool is_leaf;
    int current_nr_of_keys;
    int minimum_degree;
    vector<BTnode<Key, Data>> children;
    vector<Key> keys;
    vector<Data> data;
};

template <class Key, class Data>
void BTnode<Key, Data>::traverse(function<void(const BTnode<Key, Data> &)> &operation)
{
    int i;
    for (i = 0; i < current_nr_of_keys; i++)
    {
        if (!is_leaf)
        {
            children[i].traverse(operation);
        }
        operation(*this);
    }
    // since there is always a child more than there are keys (keys: 2t-1, children: 2t)
    // we should also traverse the final child
    if (!is_leaf)
    {
        children[i].traverse(operation);
    }
    operation(*this);
}

template <class Key, class Data>
BTnode<Key, Data> *BTnode<Key, Data>::search(const Key &key)
{
    // you could also do binary search or interpolating search
    int i = 0;
    while (i < current_nr_of_keys && key > keys[i])
    {
        i++;
    }
    // do we have the key here?
    if (keys[i] == key)
    {
        return this;
    }

    // if we didn't have the key here and there are no deeper level (aka this is already a leaf, then we don't have the key)
    else if (is_leaf)
    {
        return nullptr;
    }
    // if there are other levels, we may try to look if the key is there
    else
    {
        return children[i].search(key);
    }
}

template <class Key, class Data>
void BTnode<Key, Data>::insert_without_split(const Key &key, const Data &_data)
{
    int i = current_nr_of_keys - 1;
    if (is_leaf)
    {
        while (i >= 0 && keys[i] > key)
        {
            keys[i + 1] = move(keys[i]);
            data[i + 1] = move(data[i]);
            i--;
        }
        keys[i + 1] = key;
        data[i + 1] = _data;
        current_nr_of_keys += 1;
    }
    else
    {
        while (i >= 0 && keys[i] > key)
        {
            i--;
        }
        if (children[i].keys_full())
        {
            split_node(i + 1, &children[i + 1]);
            if (keys[i + 1] < key)
            {
                i++;
            }
        }
        children[i + 1].insert_without_split(key, _data);
    }
}

template <class Key, class Data>
void BTnode<Key, Data>::split_node(int to_split_child_index, BTnode<Key, Data> *to_split)
{
    BTnode<Key, Data> new_node(to_split->is_leaf, to_split->minimum_degree);
    new_node.current_nr_of_keys = minimum_degree - 1;

    // moving keys & data
    for (int i = 0; i < minimum_degree - 1; i++)
    {
        new_node.keys[i] = move(to_split->keys[minimum_degree + i]);
        //to_split->keys[minimum_degree+i] = Key{0}; unnecessary! Saying how many keys the node has, means we don't have to clean up residual keys, they no longer count         
        new_node.data[i] = move(to_split->data[minimum_degree + i]);
        //to_split->data[minimum_degree+i] = Data{0}; unnecessary! Saying how many keys the node has, means we don't have to clean up residual keys, they no longer count 
    }
    // moving children if the node we need to split wasn't a leaf node
    if (!to_split->is_leaf)
    {
        for (int i = 0; i < minimum_degree; i++)
        {
            new_node.children[i] = move(to_split->children[minimum_degree + i]);
        }
    }
    to_split->current_nr_of_keys = minimum_degree - 1;

    for (int i = current_nr_of_keys; i >= to_split_child_index + 1; i--)
    {
        this->children[i + 1] = move(this->children[i]);
    }
    this->children[to_split_child_index + 1] = move(new_node);

    for (int i = current_nr_of_keys - 1; i >= to_split_child_index; i--)
    {
        this->keys[i + 1] = move(this->keys[i]);
        this->data[i + 1] = move(this->data[i]);
    }
    this->keys[to_split_child_index] = move(to_split->keys[minimum_degree - 1]);
    // to_split->keys[minimum_degree-1] = Key{0}; unnecessary! Saying how many keys the node has, means we don't have to clean up residual keys, they no longer count 
    this->data[to_split_child_index] = move(to_split->data[minimum_degree - 1]);
    // to_split->data[minimum_degree-1] = Data{0}; unnecessary! Saying how many keys the node has, means we don't have to clean up residual keys, they no longer count 

    this->current_nr_of_keys += 1;
}

template <class Key, class Data>
bool BTnode<Key, Data>::empty() const
{
    return current_nr_of_keys == 0;
}

template <class Key, class Data>
bool BTnode<Key, Data>::keys_full() const
{
    return current_nr_of_keys == minimum_degree * 2 - 1;
}

#endif