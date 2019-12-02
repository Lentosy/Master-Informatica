#include "regexp11.h"
#include "thompsonna.h"
#include <iostream>
int main(void) {
    Regexp r("abcd|ckef");
    ThompsonNA na(r);
    na.schrijf(std::cout);
    na.teken("NA.dot");
}