#ifndef __RBNODE_HPP
#define __RBNODE_HPP

#include "rbtree.hpp"
#include <iostream>

enum class Color
{
    RED,
    BLACK
};

std::ostream &operator<<(std::ostream &os, const Color c)
{
    if (c == Color::RED)
    {
        os << "R";
    }
    else if (c == Color::BLACK)
    {
        os << "B";
    }
    return os;
}

template <class Key, class Data>
class RBtree;

template <class Key, class Data>
class RBnode
{
    friend class RBtree<Key, Data>;

  public:
    RBnode() : parent(0)
    {
        //cout << "RBnode()" << endl;
    }
    RBnode(const Key &sl, const Data &d, const Color &c) : key{sl}, data{d}, color{c}, parent{0}
    {
        //cout << "RBnode(const Key &, const Data &)" << endl;
    }
    RBnode(Key &&sl, Data &&d, Color &c) : key{move(sl)}, data{move(d)}, color{c}, parent{0}
    {
        //cout << "RBnode(Key &&,Data &&)" << endl;
    }
    virtual ~RBnode() = default;

    RBnode(const RBnode<Key, Data> &other) : key{other.key}, data{other.data}, color{other.color}
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

    RBnode<Key, Data> &operator=(const RBnode<Key, Data> &other)
    {
        key = other.key;
        data = other.data;
        color = other.color;
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
    RBnode(RBnode<Key, Data> &&other) = delete;
    RBnode<Key, Data> &operator=(RBnode<Key, Data> &&other) = delete;

    bool operator==(const RBnode<Key, Data> &other) const
    {
        return ((key == other.key) && (data == other.data) && (color = other.color));
    }

    bool operator!=(const RBnode<Key, Data> &other) const
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

    const Color &getColor() const
    {
        return color;
    }

    RBtree<Key, Data> *getChild(bool l)
    {
        return l ? &left : &right;
    }

    RBnode<Key, Data> *getParent()
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

  protected:
    Key key;
    Data data;
    Color color;
    RBnode<Key, Data> *parent;
    RBtree<Key, Data> left, right;
};

#endif