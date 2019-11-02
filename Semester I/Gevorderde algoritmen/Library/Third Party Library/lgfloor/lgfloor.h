
#ifndef LGFLOOR_H
#define LGFLOOR_H

#include <cassert>
#include <iostream>

//
// Schrijf een functie unsigned int lgfloor(long unsigned int) die
// zo efficiënt mogelijk log2(n), naar beneden afgerond, berekent via binair
// zoeken. Uiteraard gebruik je nergens (ook niet impliciet)
// vlottendekommagetallen.
//
// Tip: het kan in 8 stappen, want 2^8 = 256.
//
//   h      l
//   78653210
// 0b00100001 = 65
//
// See https://stackoverflow.com/questions/55378046/trouble-with-finding-floorlog2int-using-binary-search-in-olog2amount-bits

int lgfloor(unsigned long long int value)
{
    assert(value > 0);

    int high = (sizeof(value) * 8);
    int low = 0;

    while (high > (low + 1))
    {
        int mid = (low + ((high - low) / 2));
        unsigned long long int guess = 1;
        guess <<= mid;

        if (value < guess)
        {
            high = mid;
        }
        else
        {
            low = mid;
        }
    }

    return low;
}

#endif