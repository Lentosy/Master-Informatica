#include "schijf.h"
#include "btree.cpp"
#include <string>

int main(void) {
	Schijf<Bknoop<std::string, int, 8>> schijf;
	Btree<std::string, int, 8> boom(schijf);

	return 0;
}