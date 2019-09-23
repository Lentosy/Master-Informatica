#include "binarytree.h"
#include <iostream>
#include <memory>


int main(void) {

	BinaryTree<int, int> tree = std::make_unique<Node<int, int>>(3, 9);
	tree.add(2, 2 * 2);
	tree.add(4, 4 * 4);


	tree.write(std::cout);
	tree.rotate(true);
	std::cout << tree.dotcode();

	return 0;
}