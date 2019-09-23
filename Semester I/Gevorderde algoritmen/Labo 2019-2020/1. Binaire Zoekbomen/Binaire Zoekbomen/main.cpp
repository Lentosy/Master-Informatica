#include "zoekboom17.cpp"

#include <iostream>
#include <string>
using std::string;

int main(void) {
	ZoekBoom<int, char> boom = std::make_unique<ZoekKnoop<int, char>>(5, 'p');


	boom.voegtoe(3, 'l');
	boom.voegtoe(2, 'a');
	boom.voegtoe(4, 'b');
	boom.voegtoe(6, 'g');

	//boom.maakOnevenwichtig(Richting::LINKS);
	std::cout << "Boom ok? " << boom.repOK() << "\n";
	boom.schrijf(std::cout);
	boom.teken("boom.dot");


	return 0;


}