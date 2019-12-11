#include "GaleShapley.h"
#include <iostream>


int main(void) {
    std::vector<std::vector<int>> m(4, std::vector<int>(4));
    std::vector<std::vector<int>> v(4, std::vector<int>(4));


    m[0] = {1, 0, 2, 3};
    m[1] = {3, 0, 1, 2};
    m[2] = {0, 2, 1, 3};
    m[3] = {1, 2, 0, 3};

    v[0] = {0, 2, 1, 3};
    v[1] = {2, 3, 0, 1};
    v[2] = {3, 1, 2, 0};
    v[3] = {2, 1, 0, 3};

    

    GaleShapley gs(m, v);
    std::vector<int> koppeling = gs.koppel();

    for(int i = 0; i < koppeling.size(); i++){
        std::cout << "(" << i << ", " << koppeling[i] << ")\n";
    }
}