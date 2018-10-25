
#include "Tree2D.h"
#include "Point.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

void testTree() {
	std::vector<int> xValues = { 3, 17, 13, 6, 9, 2, 10 };
	std::vector<int> yValues = { 6, 15, 15, 12, 1, 7, 19 };

	Tree2D tree;
	for (int i = 0; i < xValues.size(); i++) {
		tree.add(Point(xValues[i], yValues[i]));
	}

	tree.print(std::cout);
}

void populateTreeFromFile(Tree2D& tree, const char * filename) {
	std::ifstream in(filename);

	int x, y;
	while (!in.eof()) {
		in >> x >> y;
		tree.add(Point(x, y));
	}

	in.close();

}

void Tree2DToDot(Tree2D& tree, int maxdepth) {
	tree.draw("2dtree.dot", maxdepth);
	std::string command_dot = "dot -Tpng 2dtree.dot -o 2dtree.png";
	system(command_dot.c_str());
	system("2dtree.png");
}

int main(void) {
	Tree2D tree;
	populateTreeFromFile(tree, "puntenverzameling.dat");
	Tree2DToDot(tree, 6);

	for (int i = 0; i < 200; i += 10) {
		for (int j = 0; j < 200; j += 10) {
			int amountVisited = 0;
			Point pointToFind = Point(i, j);
			Point foundPoint = tree.search(pointToFind, amountVisited);
			std::cout << pointToFind << " has neighbour " << foundPoint << ", " << amountVisited << " visited nodes\n";


		}
	}

	return 0;
}