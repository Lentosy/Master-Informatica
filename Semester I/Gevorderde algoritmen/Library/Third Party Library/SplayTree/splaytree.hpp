#ifndef __SPLAYTREE_HPP
#define __SPLAYTREE_HPP

#define CONSTRUCTION_LOGGING 1

#include "splaynode.hpp"
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
#include <iomanip>
#include <algorithm>
#include <functional>
#include <memory>
using std::make_unique;
using std::unique_ptr;
#include <sstream>
#include <stack>
#include <tuple>

template <class Key, class Data>
class SplayNode;

template <class Key, class Data>
using SplayNodeptr = unique_ptr<SplayNode<Key, Data>>;

template <class Key, class Data>
class SplayTree : public SplayNodeptr<Key, Data>
{
  public:
    SplayTree() : SplayNodeptr<Key, Data>{nullptr}
    {
        if (CONSTRUCTION_LOGGING)
            cout << "SplayTree()\n";
    };
    SplayTree(const Key &_k, const Data &_d) : SplayNodeptr<Key, Data>{make_unique<SplayNode<Key, Data>>(_k, _d)}
    {
        if (CONSTRUCTION_LOGGING)
            cout << "SplayTree(Key&,Data&)\n";
    };
    virtual ~SplayTree() = default;

    SplayTree(const SplayTree<Key, Data> &other) //: SplayNodeptr<Key, Data>{nullptr}
    {
        if (CONSTRUCTION_LOGGING)
            cout << "SplayTree(const SplayTree&)\n";

        if (other)
        {
            this->reset(new SplayNode<Key, Data>(*other));
        }
    };
    SplayTree &operator=(const SplayTree<Key, Data> &other)
    {
        if (CONSTRUCTION_LOGGING)
            cout << "operator=(const SplayTree&)\n";

        SplayTree<Key, Data> temp{other};
        temp.swap(*this);
        return *this;
    };

    SplayTree(SplayTree<Key, Data> &&other) : SplayNodeptr<Key, Data>{move(other)}
    {
        if (CONSTRUCTION_LOGGING)
            cout << "SplayTree(SplayTree&&)\n";
    };

    SplayTree &operator=(SplayTree<Key, Data> &&other)
    {
        if (CONSTRUCTION_LOGGING)
            cout << "operator=(SplayTree&&)\n";

        this->swap(other);
        return *this;
    };

    int depth() const;
    std::tuple<SplayTree<Key, Data> *, SplayTree<Key, Data> *> search(const Key &);
    void rotate(bool);
    void insert_bottom_up(const Key &, const Data &);
    void insert_top_down(const Key &, const Data &);
    void delete_bottom_up(const Key &);
    void delete_top_down(const Key &);
    bool repOK() const;

    void inorder(std::function<void(const SplayNode<Key, Data> &)> visit) const;
    void preorder(std::function<void(const SplayNode<Key, Data> &)> visit) const;
    void postorder(std::function<void(const SplayNode<Key, Data> &)> visit) const;
    void output(ostream &os) const;
    void pretty_print(int indent = 0) const;

    SplayTree<Key, Data> *predecessor(const SplayTree<Key, Data> *);
    SplayTree<Key, Data> *successor(const SplayTree<Key, Data> *);

    const SplayTree<Key, Data> *largest(const SplayTree<Key, Data> *);
    const SplayTree<Key, Data> *smallest(const SplayTree<Key, Data> *);

    std::tuple<SplayTree<Key, Data>, SplayTree<Key, Data>> split(const Key &);
    SplayTree<Key, Data> join(SplayTree<Key, Data> *, SplayTree<Key, Data> *);

  protected:
    std::tuple<SplayTree<Key, Data> *, SplayNode<Key, Data> *> search_no_splay(const Key &);
    std::tuple<SplayTree<Key, Data> *, SplayTree<Key, Data> *> get_family_pointers(const SplayTree<Key, Data> *const);
    SplayTree<Key, Data> *get_parent(const SplayTree<Key, Data> *const);
    void splay(const SplayTree<Key, Data> *);
};

template <class Key, class Data>
std::tuple<SplayTree<Key, Data> *, SplayTree<Key, Data> *> SplayTree<Key, Data>::search(const Key &key)
{
    SplayTree<Key, Data> *location = this;
    SplayTree<Key, Data> *parent = nullptr;

    while (*location && (*location)->key != key)
    {
        parent = location;
        if (key > (*location)->key)
        {
            location = &(*location)->right;
        }
        else
        {
            location = &(*location)->left;
        }
    }
    if (location && *location)
    {
        splay(location);
        return std::make_tuple(this, parent);
    }
    return std::make_tuple(location, parent);
}

template <class Key, class Data>
std::tuple<SplayTree<Key, Data> *, SplayNode<Key, Data> *> SplayTree<Key, Data>::search_no_splay(const Key &key)
{
    SplayTree<Key, Data> *location = this;
    SplayNode<Key, Data> *parent = nullptr;

    while (*location && (*location)->key != key)
    {
        parent = location->get();
        if (key > (*location)->key)
        {
            location = &(*location)->right;
        }
        else
        {
            location = &(*location)->left;
        }
    }
    return std::tuple(location, parent);
}

template <class Key, class Data>
SplayTree<Key, Data> *SplayTree<Key, Data>::predecessor(const SplayTree<Key, Data> *location)
{
    SplayTree<Key, Data> *walker = &(*location)->left;
    SplayTree<Key, Data> *predecessor = nullptr;
    while (walker && *walker)
    {
        predecessor = walker;
        walker = &(*walker)->right;
    }
    return predecessor;
}

template <class Key, class Data>
SplayTree<Key, Data> *SplayTree<Key, Data>::successor(const SplayTree<Key, Data> *location)
{
    SplayTree<Key, Data> *walker = &(*location)->right;
    SplayTree<Key, Data> *successor = nullptr;
    while (walker && *walker)
    {
        successor = walker;
        walker = &(*walker)->left;
    }
    return successor;
}

template <class Key, class Data>
const SplayTree<Key, Data> *SplayTree<Key, Data>::largest(const SplayTree<Key, Data> *location)
{
    const SplayTree<Key, Data> *largest = location;
    while (location && *location)
    {
        if ((*location)->right)
        {
            largest = &(*location)->right;
        }
        location = &(*location)->right;
    }
    return largest;
}

template <class Key, class Data>
const SplayTree<Key, Data> *SplayTree<Key, Data>::smallest(const SplayTree<Key, Data> *location)
{
    const SplayTree<Key, Data> *smallest = location;
    while (location && *location)
    {
        if ((*location)->left)
        {
            smallest = &(*location)->left;
        }
        location = &(*location)->left;
    }
    return smallest;
}

template <class Key, class Data>
std::tuple<SplayTree<Key, Data>, SplayTree<Key, Data>> SplayTree<Key, Data>::split(const Key &key)
{
    auto [location, parent] = search(key);
    std::tuple<SplayTree<Key, Data>, SplayTree<Key, Data>> tup;

    if (location && *location)
    {
        if ((*location)->right)
        {
            (*location)->right->parent = nullptr;
            std::get<1>(tup) = move((*location)->right);
        }
        std::get<0>(tup) = move(*location);
    }
    return tup;
}

template <class Key, class Data>
SplayTree<Key, Data> SplayTree<Key, Data>::join(SplayTree<Key, Data> *left, SplayTree<Key, Data> *right)
{
    SplayTree<Key, Data> total;
    if (left && *left && right && *right)
    {
        const SplayTree<Key, Data> *left_largest = left->largest(left);
        splay(left_largest);
        (*right)->parent = left->get();
        (*left)->right = move(*right);
        total = move(*left);
    }
    return total;
}

template <class Key, class Data>
std::tuple<SplayTree<Key, Data> *, SplayTree<Key, Data> *> SplayTree<Key, Data>::get_family_pointers(const SplayTree<Key, Data> *const location)
{
    SplayTree<Key, Data> *parent = nullptr;
    SplayTree<Key, Data> *grandparent = nullptr;
    if (location && *location && (*location)->parent && (*location)->parent->parent)
    {
        if (!((*location)->parent->parent->parent))
        {
            grandparent = this;
        }
        else
        {
            grandparent = (*location)->parent->parent->parent->getChild((*location)->parent->parent->isLeftChild());
        }
        bool grandparent_to_parent_direction = (*location)->parent->isLeftChild();
        parent = (*grandparent)->getChild(grandparent_to_parent_direction);
    }
    else if (location && *location && (*location)->parent)
    {
        if (!((*location)->parent->parent))
        {
            parent = this;
        }
    }

    return std::make_tuple(grandparent, parent);
}

template <class Key, class Data>
SplayTree<Key, Data> *SplayTree<Key, Data>::get_parent(const SplayTree<Key, Data> *const location)
{
    SplayTree<Key, Data> *parent = nullptr;
    if (location && *location)
    {
        if (!(*location)->parent->parent)
        {
            parent = this;
        }
        else
        {
            bool grandparent_to_parent_direction = (*location)->parent->isLeftChild();
            parent = (*location)->parent->parent->getChild(grandparent_to_parent_direction);
        }
    }
    return parent;
}

template <class Key, class Data>
void SplayTree<Key, Data>::splay(const SplayTree<Key, Data> *location)
{
    if (location && *location)
    {
        auto [grandparent, parent] = get_family_pointers(location);
        if (parent && *parent)
        {
            if (!grandparent)
            {
                bool parent_to_location_direction = (*location)->isLeftChild();
                parent->rotate(!parent_to_location_direction);
            }
            else if (grandparent && *grandparent)
            {
                bool grandparent_to_parent_direction = (*parent)->isLeftChild();
                bool parent_to_location_direction = (*location)->isLeftChild();
                if ((grandparent_to_parent_direction && parent_to_location_direction) || (!grandparent_to_parent_direction && !parent_to_location_direction))
                {
                    grandparent->rotate(!grandparent_to_parent_direction);
                    grandparent->rotate(!parent_to_location_direction); // the original parent is now the grandparent
                }
                else
                {
                    parent->rotate(!parent_to_location_direction);
                    grandparent->rotate(!grandparent_to_parent_direction);
                }
            }
            splay(grandparent);
        }
    }
}

template <class Key, class Data>
int SplayTree<Key, Data>::depth() const
{
    if (!*this)
    {
        return -1;
    }
    return std::max((*this)->left.depth(), (*this)->right.depth()) + 1;
}

template <class Key, class Data>
void SplayTree<Key, Data>::rotate(bool left)
{
    if (!*this)
    {
        return;
    }
    SplayTree<Key, Data> child = move(*((*this)->getChild(!left)));
    if (child)
    {
        SplayTree<Key, Data> subchild = move(*(child->getChild(left)));
        if (subchild)
        {
            *((*this)->getChild(!left)) = move(subchild);
        }
        child->parent = (*this)->parent;
        (*this)->parent = child.get();
        *(child->getChild(left)) = move(*this);
        *this = move(child);
    }
}

template <class Key, class Data>
void SplayTree<Key, Data>::insert_bottom_up(const Key &key, const Data &data)
{
    auto [location, parent] = search_no_splay(key);
    if (*location)
    {
        return;
    }
    *location = SplayTree<Key, Data>(key, data); // despite not writing move(SplayTree...) a move is performed to bring the new node into location
    (*location)->parent = parent;
    splay(location);
}

template <class Key, class Data>
void SplayTree<Key, Data>::insert_top_down(const Key &key, const Data &data)
{
    auto [location, parent] = search_no_splay(key);
    if (!*location && parent)
    {
        auto [left, right] = split(parent->key);
        SplayTree<Key, Data> tmp{key, data};
        if (key > parent->key)
        {
            tmp->parent = nullptr;
            left->parent = tmp.get();
            tmp->left = move(left);
            if (right)
            {
                right->parent = tmp.get();
                tmp->right = move(right);
            }
        }
        else if (key < parent->key)
        {
            right->parent = left.get();
            left->right = move(right);

            SplayTree<Key, Data> left_left;
            if (left->left)
            {
                left->left->parent = tmp.get();
                left_left = move(left->left);
                tmp->left = move(left_left);
            }
            left->parent = tmp.get();
            tmp->right = move(left);
        }
        *this = move(tmp);
    }
    else
    {
        *location = SplayTree<Key, Data>(key, data);
        (*location)->parent = nullptr;
        *this = move(*location);
    }
}

template <class Key, class Data>
void SplayTree<Key, Data>::delete_bottom_up(const Key &key)
{
    auto [location, parent] = search_no_splay(key);
    if (location && *location)
    {
        if ((*location)->left && (*location)->right)
        {
            SplayTree<Key, Data> *suc = successor(location);
            if (suc && *suc)
            {
                (*location)->key = (*suc)->key;
                (*location)->data = (*suc)->data;
                if ((*suc)->right)
                {
                    (*suc)->right->parent = (*suc)->parent;
                    (*suc)->parent->left = move((*suc)->right);
                }
            }
            suc->reset(nullptr);
            splay(location);
        }
        else if ((*location)->left)
        {
            (*location)->left->parent = (*location)->parent;
            *location = move((*location)->left);
            splay(location);
        }
        else if ((*location)->right)
        {
            (*location)->right->parent = (*location)->parent;
            *location = move((*location)->right);
            splay(location);
        }
        else
        {
            SplayTree<Key, Data> *p = get_parent(location);
            location->reset(nullptr);
            splay(p);
        }
    }
}

template <class Key, class Data>
void SplayTree<Key, Data>::inorder(std::function<void(const SplayNode<Key, Data> &)> visit) const
{
    if (*this)
    {
        (*this)->left.inorder(visit);
        visit(**this);
        (*this)->right.inorder(visit);
    };
}

template <class Key, class Data>
void SplayTree<Key, Data>::preorder(std::function<void(const SplayNode<Key, Data> &)> visit) const
{
    if (*this)
    {
        visit(**this);
        (*this)->left.preorder(visit);
        (*this)->right.preorder(visit);
    }
}

template <class Key, class Data>
void SplayTree<Key, Data>::postorder(std::function<void(const SplayNode<Key, Data> &)> visit) const
{
    if (*this)
    {
        (*this)->left.postorder(visit);
        (*this)->right.postorder(visit);
        visit(**this);
    }
}

template <class Key, class Data>
void SplayTree<Key, Data>::output(ostream &os) const
{
    inorder([&os](const SplayNode<Key, Data> &node) {
        os << "(" << node.key << " -> " << node.data << ")";
        os << "\n  Left child: ";
        if (node.left)
            os << node.left->key;
        else
            os << "-----";
        os << "\n  Right child: ";
        if (node.right)
            os << node.right->key;
        else
            os << "-----";
        os << "\n";
    });
}

template <class Key, class Data>
void SplayTree<Key, Data>::pretty_print(int indent) const
{
    if (*this)
    {
        if ((*this)->right)
            (*this)->right.pretty_print(indent + 8);

        if (indent)
        {
            cout << std::setw(indent) << ' ';
        }
        cout << (*this)->key << ',' << (*this)->data << '\n';

        if ((*this)->left)
            (*this)->left.pretty_print(indent + 8);
    }
}

#endif