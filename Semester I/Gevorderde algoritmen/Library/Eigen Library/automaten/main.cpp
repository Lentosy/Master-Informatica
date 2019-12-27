#include "regexp11.h"
#include "thompsonna.h"


int main(void){
    Regexp regexp("(a|b)*a(a|b)");
    ThompsonNA na(regexp);
    na.teken("NA.DOT");
}