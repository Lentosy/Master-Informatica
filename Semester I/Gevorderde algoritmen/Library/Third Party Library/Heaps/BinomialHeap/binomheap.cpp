#include "binomheap.hpp"
#include <iostream>

using namespace std;

int main(int argc, char ** argv){
    BinomHeap<int,int>b1;    
    b1.put(10,10);    
    b1.put(50,50);
    b1.put(100,100);
    
    BinomHeap<int,int>b2;
    b2.put(30,30);
    b2.put(20,20);
    b2.put(5,5);
    return 0;
}