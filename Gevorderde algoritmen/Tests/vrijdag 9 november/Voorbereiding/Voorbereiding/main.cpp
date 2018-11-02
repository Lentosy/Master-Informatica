
#include "BinarySearchTree.cpp"
#include "SplayTreeBottomUp.cpp"

#include <vector>
#include <string>
#include <iostream>

void testBinarySearchTree() {
	const std::vector<int> keys = { 8, 3, 10, 1 };
	const std::vector<int> values = { 16, 6, 20, 2 };

	// simple test tree, map a key to its double value
	try {
		BinarySearchTree<int, int> tree(keys, values);
		tree.getDotCode("BinarySearchTree.dot");
	} catch (const std::string str) {
		std::cout << str;
	}
}

void testSplayTreeBottomUp() {
	try {
		std::vector<int> numbers = { 0 };
		std::vector<int> doublenumbers = { 0 };
		SplayTreeBottomUp<int, int> tree(numbers, doublenumbers);
		for (int i = 1; i < 10; i++) {
			tree.add(i, i * 2);
		}
		tree.getDotCode("GoodSplayTree.dot");
		std::cout << "The potential of the tree is : " << tree.potential();

	} catch (const std::string str) {
		std::cout << str;
	}



}

int main(void) {
	testBinarySearchTree();


	return 0;
}