#pragma once
#include "BinaryTree.h"
#include <string>




class DigitalSearchTree : public BinaryTree<std::string> {
	using BinaryTree::BinaryTree;
public:

	BinaryTree<std::string>* search(const std::string&);
};




BinaryTree<std::string>* DigitalSearchTree::search(const std::string& key) {

	BinaryTree<std::string>* location = this;
	int indexToCompare = 0;

	while (*location && key[indexToCompare] != (*location)->key[indexToCompare]) {

		if (key[indexToCompare] < (*location)->key[i]) 
			location = &((*location)->left);
		
		else 
			location = &((*location)->right);
		
		indexToCompare++;
	}

	return location;

}