#include "bruggen.h"
#include <iostream>
#include <fstream>
#include <sstream>
int main(int argc, char * argv[]) {

	if (argc < 3) {
		std::cerr << "geef het databestand en het outputbestand op.\n";
		exit(1);
	}
	std::ofstream output(argv[2]);
	try {
		Bruggen b(argv[1]);
		b.printOplossing(output);
	} catch (std::string ex) {
		std::cout << ex;
	}

	return 0;
}

