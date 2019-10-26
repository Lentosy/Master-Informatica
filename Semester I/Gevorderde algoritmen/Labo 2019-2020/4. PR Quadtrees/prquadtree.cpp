#include "prquadtree.h"
#include <iostream>
#include <sstream>
#include <queue>


std::ostringstream PRQuadtree::dotCode() const {
    std::ostringstream code;
    code << "digraph G {\n";
    if(!*this){
        code << "null[shape=point]\n";
    } else {
        std::queue<std::pair<PRKnoop*, int>> BEqueue;
        int knoopteller = 0;
        BEqueue.emplace(this->get(), knoopteller);

        while(!BEqueue.empty()){
            std::pair<PRKnoop*, int> f = BEqueue.front();
            PRKnoop* huidig = f.first;
            int ouder = f.second;
            knoopteller++;
            
            if(ouder > 0){
                code << "knoop" << ouder << " -> knoop" << knoopteller << "\n";
            }
            
            if(!huidig){ // nullknoop
                code << "knoop" << knoopteller << "[shape=point]\n" ;
            }
            else if(huidig->isBlad()){ // bladknoop
                PRBlad* huidigBlad = static_cast<PRBlad*>(huidig);
                code << "knoop" << knoopteller << "[shape=square, label=\"" << huidigBlad->x << "," << huidigBlad->y << "\"]\n";            
            } else { // inwendigeknoop
                PRNietblad* huidigNietblad = static_cast<PRNietblad*>(huidig);
                code << "knoop" << knoopteller << "[label=\"\"]\n";

                // kinderen toevoegen aan de queue
                for(int i = 0; i < 4; i++){
                    Knoopptr* kind = &huidigNietblad->kind[i];
                    if(*kind){
                        BEqueue.emplace(std::make_pair(kind->get(), knoopteller));
                    } else {
                        BEqueue.emplace(std::make_pair(nullptr, knoopteller));
                    }
                }
            }

            BEqueue.pop();
        }

    }
    code << "}";
    return code;
}

void PRQuadtree::schrijf(std::ostream& os) const {
    if(!*this){
        os << "De boom is ledig\n";
        return;
    }

    std::queue<PRKnoop*> BEqueue;
    BEqueue.emplace(this->get());

    while(!BEqueue.empty()){
        // Een knoop is ofwel een blad, ofwel een nietblad
        PRKnoop* huidig = BEqueue.front();
        if(huidig->isBlad()){

            PRBlad* huidigBlad = static_cast<PRBlad*>(huidig);
            std::cout << "Blad met punt (" << huidigBlad->x << ", " << huidigBlad->y << ")\n";  
        } else {
            PRNietblad* huidigNietblad = static_cast<PRNietblad*>(huidig);
            
            std::cout << "Inwendige knoop die het gebied opsplitst\n";  
            for(int i = 0; i < 4; i++){
                Knoopptr* kind = &huidigNietblad->kind[i];
                if(*kind){
                    BEqueue.emplace(kind->get());
                }
            }
        }
        BEqueue.pop();
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
    if(x > this->maxcoordinaat || -x > this->maxcoordinaat || y > this->maxcoordinaat || -y > this->maxcoordinaat){
        throw  "De opgegeven coördinaten liggen niet binnen de rechthoek\n";
    }
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