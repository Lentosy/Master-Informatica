#include "zoekboom17.cpp"


int main(void){
    Boom<int, int> boom;
    boom.voegtoe(7, 'x');
    boom.voegtoe(8, 'a');
    boom.voegtoe(9, 'n');
    boom.voegtoe(10, 'd');
    boom.voegtoe(11, 'r');
    boom.voegtoe(12, 'o');
    boom.schrijf(std::cout);
    return 0;
}