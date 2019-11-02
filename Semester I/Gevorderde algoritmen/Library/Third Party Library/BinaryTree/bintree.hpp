#ifndef __BINTREE_HPP
#define __BINTREE_HPP

#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;
using std::ifstream;
using std::istream;
using std::ostream;
#include <cassert>
#include <stack>
using std::stack;
#include <functional>
using std::function;
#include <memory>
using std::make_unique;
#include <queue>
using std::queue;
#include <sstream>
using std::stringstream;
#include <string>
#include <map>
#include <vector>
using std::vector;
#include <utility>
using std::move;
using std::pair;
#include <string>
using std::stoi;
using std::string;

template <class T>
class BinTree;

template <class T>
class BinTreeNode;

template <class T>
using BinTreeNodeptr = std::unique_ptr<BinTreeNode<T>>;

enum class Order
{
    Pre,
    In,
    Post
};

#pragma region BinTree class definition
template <class T>
class BinTree : private BinTreeNodeptr<T>
{
    using BinTreeNodeptr<T>::BinTreeNodeptr;

  public:
    BinTree() = default;
    BinTree(const BinTree<T> &) = default;
    BinTree(BinTree<T> &&) = default;
    BinTree<T> &operator=(const BinTree<T> &) = default;
    BinTree<T> &operator=(BinTree<T> &&) = default;
    BinTree<T> &operator=(BinTreeNodeptr<T> &&_nptr)
    {
        // cout << "Called move op with BinTreeNodeptr" << endl;
        this->BinTreeNodeptr<T>::operator=(move(_nptr));
        return *this;
    }

  public:
    int size() const;
    istream &read_from_file(istream &);
    ostream &output_to_stream(ostream &) const;
    ostream &output_to_stream_bfs(ostream &) const;
    void DFS(function<void(T &&)>, function<void(T &&)>, function<void(T &&)>);
    void DFS(function<void(T &&)>, enum Order);
    void BFS(function<void(T &&)>);
    friend istream &operator>>(istream &is, BinTree<T> &bt)
    {
        return bt.read_from_file(is);
    }
    friend ostream &operator<<(ostream &os, const BinTree<T> &bt)
    {
        return bt.output_to_stream(os);
        //return bb.output_to_stream_bfs(os);
    }

  private:
    void recursive_tree_construct(int, vector<BinTree<T>> &&, vector<pair<int, int>> &&);
};
#pragma endregion BinTree class definition

#pragma region BinTreeNode class definition
template <class T>
class BinTreeNode
{
  public:
    BinTreeNode() = default;
    BinTreeNode(const T &_item) : item(_item){};
    BinTreeNode(T &&_item) : item(move(_item)){};
    BinTreeNode<T> &operator=(const T &_other)
    {
        this->item = _other.item;
        return *this;
    };

    BinTreeNode<T> &operator=(T &&_other)
    {
        this->item = move(_other.item);
        return *this;
    };

  private:
    T item;
    BinTree<T> left, right;
    friend class BinTree<T>;
};
#pragma endregion BinTreeNode class definition

template <class T>
int BinTree<T>::size() const
{
    if (!*this)
        return 0;
    else
        return (*this)->left.size() + (*this)->right.size() + 1;
}

template <class T>
istream &BinTree<T>::read_from_file(istream &is)
{
    string line;
    getline(is, line);
    int number_of_nodes = stoi(line);
    vector<BinTree<T>> knopen(number_of_nodes);
    vector<pair<int, int>> children(number_of_nodes);
    vector<bool> no_root(number_of_nodes);
    for (int i = 0; i < number_of_nodes; i++)
    {
        T value;
        int l, r;
        getline(is, line);
        stringstream ss(line); // je kan met stringstream tokens inlezen op voorwaarde dat je zeker bent welk type wanneer komt
        ss >> value >> l >> r; // hier weet je zeker dat je value van T type is, in ons vb gaat dat een string zijn, gevolgd door 2 ints l en r
        knopen[i] = move(make_unique<BinTreeNode<T>>(value));
        children[i] = {l, r}; // gebruik initializer list om het pair in te vullen
        // terwijl je overloopt, als je knopen tegenkomt die children hebben ( dwz r of l != -1) dan kunnen die children in geen geval de root knoop zijn -> no_root[r of l] = true;
        if (l != -1)
        {
            no_root[l] = true;
        }
        if (r != -1)
        {
            no_root[r] = true;
        }
    }

    int root; //nadat we alle knopen hebben ingelezen gaan we op zoek naar wie wel de root is, er is maar 1 element in de no_root tabel die false heeft als waarde. De knoop op die index is de root
    for (int i = 0; i < number_of_nodes; i++)
    {
        if (!no_root[i])
        {
            root = i;
        }
    }

    recursive_tree_construct(root, move(knopen), move(children));

    this->operator=(move(knopen[root]));
    return is;
}

template <class T>
void BinTree<T>::recursive_tree_construct(int i, vector<BinTree> &&knopen, vector<pair<int, int>> &&children)
{
    if (children[i].first != -1 && children[i].second != -1)
    {
        recursive_tree_construct(children[i].first, move(knopen), move(children));
        recursive_tree_construct(children[i].second, move(knopen), move(children));
        knopen[i]->left = move(knopen[children[i].first]);
        knopen[i]->right = move(knopen[children[i].second]);
    }
    else if (children[i].first != -1)
    {
        recursive_tree_construct(children[i].first, move(knopen), move(children));
        knopen[i]->left = move(knopen[children[i].first]);
    }
    else if (children[i].second != -1)
    {
        recursive_tree_construct(children[i].second, move(knopen), move(children));
        knopen[i]->right = move(knopen[children[i].second]);
    }
}

template <class T>
ostream &BinTree<T>::output_to_stream(ostream &os) const
{
    if ((*this))
    {
        return this->output_to_stream_bfs(os);
    }
    return os;
}

template <class T>
ostream &BinTree<T>::output_to_stream_bfs(ostream &os) const
{
    if ((*this))
    {
        os << size() << endl;
        queue<BinTreeNode<T> *> ATW; // FIFO: een lijst met BinTreeNode<T>* elementen
        ATW.push(this->get());       // je moet van de huidige boom de inhoud van de knoop op
        int kindnr = 1;
        BinTreeNode<T> *current = ATW.front();
        while (current != 0)
        {
            os << current->item << ' ';
            if (!current->left)
                os << "-1 ";
            else
            {
                os << kindnr++ << ' ';
                ATW.push(current->left.get());
            }
            if (!current->right)
                os << "-1\n";
            else
            {
                os << kindnr++ << '\n';
                ATW.push(current->right.get());
            }
            ATW.pop();
            if (ATW.front() != 0)
                current = ATW.front();
            else
                current = 0;
        }
    }
    return os;
}

template <class T>
void BinTree<T>::DFS(function<void(T &&)> preorder, function<void(T &&)> inorder, function<void(T &&)> postorder)
{

    if ((*this) != 0)
    {
        stack<pair<BinTreeNode<T> *, int>> ATW;
        ATW.emplace((*this).get(), 1);
        while (!ATW.empty())
        {
            BinTreeNode<T> *current = ATW.top().first;
            int pass = ATW.top().second;
            ATW.top().second++;
            switch (pass)
            {
            case 1:
                preorder(move(current->item));
                if (current->left)
                    ATW.emplace(current->left.get(), 1);
                break;
            case 2:
                inorder(move(current->item));
                if (current->right)
                    ATW.emplace(current->right.get(), 1);
                break;
            case 3:
                postorder(move(current->item));
                ATW.pop();
                break;
            }
        }
    }
}

template <typename T>
void BinTree<T>::DFS(function<void(T &&)> orderfct, Order ord)
{

    if ((*this) != 0)
    {
        stack<pair<BinTreeNode<T> *, int>> ATW;
        ATW.emplace(this->get(), 1);
        while (!ATW.empty())
        {
            BinTreeNode<T> *current = ATW.top().first;
            int pass = ATW.top().second;
            ATW.top().second++;
            switch (pass)
            {
            case 1:
                if (ord == Order::Pre)
                {
                    orderfct(move(current->item));
                }
                if (current->left)
                {
                    ATW.emplace(current->left.get(), 1);
                }
                break;
            case 2:
                if (ord == Order::In)
                {
                    orderfct(move(current->item));
                }
                if (current->right)
                {
                    ATW.emplace(current->right.get(), 1);
                }
                break;
            case 3:
                if (ord == Order::Post)
                {
                    orderfct(move(current->item));
                }
                ATW.pop();
                break;
            }
        }
    }
}

template <typename T>
void BinTree<T>::BFS(function<void(T &&)> fct)
{
    if (*this)
    {
        queue<BinTreeNode<T> *> ATW;
        ATW.emplace(this->get());
        while (!ATW.empty())
        {
            BinTreeNode<T> *current = ATW.front();
            fct(move(current->item));
            if (current->left)
            {
                ATW.emplace(current->left.get());
            }
            if (current->right)
            {
                ATW.emplace(current->right.get());
            }
            ATW.pop();
        }
    }
}

#endif