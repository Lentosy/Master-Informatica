
#include "BinarySearchTree.cpp"
#include "SplayTreeBottomUp.cpp"
#include "PairingHeap.cpp"
#include "DNASequence.h"
#include "Bottling.h"
#include <iostream>
#include <fstream>
#include <cassert>


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

void testPairingHeap() {
	PairingHeap<int, int> heap(3, 6);
	heap.insert(4, 8);
	heap.print(std::cout);
}

void testMutationDistance() {
	std::ifstream human("human.dna");
	std::ifstream chimp("chimp.dna");
	assert(human); assert(chimp);

	std::vector<DNASequence> humanLines;
	std::vector<DNASequence> chimpLines;

	DNASequence humanLine;
	DNASequence chimpLine;
	while (human >> humanLine) {
		chimp >> chimpLine;
		humanLines.push_back(humanLine);
		chimpLines.push_back(chimpLine);
	}

	human.close(); chimp.close();

	for (int i = 0; i < humanLines.size(); i++) {
		int min_index = 0;
		int min_distance = std::numeric_limits<int>::max();

		for (int j = 0; j < chimpLines.size(); j++) {
			int distance = humanLines[i].mutationDistance(chimpLines[j]);
			if (distance < min_distance) {
				min_distance = distance;
				min_index = j;
			}
		}

		std::cout << "Mens " << i << " komt overeen met chimpansee " << min_index << " met afstand " << min_distance << "\n";
	}
}

void testBottling() {
	const std::vector<Bottle> bottles = { Bottle(50), Bottle(100), Bottle(200) };

	Bottling bottling(bottles);
	std::cout << bottling;
	std::cout << bottling.getOptimalBottles(450);

	//std::cout << "Following bottles are needed to reach 450 cl\n";
	//for (int i = 0; i < answer.size(); i++) {
	//	std::cout << answer[i].second << " of " << answer[i].first << " cl\n";
	//}
}

int main(void) {

	testBottling();
	return 0;
}