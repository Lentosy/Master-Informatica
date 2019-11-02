#ifndef __SPLAYNODE_HPP
#define __SPLAYNODE_HPP

#include "splaytree.hpp"
#include <iostream>

template <class Key, class Data>
class SplayTree;

template <class Key, class Data>
class SplayNode
{
    friend class SplayTree<Key, Data>;

  public:
    SplayNode() : parent(0)
    {
        //cout << "SplayNode()" << endl;
    }
    SplayNode(const Key &sl, const Data &d) : key{sl}, data{d}, parent{0}
    {
        //cout << "SplayNode(const Key &, const Data &)" << endl;
    }
    SplayNode(Key &&sl, Data &&d) : key{move(sl)}, data{move(d)}, parent{0}
    {
        //cout << "SplayNode(Key &&,Data &&)" << endl;
    }
    virtual ~SplayNode() = default;

    SplayNode(const SplayNode<Key, Data> &other) : key{other.key}, data{other.data}
    {
        parent = other.parent ? other.parent : nullptr;
        if (other.left)
        {
            other.left->parent = this;
        }
        if (other.right)
        {
            other.right->parent = this;
        }
    }

    SplayNode<Key, Data> &operator=(const SplayNode<Key, Data> &other)
    {
        key = other.key;
        data = other.data;
        parent = other.parent ? other.parent : nullptr;
        if (other.left)
        {
            other.left->parent = this;
        }
        if (other.right)
        {
            other.right->parent = this;
        }

        return *this;
    }
    SplayNode(SplayNode<Key, Data> &&other) = delete;
    SplayNode<Key, Data> &operator=(SplayNode<Key, Data> &&other) = delete;

    bool operator==(const SplayNode<Key, Data> &other) const
    {
        return ((key == other.key) && (data == other.data));
    }

    bool operator!=(const SplayNode<Key, Data> &other) const
    {
        return !(*this == other);
    }

    const Data &getData() const
    {
        return data;
    }

    const Key &getKey() const
    {
        return key;
    }

    SplayTree<Key, Data> *getChild(bool l)
    {
        return l ? &left : &right;
    }

    SplayNode<Key, Data> *getParent()
    {
        return this->parent;
    }

    bool isLeftChild() const
    {
        // [[expects: parent != nullptr]] This syntax is not yet support by GCC or CLANG
        if (parent)
        {
            if (this == (parent->left).get())
            {
                return true;
            }
            else if (this == (parent->right).get())
            {
                return false;
            }
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const SplayNode<Key, Data> &node)
    {
        os << node.key << ',' << node.data << " L: " << node.left.get() << " R: " << node.right.get() << '\n';
        return os;
    }

  protected:
    Key key;
    Data data;
    SplayNode<Key, Data> *parent;
    SplayTree<Key, Data> left, right;
};

#endif