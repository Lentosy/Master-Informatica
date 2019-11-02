#include "kdtree.hpp"
#include "kdnode.hpp"
#include <iostream>
#include <random>
#include <tuple>

const int TEST_SIZE = 10;

using namespace std;

int main(int argc, char **argv)
{
    KdTree<int, int, int, int> t1(4);    
    vector<tuple<int, int, int, int>> data;
    tuple<int,int,int,int> tx{1,5,1,1};
    tuple<int,int,int,int> ty{2,2,5,2};
    tuple<int,int,int,int> tz{3,3,9,3};
    t1.insert(move(tx));
    t1.insert(move(ty));
    t1.insert(move(tz));
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);
    for (int i = 0; i < TEST_SIZE; i++)
    {
        data.emplace_back(tuple<int, int, int, int>(dis(gen), dis(gen), dis(gen), dis(gen)));
    }
    t1.insert(move(data));
    cout << t1.depth() << endl;
    cout<<t1.size()<<endl;
    return 0;
}