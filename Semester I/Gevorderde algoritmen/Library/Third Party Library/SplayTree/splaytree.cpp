#include "splaynode.hpp"
#include "splaytree.hpp"
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    int i = 0;
    SplayTree<int, int> t1(50, 50);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();
    t1.insert_bottom_up(100, 100);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();
    t1.insert_bottom_up(75, 75);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();
    t1.insert_bottom_up(25, 25);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();
    t1.insert_bottom_up(0, 0);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();
    t1.insert_bottom_up(40, 40);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();
    t1.insert_bottom_up(200, 200);

    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();

    t1.search(200);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();

    cout << i++ << '.' << " predecessor " << '\n'
         << *(t1.predecessor(&t1)->get())
         << '\t'
         << endl;

    cout << i++ << '.' << " largest " << '\n'
         << *(t1.largest(&t1)->get()) << '\t' << endl;
    cout << i++ << '.' << " smallest " << '\n'
         << *(t1.smallest(&t1)->get()) << '\t' << endl;

    auto [left, right] = t1.split(0);
    cout << i++ << '.' << '\n'
         << endl;
    left.pretty_print();

    cout << i++ << '.' << '\n'
         << endl;
    right.pretty_print();

    t1 = left.join(&left, &right);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();

    t1.delete_bottom_up(0);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();

    t1.delete_bottom_up(40);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();

    t1.delete_bottom_up(50);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();

    t1.delete_bottom_up(200);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();

    t1.insert_top_down(0, 0);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();

    t1.insert_top_down(40, 40);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();

    t1.insert_top_down(50, 50);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();

    t1.insert_top_down(200, 200);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();

    return 0;
}