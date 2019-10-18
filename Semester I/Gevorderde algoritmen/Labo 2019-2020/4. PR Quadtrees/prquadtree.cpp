#include "prquadtree.h"
#include <cstdlib>

void PRQuadtree::voegToe(int x, int y) {
    if(!*this){
        (*this) = (std::unique_ptr<PRKnoop>) std::make_unique<PRBlad>(x, y);
    } else {
        Knoopptr* plaats = zoek(x, y);
        

    }

    std::cout << static_cast<PRBlad*>(&*(*this))->x;
}


Knoopptr* PRQuadtree::zoek(int x, int y) {
    if(std::abs(x) > this->maxcoordinaat || std::abs(y) > this->maxcoordinaat){
        return nullptr;
    }

    int minX = -this->maxcoordinaat;
    int maxX = this->maxcoordinaat;
    int minY = -this->maxcoordinaat;
    int maxY = this->maxcoordinaat;

    
    Knoopptr* huidige = this;
    while(!(*huidige)->isBlad()){
        int middenX = (minX + maxX) / 2;
        int middenY = (minY + maxY) / 2;
        huidige = static_cast<PRNietblad*>(huidige->get())->geefKind(x, y, middenX, middenY);

        if(x < middenX){
            maxX = middenX;
        } else {
            minX = middenX;
        }

        if(y < middenY){
            maxY = middenY;
        } else {
            minY = middenY;
        }
    }  

    return huidige;

}