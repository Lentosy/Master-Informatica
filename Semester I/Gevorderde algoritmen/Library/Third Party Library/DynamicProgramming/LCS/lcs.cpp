#include "lcs.hpp"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    LCSsolver solver{"string"};
    int res = solver.get_lcs_length_bu("hung");
    return 0;
}