#include "btree.hpp"
#include <iostream>

using namespace std;

int main(int argc, char ** argv) {
    int x=5;
    int y;
    y = move(x);
    
    BTree<int,int> t1(2);
    t1.insert_bottom_up(1,1);   
    t1.insert_bottom_up(2,2);
    t1.insert_bottom_up(3,3);
    t1.insert_bottom_up(4,4);
    t1.insert_bottom_up(5,5);
    t1.insert_bottom_up(6,6);
    t1.insert_bottom_up(7,7);

    
    return 0;
}