#ifndef __PRQUADTREE_H__
#define __PRQUADTREE_H__
#include <cassert>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <stack>
using std::unique_ptr;

/*****************************************************************************
    Bevat de headers en code voor een PRQuadtree
    en voor de abstracte klasse PRKnoop met deelklassen Blad en Nietblad
    
*****************************************************************************/


class PRKnoop;
typedef unique_ptr<PRKnoop> Knoopptr;
class PRQuadtree;



class PRQuadtree: public Knoopptr {
public:
    using Knoopptr::unique_ptr;
    PRQuadtree(int a):maxcoordinaat{a}{};
    PRQuadtree( Knoopptr&& a):Knoopptr(move(a)){};
    PRQuadtree& operator=(Knoopptr&& a){
        Knoopptr::operator=(move(a));
        return *this;
    };
    void preEnPostOrder(std::function<void(PRKnoop*)>& bezoekPre,std::function<void(PRKnoop*)>& bezoekPost) const;
    

    //te implementeren
    std::ostringstream dotCode() const;
    void schrijf(std::ostream& os) const;
    void voegToe(int x, int y);
    int geefDiepte() const;
    Knoopptr* zoek(int x, int y);
//de PRquadtree kan alleen punten bevatten met
//-maxcoordinaat <= x < maxcoordinaat
//-maxcoordinaat <= y < maxcoordinaat
    int maxcoordinaat;
};

//Opmerking: om de functies specifiek aan een deelklasse te kunnen gebruiken moet je soms een
//static_cast doen, zoals in
//  PRKnoop* knoopptr=...;
//  if (knoopptr!=nullptr && knoopptr->isBlad() && static_cast<PRBlad*>(knoopptr)->x == 5)
class PRKnoop{
public:
    virtual bool isBlad()=0;
    virtual int geefDiepte()=0;
};
class PRBlad:public PRKnoop{
public:
    PRBlad(int x,int y):x{x},y{y}{};
    virtual bool isBlad(){ return true;}
    virtual int geefDiepte(){
        return 1;
    };
    int x,y;
    
};
class PRNietblad:public PRKnoop{
public:
    virtual int geefDiepte() {
        std::vector<int> dieptes;
        for(int i = 0; i < 4; i++){
            Knoopptr* kind = &(this->kind[i]);
            if(*kind){
                dieptes.push_back((*kind)->geefDiepte());
            }
        } 
        
        return 1 + *std::max_element(dieptes.begin(), dieptes.end());
    }
    virtual bool isBlad(){ return false;}
    int geefAantalKinderen(){
         int aantal=0;
         for (int i=0; i<4; i++ ){
             if (kind[i])
                ++aantal;
         }
         return aantal;
    };
    //xc, yc: co"ordinaten van het centrum van het gebied
    Knoopptr* geefKind(int x, int y, int xc, int yc){
        int xindex=(x<xc? WEST : OOST);
        int yindex=(y<yc? NOORD : ZUID);
        return &kind[xindex+yindex];
    };
    static const int OOST, WEST, NOORD, ZUID;
    Knoopptr kind[4];//indexeren met windrichting (bv. kind[NOORD+WEST] bevat punten
                       //met x en y kleiner dan grenswaarde)
                       //leeg gebied: nulpointer
};

void PRQuadtree::preEnPostOrder(std::function<void(PRKnoop*)>& bezoekPre,std::function<void(PRKnoop*)>& bezoekPost) const{
        enum staat {pre,post};
        std::stack<std::pair<PRKnoop*,staat>> DEstack;//bevat alleen niet-nulpointers
        if (*this)
            DEstack.emplace(this->get(),pre);
        while (!DEstack.empty()){
            // auto [nuknoop,nustaat]=DEstack.top(); C++17 feature, bindt automatisch pair.first en pair.second naar variabele
            std::pair<PRKnoop*, staat>& huidig = DEstack.top();
            PRKnoop* nuknoop = huidig.first;
            staat nustaat = huidig.second;
            if (nustaat==pre){
                bezoekPre(nuknoop);
                DEstack.top().second=post;
                if (!nuknoop->isBlad()){
                    for (int i=0; i<4; i++ ){
                        Knoopptr* kind=&(static_cast<PRNietblad*>(nuknoop)->kind[i]);
                        if (*kind)
                            DEstack.emplace(kind->get(),pre);
                    };
                };
            } else{
                bezoekPost(nuknoop);
                DEstack.pop();
            };
        };

    };

const int PRNietblad::OOST=0;
const int PRNietblad::WEST=1;
const int PRNietblad::NOORD=0;
const int PRNietblad::ZUID=2;
#endif

