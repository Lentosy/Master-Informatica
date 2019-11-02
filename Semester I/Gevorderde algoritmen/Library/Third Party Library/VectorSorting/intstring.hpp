
#ifndef __INTSTRING_HPP
#define __INTSTRING_HPP
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
using std::string;
/**
 * Intstring
 * 
 * inheritance from std::string is safe because we don't add fields that require dynamic memory mgmt
 * */

class Intstring : public string
{
  public:
    Intstring(int a = 0) : string("0000000000")
    {
        int modulo = 1000000000;
        for (int i = 0; i < 10; i++)
        {
            this->operator[](i) = '0' + a / modulo;
            a = a % modulo;
            modulo /= 10;
        }
    };
};

#endif
