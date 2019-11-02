#include "multigraph.hpp"
#include "hierholzer.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

void test_hierholzer();

int main(int argc, char **argv)
{
    test_hierholzer();
    return 0;
}

void test_hierholzer()
{
    MultiGraph<DirectionType::UNDIRECTED> G(16);
    G.voegVerbindingToe(0, 1);
    G.voegVerbindingToe(0, 3);
    G.voegVerbindingToe(5, 1);
    G.voegVerbindingToe(2, 1);
    G.voegVerbindingToe(4, 1);
    G.voegVerbindingToe(2, 4);
    G.voegVerbindingToe(2, 5);
    G.voegVerbindingToe(3, 2);
    Hierholzer H(G);
    for(const auto & x:H.path){
        cout<<x<<' ';
    }
}