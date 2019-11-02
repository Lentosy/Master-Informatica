#include "galeshapley.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char ** argv) {
    vector<vector<int>> m_pref = {
        {0,2,1},
        {2,0,1},
        {2,1,0}
    };

    vector<vector<int>> f_pref = {
        {0,1,2},
        {0,2,1},
        {1,0,2}
    };
    
    GaleShapley solver(m_pref,f_pref);
    for(const auto& pair: solver.matches){
        cout<<"M "<<pair.second<<" F "<<pair.first<<endl;
    }    

    return 0;
}