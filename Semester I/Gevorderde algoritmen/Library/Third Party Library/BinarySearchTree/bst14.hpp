#ifndef __BST_HPP
#define __BST_HPP
#include <cstdlib>
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
#include <iomanip>
#include <queue>
#include <memory>
#include <functional>

using std::make_unique;
using std::ostream;
using std::unique_ptr;
/**********************************************************************

   Class: Binary Search Tree (BST)
   
   beschrijving: BST in which no ducplicate keys are allowed
   
***************************************************************************/

template <class Key, class Data>
class BSTnode;

template <class Key, class Data>
class BST : public unique_ptr<BSTnode<Key, Data>>
{
    using unique_ptr<BSTnode<Key, Data>>::unique_ptr;

  public:
    BST<Key, Data>() = default;
    // ~BST<Key, Data>() = default;
    // BST<Key, Data>(const BST<Key, Data> &other) = delete;
    // BST<Key, Data>(BST<Key, Data> &&other) = default;
    // BST<Key, Data> &operator=(const BST<Key, Data> &other) = delete;
    // BST<Key, Data> &operator=(BST<Key, Data> &&other) = default;

    BST<Key, Data>(unique_ptr<BSTnode<Key, Data>> &&nodeptr) : unique_ptr<BSTnode<Key, Data>>(move(nodeptr)){
                                                                   //cout << "BST(unique_ptr<BSTnode>&&)" << endl;
                                                               };

    BST<Key, Data> &operator=(unique_ptr<BSTnode<Key, Data>> &&nodeptr)
    {
        //cout << "operator=(BSTnode&&)" << endl;
        this->unique_ptr<BSTnode<Key, Data>>::operator=(move(nodeptr));
        return *this;
    };

  public:
    void add(const Key &key, const Data &data);
    void rotate(bool left);
    void inorder(std::function<void(const BSTnode<Key, Data> &)> visit) const;
    void preorder(std::function<void(const BSTnode<Key, Data> &)> visit) const;
    void postorder(std::function<void(const BSTnode<Key, Data> &)> visit) const;
    void output(ostream &os) const;
    bool repOK() const;
    int size() const;
    int depth() const;
    void makeImbalanced();
    void makeBalanced();
    void pretty_print(int indent = 0) const;

  protected:
    // The search function looks for key in the tree and return the tree containing the key or an empty tree if the key isn't in the tree
    // It also sets the parent argument (a pointer passed via reference) to that tree's parent (so long as the tree has a parent)
    void search(const Key &key, BSTnode<Key, Data> *&parent, BST<Key, Data> *&location);

  private:
    void makeBalanced_op();
};

template <class Key, class Data>
class BSTnode
{
    friend class BST<Key, Data>;

  public:
    BSTnode() : parent(0)
    {
        //cout << "BSTnode()" << endl;
    }
    BSTnode(const Key &sl, const Data &d) : key{sl}, data(d), parent(0)
    {
        //cout << "BSTnode(const Key &, const Data &)" << endl;
    }
    BSTnode(Key &&sl, Data &&d) : key{move(sl)}, data(move(d)), parent(0)
    {
        //cout << "BSTnode(Key &&,Data &&)" << endl;
    }

    const Data &getData() const
    {
        return data;
    }

    const Key &getKey() const
    {
        return key;
    }

    BST<Key, Data> getChild(bool l)
    {
        return l ? left : right;
    }

  protected:
    Key key;
    Data data;
    BSTnode<Key, Data> *parent;
    BST<Key, Data> left, right;
};

template <class Key, class Data>
void BST<Key, Data>::add(const Key &key, const Data &data)
{
    BST<Key, Data> *location;
    BSTnode<Key, Data> *parent;
    search(key, parent, location);
    if (!*location)
    {
        //note: C++14 style
        BST<Key, Data> newnode = make_unique<BSTnode<Key, Data>>(key, data);
        // C++11 style
        //        BST<Key,Data> newnode(new BSTnode<Key,Data>(key,data));
        newnode->parent = parent;
        *location = move(newnode);
    };
};

// To learn more about the reference to pointer *& read https://www.codeproject.com/Articles/4894/Pointer-to-Pointer-and-Reference-to-Pointer
template <class Key, class Data>
void BST<Key, Data>::search(const Key &key, BSTnode<Key, Data> *&parent, BST<Key, Data> *&location)
{
    location = this;
    parent = 0;
    // Fixed while location => *location !!!
    while (*location && (*location)->key != key)
    {
        parent = location->get();
        if ((*location)->key < key)
            // location is of BST* type, so (*location) is a BST, but
            // a BST is a unique_ptr so even though it seems like a normal object,
            // you can call the -> operator on it!
            location = &(*location)->right;
        else
            location = &(*location)->left;
    };
};

template <class Key, class Data>
void BST<Key, Data>::rotate(bool left)
{
    if (*this)
    {

        BST<Key, Data> child = move((*this)->getChild(!left));
        if (child)
        {

            BST<Key, Data> subchild = move(child->getChild(left));
            if (subchild)
            {
                (*this)->getChild(!left) = move(subchild);
            }

            child->parent = (*this)->parent;
            (*this)->parent = child.get();
            child->getChild(left) = move(*this);
            *this = move(child);
        }
    }
}

template <class Key, class Data>
void BST<Key, Data>::inorder(std::function<void(const BSTnode<Key, Data> &)> visit) const
{
    if (*this)
    {
        (*this)->left.inorder(visit);
        visit(**this);
        (*this)->right.inorder(visit);
    };
}

template <class Key, class Data>
void BST<Key, Data>::preorder(std::function<void(const BSTnode<Key, Data> &)> visit) const
{
    if (*this)
    {
        visit(**this);
        (*this)->left.preorder(visit);
        (*this)->right.preorder(visit);
    }
}

template <class Key, class Data>
void BST<Key, Data>::postorder(std::function<void(const BSTnode<Key, Data> &)> visit) const
{
    if (*this)
    {
        (*this)->left.postorder(visit);
        (*this)->right.postorder(visit);
        visit(**this);
    }
}

template <class Key, class Data>
void BST<Key, Data>::output(ostream &os) const
{
    inorder([&os](const BSTnode<Key, Data> &node) {
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
bool BST<Key, Data>::repOK() const
{
    if (*this)
    {
        bool isOK = true;
        const Key *previousKey = nullptr;

        inorder([&isOK, &previousKey](const BSTnode<Key, Data> &node) {
            if (!isOK)
            {
                return;
            }
            if (previousKey && (*previousKey > node.key))
            {
                isOK = false;
            }
            if (node.left && (node.left->parent) != &node)
            {
                isOK = false;
            }
            if (node.right && (node.right->parent) != &node)
            {
                isOK = false;
            }
        });
        return isOK;
    }
    else
        return false;
}

template <class Key, class Data>
int BST<Key, Data>::size() const
{
    if (*this)
    {
        return 1 + (*this)->left.size() + (*this)->right.size();
    }
    else
    {
        return 0;
    }
}

template <class Key, class Data>
int BST<Key, Data>::depth() const
{
    if (*this)
    {
        if ((*this)->right && (*this)->left)
        {
            int r = 1 + (*this)->right.depth();
            int l = 1 + (*this)->left.depth();
            // the trick to return the proper length if a node has 2 possible paths down is to make the comparison here
            // instead of trying to keep track of the maximum observed depth value!
            return r > l ? r : l;
        }
        else if ((*this)->right)
        {
            return 1 + (*this)->right.depth();
        }
        else if ((*this)->left)
        {
            return 1 + (*this)->left.depth();
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

template <class Key, class Data>
void BST<Key, Data>::makeImbalanced()
{
    if (*this)
    {
        while ((*this)->left)
        {
           rotate(false);
        }
        if((*this)->right){
            (*this)->right.makeImbalanced();
        }
    }
}

template <class Key, class Data>
void BST<Key, Data>::makeBalanced()
{
    if(*this){
        makeImbalanced();
        makeBalanced_op();
    }
}

template <class Key, class Data>
void BST<Key, Data>::makeBalanced_op() {
    if(*this){
        int depth = this->depth();
        if((*this)->right) {
            for(int i=0;i<(depth/2);i++){
                rotate(true);
            }
        }
        else if((*this)->left){
            for(int i=0;i<(depth/2);i++){
                rotate(false);
            }
        }
        (*this)->left.makeBalanced_op();
        (*this)->right.makeBalanced_op();
    }
}


template <class Key, class Data>
void BST<Key, Data>::pretty_print(int indent) const
{
    if (*this)
    {
        if ((*this)->right)
            (*this)->right.pretty_print(indent + 4);

        if (indent)
        {
            cout << std::setw(indent) << ' ';
        }
        cout << (*this)->key << ',' << (*this)->data << '\n';

        if ((*this)->left)
            (*this)->left.pretty_print(indent + 4);
    }
}

#endif