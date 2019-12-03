#include "saisclass.h"
#include <iostream>
#include <string>
int main(void){
    std::string T("banana");
    SAIS suffixarray((unsigned char *)T.c_str(), T.size());

}