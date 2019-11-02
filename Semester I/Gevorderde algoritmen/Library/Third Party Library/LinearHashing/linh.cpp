#include "linh.hpp"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    LinearHashTable<int,int> linht(0.9,2);
    linht.insert(0,0);
    linht.insert(2,2);
    linht.insert(1,1);
    linht.insert(3,3);
    linht.insert(5,5);
    linht.insert(4,4);
    linht.insert(6,6);
    linht.insert(8,8);
    linht.insert(7,7);
    linht.insert(12,12);

    return 0;
}