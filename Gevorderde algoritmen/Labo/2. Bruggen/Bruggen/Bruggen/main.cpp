#include "bruggen.h"

int main(int argc, char * argv[]) {
	
	if (!argv[1]) {
		std::cerr << "Geen argument opgegeven\n";
		exit(1);
	}
	

	try {
		Bruggen b(argv[1]);
		b.printOplossing(std::cout);
	} catch (std::string ex) {
		std::cout << ex;
	}

	return 0;
}

