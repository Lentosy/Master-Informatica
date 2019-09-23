#include <iostream>


int main(void) {


	int g = 5;
	int* pg = &g;

	std::cout << g << " - " << *pg << " - " << &g << " - " << pg <<  "\n";

	return 0;
}