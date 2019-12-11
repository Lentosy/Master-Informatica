#include "GaleShapley.h"
#include <iostream>
#include <cassert>

int main(void) {
    std::vector<std::vector<int>> m(5, std::vector<int>(5));
    std::vector<std::vector<int>> v(5, std::vector<int>(5));

    // Voorbeeld https://youtu.be/0m_YW1zVs-Q, t=114
    int A = 0;
    int B = 1;
    int C = 2;
    int D = 3;
    int E = 4;

    int L = 0;
    int M = 1;
    int N = 2;
    int O = 3;
    int P = 4;

    m[A] = {O, M, N, L, P};
    m[B] = {P, N, M, L, O};
    m[C] = {M, P, L, O, N};
    m[D] = {P, M, O, N, L};
    m[E] = {O, L, M, N, P};

    v[L] = {D, B, E, C, A};
    v[M] = {B, A, D, C, E};
    v[N] = {A, C, E, D, B};
    v[O] = {D, A, C, B, E};
    v[P] = {B, E, A, C, D};

    

    GaleShapley gs(m, v);
    std::vector<int> koppeling = gs.koppel();
    std::vector<int> oplossing = {O, P, N, M, L}; // de oplossing die zou gegeven moeten worden

    for(int i = 0; i < koppeling.size(); i++){
        std::cout << "(" << i << ", " << koppeling[i] << ")\n";
        assert(koppeling[i] == oplossing[i]);
    }
}