#include <iostream>
using std::cout;
using std::endl;
#include "bst.hpp"
#include <utility>
using std::move;
#include <memory>
using std::make_unique;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <functional>
using std::function;

void construction_tests();
template <typename T>
void test(const BST<T> &);
template <typename T>
void testvec(const BST<T> &);

int main(int argc, char **argv)
{
    construction_tests();

    // BST<int> bst;
    // bst = move(make_unique<BSTnode<int>>(100));
    // if (bst)
    // {
    //     cout << "Yes" << endl;
    // }
    // else
    //     cout << "No" << endl;

    // bst.add(50);
    // bst.add(20);
    // bst.add(10);
    // bst.add(40);
    // bst.add(50);
    // bst.add(70);
    // bst.add(-10);

    // auto bfsfct = [](int item) { cout << item << endl; };
    // bst.BFS(bfsfct);

    return 0;
}

void construction_tests()
{    
    BST<string> b("hi");
    BST<int> bs(4);
    BST<int> bst(10);
    vector<int> vx = {1};
    BST<vector<int>> bstv(vx);
    test(b);
    test(bs);
    test(bst);
    testvec(bstv);
}
template <typename T>
void test(const BST<T> &bst)
{
    cout << "called test" << endl;
    cout << bst.get()->getItem() << endl;
}

template <typename T>
void testvec(const BST<T> &bst)
{
    cout << "called testvec" << endl;
    for (const auto &x : bst.get()->getItem())
    {
        cout << x << ", ";
    }
    cout << endl;
}