#ifndef __Splayboom_H
#define __Splayboom_H
#include <cstdlib>
#include <iostream>
#include <queue>
#include <memory>
#include <functional>
#include <fstream>
#include <sstream>
#include <cassert>
#include "zoekboom17.cpp"

using namespace std;

template <class Sleutel, class Data>
class Splayboom: public Boom<Sleutel, Data> {
	public:
		void voegtoe(const Sleutel& sleutel,const Data& data,bool dubbelsToestaan=false);
		Knoop<Sleutel, Data>* zoek(const Sleutel& sleutel); // return pointer naar knoop en niet naar boom omdat ik geen manipulaties op de boom toelaat
	
		
	private:
		void splay(Boom<Sleutel, Data>* huidigeKnoop);
	
};




#endif
