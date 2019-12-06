#include "regexp11.h"
#include "zoekda.h"
#include "thompsonna.h"
#include <iostream>
#include <string>
int main(void) {
    Regexp r("abcd|ckef");
    ThompsonNA na(r);
    std::string T = "xandro bert glenn";
    ZoekDA zoekDA(na);
    std::string output = zoekDA.zoek(T) ? "gevonden" : "niet gevonden";
    std::cout << output << std::endl;
    //na.schrijf(std::cout);
    //na.teken("NA.dot");
}