#include "minheap.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

const size_t TEST_SIZE = 16;

int main(int argc, char ** argv) {    
    vector<pair<int,double>> data;
    for(int i=TEST_SIZE-1;i>=0;i--) {
        data.emplace_back(make_pair(i,i*2.0));
    }
    MinHeap<int,double> minheap(move(data));
    return 0;
}