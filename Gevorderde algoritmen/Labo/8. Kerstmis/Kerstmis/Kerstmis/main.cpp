
#include "suffixboom.h"


int main(void) {
	Sboom boom;
	std::ifstream verhaal("test.txt");
	std::string woord;
	while (verhaal >> woord) {
		boom.voegtoe(woord, 200);
	}
	boom.print(std::cout);
	return 0;
}