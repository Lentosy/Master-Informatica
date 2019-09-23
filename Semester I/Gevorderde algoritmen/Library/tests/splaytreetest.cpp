#include "splaytree.h"
#include <iostream>
#include <memory>


int main(void) {

	BinaryTree<int> tree = std::make_unique<Node<int>>(3);
	tree.add(2);
	tree.add(4);


	std::cout << tree.dotcode();

	return 0;
}