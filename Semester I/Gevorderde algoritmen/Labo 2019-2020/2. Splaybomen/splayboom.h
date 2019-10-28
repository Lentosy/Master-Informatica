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
class SplayboomBottomUp: public Boom<Sleutel, Data> {
	public:
		void voegtoe(const Sleutel& sleutel, const Data& data, bool dubbelsToestaan=false);
		Knoop<Sleutel, Data>* zoek(const Sleutel& sleutel); // return pointer naar knoop en niet naar boom omdat ik geen manipulaties op de boom wil toelaten
		
	private:
		void splay(Boom<Sleutel, Data>* huidigeKnoop);

		void zig(Boom<Sleutel, Data>*& knoop, bool naarLinks);
		void zigzig(Boom<Sleutel, Data>*& knoop, bool naarLinks);
		void zigzag(Boom<Sleutel, Data>*& knoop, bool naarLinks);
};

template <class Sleutel, class Data>
class SplayboomTopDown: public Boom<Sleutel, Data> {
	public:
		using Boom<Sleutel,Data>::voegtoe;
		//void voegtoe(const Sleutel& sleutel, const Data& data, bool dubbelsToestaan=false);
		Knoop<Sleutel, Data>* zoek(const Sleutel& sleutel); 

	private:
		void zig(Boom<Sleutel, Data>& L, Boom<Sleutel, Data>*& Linvoer, Boom<Sleutel, Data>& R, Boom<Sleutel, Data>*& Rinvoer, bool kindZitLinks);
		void zigzig(Boom<Sleutel, Data>& L, Boom<Sleutel, Data>*& Linvoer, Boom<Sleutel, Data>& R, Boom<Sleutel, Data>*& Rinvoer, bool kindZitLinks);
		void zigzag(Boom<Sleutel, Data>& L, Boom<Sleutel, Data>*& Linvoer, Boom<Sleutel, Data>& R, Boom<Sleutel, Data>*& Rinvoer, bool kindZitLinks);

};




#endif
