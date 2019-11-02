#ifndef __RBTREE_HPP
#define __RBTREE_HPP

#define CONSTRUCTION_LOGGING 0

#include "rbnode.hpp"
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
class RBnode;

template <class Key, class Data>
using RBnodeptr = unique_ptr<RBnode<Key, Data>>;

template <class Key, class Data>
class RBtree : public RBnodeptr<Key, Data>
{
  public:
    RBtree() : RBnodeptr<Key, Data>{nullptr}
    {
        if (CONSTRUCTION_LOGGING)
            cout << "RBtree()\n";
    };
    RBtree(const Key &_k, const Data &_d, const Color &_c) : RBnodeptr<Key, Data>{make_unique<RBnode<Key, Data>>(_k, _d, _c)}
    {
        if (CONSTRUCTION_LOGGING)
            cout << "RBtree(Key&,Data&,Color&)\n";
    };
    virtual ~RBtree() = default;

    RBtree(const RBtree<Key, Data> &other) //: RBnodeptr<Key, Data>{nullptr}
    {
        if (CONSTRUCTION_LOGGING)
            cout << "RBtree(const RBtree&)\n";

        if (other)
        {
            this->reset(new RBnode<Key, Data>(*other));
        }
    };
    RBtree &operator=(const RBtree<Key, Data> &other)
    {
        if (CONSTRUCTION_LOGGING)
            cout << "operator=(const RBtree&)\n";

        RBtree<Key, Data> temp{other};
        temp.swap(*this);
        return *this;
    };

    RBtree(RBtree<Key, Data> &&other) : RBnodeptr<Key, Data>{move(other)}
    {
        if (CONSTRUCTION_LOGGING)
            cout << "RBtree(RBtree&&)\n";
    };

    RBtree &operator=(RBtree<Key, Data> &&other)
    {
        if (CONSTRUCTION_LOGGING)
            cout << "operator=(RBtree&&)\n";

        this->swap(other);
        return *this;
    };

    int depth() const;
    void rotate(bool);
    void insert_bottom_up(const Key &, const Data &);
    void insert_top_down(const Key &, const Data &);
    void delete_bottom_up(const Key &);
    void delete_top_down(const Key &);
    bool repOK() const;
    Color getColor() const;

    void inorder(std::function<void(const RBnode<Key, Data> &)> visit) const;
    void preorder(std::function<void(const RBnode<Key, Data> &)> visit) const;
    void postorder(std::function<void(const RBnode<Key, Data> &)> visit) const;
    void output(ostream &os) const;
    void pretty_print(int indent = 0) const;

  protected:
    std::tuple<RBtree<Key, Data> *, RBnode<Key, Data> *> search(const Key &);
    std::tuple<RBtree<Key, Data> *, RBtree<Key, Data> *, RBtree<Key, Data> *> get_family_pointers(const RBtree<Key, Data> *const);
    void insert_bu_fixup(RBtree<Key, Data> *);
    void transplant(RBtree<Key, Data> &&);
    int black_depth(bool &) const;
};

template <class Key, class Data>
std::tuple<RBtree<Key, Data> *, RBnode<Key, Data> *> RBtree<Key, Data>::search(const Key &key)
{
    RBtree<Key, Data> *location = this;
    RBnode<Key, Data> *parent = nullptr;

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
std::tuple<RBtree<Key, Data> *, RBtree<Key, Data> *, RBtree<Key, Data> *> RBtree<Key, Data>::get_family_pointers(const RBtree<Key, Data> *const location)
{
    RBtree<Key, Data> *parent = nullptr;
    RBtree<Key, Data> *grandparent = nullptr;
    RBtree<Key, Data> *uncle = nullptr;
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
    }

    bool grandparent_to_parent_direction = (*location)->parent->isLeftChild();
    parent = (*grandparent)->getChild(grandparent_to_parent_direction);
    uncle = (*grandparent)->getChild(!grandparent_to_parent_direction);
    return std::make_tuple(grandparent, parent, uncle);
}

template <class Key, class Data>
int RBtree<Key, Data>::depth() const
{
    if (!*this)
    {
        return -1;
    }
    return std::max((*this)->left.depth(), (*this)->right.depth()) + 1;
}

template <class Key, class Data>
void RBtree<Key, Data>::rotate(bool left)
{
    if (!*this)
    {
        return;
    }
    RBtree<Key, Data> child = move(*((*this)->getChild(!left)));
    if (child)
    {
        RBtree<Key, Data> subchild = move(*(child->getChild(left)));
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
void RBtree<Key, Data>::insert_bottom_up(const Key &key, const Data &data)
{
    auto [location, parent] = search(key);
    if (*location)
    {
        return;
    }
    *location = RBtree<Key, Data>(key, data, Color::RED);
    (*location)->parent = parent;
    // subtle shit that bites you in the ass, if you write location->insert_bu_fixup()
    // then 'this' in the context of that function will be the RBtree at the location.
    // This makes implementing proper behavior in case the tree is small (no grandparent) impossible
    // without really forced type conversions. So what you need is to move the location in as an argument
    insert_bu_fixup(location);
}

template <class Key, class Data>
void RBtree<Key, Data>::insert_bu_fixup(RBtree<Key, Data> *location)
{
    while (location && *location && (*location)->parent && (*location)->parent->color == Color::RED && (*location)->parent->parent)
    {
        auto [grandparent, parent, uncle] = get_family_pointers(location);
        if (*uncle && (*uncle)->color == Color::RED)
        {
            (*parent)->color = Color::BLACK;
            (*uncle)->color = Color::BLACK;
            location = grandparent;
        }
        else if (*parent && (*parent)->isLeftChild())
        {
            if (!(*location)->isLeftChild())
            {
                (*location)->color = Color::BLACK;
                (*grandparent)->color = Color::RED;
                parent->rotate(true);
                grandparent->rotate(false);
            }
            else
            {
                (*parent)->color = Color::BLACK;
                (*grandparent)->color = Color::RED;
                grandparent->rotate(false);
            }
        }
        else
        {
            if ((*location)->isLeftChild())
            {
                (*location)->color = Color::BLACK;
                (*grandparent)->color = Color::RED;
                parent->rotate(false);
                grandparent->rotate(true);
            }
            else
            {
                (*parent)->color = Color::BLACK;
                (*grandparent)->color = Color::RED;
                grandparent->rotate(true);
            }
        }
    }
    if (location && *location)
    {
        RBnode<Key, Data> *up = (*location)->getParent();
        if (up)
        {
            while (up->parent)
            {
                up = up->parent;
            }
            up->color = Color::BLACK;
        }
        else
        {
            (*location)->color = Color::BLACK;
        }
    }
}

template <class Key, class Data>
void RBtree<Key, Data>::transplant(RBtree<Key, Data> &&other)
{
    if ((*this)->parent)
    {
        if ((*this)->isLeftChild())
        {
            (*this)->parent->left = move(other);
        }
        else
        {
            (*this)->parent->right = move(other);
        }
    }
}

template <class Key, class Data>
void RBtree<Key, Data>::delete_bottom_up(const Key &key)
{
}

template <class Key, class Data>
void RBtree<Key, Data>::inorder(std::function<void(const RBnode<Key, Data> &)> visit) const
{
    if (*this)
    {
        (*this)->left.inorder(visit);
        visit(**this);
        (*this)->right.inorder(visit);
    };
}

template <class Key, class Data>
void RBtree<Key, Data>::preorder(std::function<void(const RBnode<Key, Data> &)> visit) const
{
    if (*this)
    {
        visit(**this);
        (*this)->left.preorder(visit);
        (*this)->right.preorder(visit);
    }
}

template <class Key, class Data>
void RBtree<Key, Data>::postorder(std::function<void(const RBnode<Key, Data> &)> visit) const
{
    if (*this)
    {
        (*this)->left.postorder(visit);
        (*this)->right.postorder(visit);
        visit(**this);
    }
}

template <class Key, class Data>
void RBtree<Key, Data>::output(ostream &os) const
{
    inorder([&os](const RBnode<Key, Data> &node) {
        os << "(" << node.key << " -> " << node.data << " ->" << node.color << ")";
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
void RBtree<Key, Data>::pretty_print(int indent) const
{
    if (*this)
    {
        if ((*this)->right)
            (*this)->right.pretty_print(indent + 8);

        if (indent)
        {
            cout << std::setw(indent) << ' ';
        }
        cout << (*this)->key << ',' << (*this)->data << ',' << (*this)->color << '\n';

        if ((*this)->left)
            (*this)->left.pretty_print(indent + 8);
    }
}

#endif