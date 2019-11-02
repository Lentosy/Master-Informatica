#include "rbtree.hpp"
#include "rbnode.hpp"

#include <iostream>
#include <memory>

using namespace std;

void creationTest();

int main(int argc, char **argv)
{
    creationTest();
    RBtree<int, int> t1(20, 20, Color::BLACK);
    t1.pretty_print();
    cout << endl;
    t1.insert_bottom_up(30, 30);
    t1.pretty_print();
    cout << endl;
    t1.insert_bottom_up(40, 40);
    t1.pretty_print();
    cout << endl;
    t1.insert_bottom_up(10, 10);
    t1.pretty_print();
    cout << endl;
    t1.insert_bottom_up(15, 15);
    t1.pretty_print();
    cout << endl;
    t1.insert_bottom_up(50, 50);
    t1.pretty_print();
    cout << endl;
    return 0;
}

void creationTest()
{
    RBtree<int, int> t1(10, 10, Color::BLACK);
    RBtree<int, int> t2;
    t2 = t1;
    RBtree<int, int> t3 = t2;
    RBtree<int, int> t4;
    t4 = move(t3);
    RBtree<int, int> t5 = move(t4);
}