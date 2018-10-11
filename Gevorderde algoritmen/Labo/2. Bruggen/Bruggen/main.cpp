#include "bruggen.cpp"

int main(int argc, char * argv[]) {
	
	/*if (!argv[1]) {
		std::cerr << "Geen argument opgegeven\n";
		exit(1);
	}*/
	
	std::string bestand = "versnickt.dat";

	try {
		Bruggen b(bestand.c_str());
		b.printOplossing(std::cout);
	} catch (std::string ex) {
		std::cout << ex;
	}


	int x;
	std::cin >> x;
	return 0;
}

