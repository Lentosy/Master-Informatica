#include "prquadtree.h"
#include <iostream>
#include <queue>

void PRQuadtree::schrijf(std::ostream& os) const {
    if(!*this){
        os << "De boom is ledig\n";
        return;
    }

    std::queue<PRKnoop*> BEstack;
    BEstack.emplace(this->get());

    while(!BEstack.empty()){
        // Een knoop is ofwel een blad, ofwel een nietblad
        PRKnoop* huidig = BEstack.front();
        if(huidig->isBlad()){

            PRBlad* huidigBlad = static_cast<PRBlad*>(huidig);
            std::cout << "Blad met punt (" << huidigBlad->x << ", " << huidigBlad->y << ")\n";  
        } else {
            PRNietblad* huidigNietblad = static_cast<PRNietblad*>(huidig);
            
            std::cout << "Inwendige knoop die het gebied opsplitst\n";  
            for(int i = 0; i < 4; i++){
                Knoopptr* kind = &huidigNietblad->kind[i];
                if(*kind){
                    BEstack.emplace(kind->get());
                }
            }
        }
        BEstack.pop();
    }
}

int PRQuadtree::geefDiepte() const {
    if(*this){
        return this->get()->geefDiepte();
    } else {
        return 0;
    }
    
}

Knoopptr* PRQuadtree::zoek(int x, int y) {
    Knoopptr* huidig = this;
    int minX = -this->maxcoordinaat;
    int maxX = this->maxcoordinaat;
    int minY = -this->maxcoordinaat;
    int maxY = this->maxcoordinaat;

    // zoek het blad waarin het punt moet zitten
    while(*huidig && !(*huidig)->isBlad()) {
        int middenX = (minX + maxX) / 2;
        int middenY = (minY + maxY) / 2;

        huidig = (static_cast<PRNietblad*>(huidig->get())->geefKind(x, y, middenX, middenY));

        if(x < middenX) maxX = middenX;
        else minX = middenX;
        
        if(y < middenY) maxY = middenY;
        else minY = middenY;
        
    }
    return huidig;
}

void PRQuadtree::voegToe(int x, int y) {

    Knoopptr* plaats = this->zoek(x, y);
    // als er geen blad bestaat, kan het blad gewoon aangemaakt worden
    if(!*plaats){
        *plaats = (std::unique_ptr<PRKnoop>) std::make_unique<PRBlad>(x, y);
    } else {
        int bladX = static_cast<PRBlad*>(plaats->get())->x;
        int bladY = static_cast<PRBlad*>(plaats->get())->y;
        plaats->reset();
        *plaats = (std::unique_ptr<PRKnoop>) std::make_unique<PRNietblad>();
        this->voegToe(bladX, bladY);
        this->voegToe(x, y);
    }

}