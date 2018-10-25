
#include "KDTree.h"
#include <iostream>


int main(void) {
	KDTree tree;

	
	Point p = Point(3, 5);
	tree.add(p);
	tree.add(p);
	tree.print(std::cout);
	//tree.add()


	return 0;
}