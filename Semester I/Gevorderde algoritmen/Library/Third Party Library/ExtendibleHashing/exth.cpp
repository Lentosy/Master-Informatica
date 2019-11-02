#include "exth.hpp"
#include <iostream>

using namespace std;

int main(int argc, char ** argv) {
    ExtendibleHashTable<int,int> ht(1);
    ht.insert(0,0);
    ht.insert(1,1);
    ht.insert(2,2);
    ht.insert(3,3);
    ht.insert(4,4);
    ht.insert(5,5);
    ht.insert(7,7);
    ht.insert(10,10);
    ht.insert(16,16);
    ht.insert(20,20);
    return 0;
}