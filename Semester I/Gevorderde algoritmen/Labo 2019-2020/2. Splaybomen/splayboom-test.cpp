#include "splayboom.cpp"
#include <iostream>
#include <string>
#include <fstream>

void testSplay1Tot100EnZoek1(){
    Splayboom<int, int> boom;
    for(int i = 1; i < 100; i++){
        boom.voegtoe(i, i);
    }
    
    boom.teken("dot/boom-1-tot-100.dot");
    system("dot -Tpng dot/boom-1-tot-100.dot -o dot/boom-1-tot-100.jpg");
    boom.zoek(1);
    boom.teken("dot/boom-1-tot-100-zoek-1.dot");
    system("dot -Tpng dot/boom-1-tot-100-zoek-1.dot -o dot/boom-1-tot-100-zoek-1.jpg");
}


void testShakespeare() {
    Splayboom<string, int> frequentieBoom;
    std::ifstream file("shakespeare.txt");
    std::string word;
    int c = 0;
    
    while(file >> word && c < 100){
       // nog een BUG ergens, probably in splay
        Knoop<string, int>* woordKnoop = frequentieBoom.zoek(word);
        if(woordKnoop != nullptr){
            woordKnoop->data++;
        } else {
            frequentieBoom.voegtoe(word, 1, false);
        }
        c++;
    }
    
    frequentieBoom.teken("dot/shakespeare.dot");
    system("dot -Tpng dot/shakespeare.dot -o dot/shakespeare.jpg && dot/shakespeare.jpg");

}


int main(void){
    testSplay1Tot100EnZoek1();    

    return 0;
}