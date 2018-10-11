#include "rzwboom14.cpp"
#include <vector>
#include <string>
#include <stdlib.h>

int huidigeBoom = 1; // loper voor generatie bestandsnamen bij testoperaties

template<class Sleutel>
void tekenBoom(RZWboom<Sleutel>& boom, bool open_bestand) {

	string bestand_binair = std::to_string(huidigeBoom) + "-binair.dot";
	boom.tekenAlsBinaireBoom(bestand_binair.c_str());
	string bestand_234 = std::to_string(huidigeBoom) + "-234.dot";
	boom.tekenAls234Boom(bestand_234.c_str());


	std::vector<string> bestandsnamen = { bestand_binair, bestand_234 };
	for (string b : bestandsnamen) {
		string filename_png = b.substr(0, b.length() - 3) + "png";
		string command_dot = "dot -Tpng " + b + " -o " + filename_png;
		system(command_dot.c_str());
	}

	if (open_bestand) {
		system((bestandsnamen[0].substr(0, bestandsnamen[0].length() - 3 ) + "png").c_str());
	}
	huidigeBoom++;
}


int main() {

	const std::vector<int> sleutels1 = { 0, -4, 30, -5, -2, 15, 45, 8, 23, 37, 52, 4, 11, 19, 26, 34, 40, 48, 60, 1, 5, 9, 13, 16, 21, 24, 28, 31, 35, 39, 43, 46, 51, 54, 61 };
	const std::vector<int> zwarteSleutels1 = { 0, -4, -5, -2, 15, 45, 4, 11, 19, 26, 34, 40, 48, 60 };

	const std::vector<int> sleutels2 = { 10, 3, 15, 2, 6, 12, 18, 4, 8, 11, 13, 16, 20 };
	const std::vector<int> zwarteSleutels2 = { 10, 3, 2, 6, 12, 18, 11, 13, 16, 20 };

	RZWboom<int> boom(sleutels1, zwarteSleutels1);
	/*for (int i = 0; i < 3; i++) {
		boom.voegtoe(sleutels2[i]);
	}*/
	try {
		if (boom.repOK()) {
			std::cout << "Representatie OK\n";
			//boom.voegtoe(-3);
			boom.voegtoe(6);
			tekenBoom(boom, true);
		}
	} catch (const char * ex) {
		std::cout << ex;
	}

	return 0;
}