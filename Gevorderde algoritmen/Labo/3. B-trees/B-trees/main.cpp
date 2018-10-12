#include "schijf.h"
#include "btree.cpp"
#include "bknoop.cpp"
#include <string>

const int GROOTTE = 8;

int main(void) {
	// knoop heeft string als sleutel ( de woorden )
	//		, int als data ( de frequentie )
	//      , maximum GROOTTE aantal sleutels
	Schijf<Bknoop<std::string, int, GROOTTE>> schijf;
	Btree<std::string, int, GROOTTE> boom(schijf);




	try {
		
	} catch (const char * ex) {
		std::cout << ex;
	}

	return 0;
}