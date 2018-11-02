
#include "SplayTreeBottomUp.h"


#include <cmath>


template<typename Key, typename Value>
void SplayTreeBottomUp<Key, Value>::add(const Key & key, const Value & value) {
	BinarySearchTree<Key, Value>::add(key, value);

	BinarySearchTree<Key, Value>* position = nullptr;
	Node<Key, Value>* parent = nullptr;
	BinarySearchTree<Key, Value>::search(key, parent, position);
	splay(position);
}

template<typename Key, typename Value>
void SplayTreeBottomUp<Key, Value>::splay(BinarySearchTree<Key, Value>*& position) {
	if (!position) {
		return;
	}
}



template<typename Key, typename Value>
double SplayTreeBottomUp<Key, Value>::potential() const {
	// assume s_i, the weight for node i, 
	// is equal to the amount of nodes in the subtree where node i is the root.
	// 
	// The potential can then be calculated as:
	//   P = sum(1 to n) lg s_i

	double potential = 0;
	int nodes = 0;
	calculate_potential(*this, potential, nodes);

	return potential;

}

template<typename Key, typename Value>
void SplayTreeBottomUp<Key, Value>::calculate_potential(const BinarySearchTree<Key, Value>& splaytree, double & potential, int & nodes) const {
	int nodes_left = 0;
	int nodes_right = 0;

	if ((*splaytree).left) {
		calculate_potential((*splaytree).left, potential, nodes_left);
	}

	if ((*splaytree).right) {
		calculate_potential((*splaytree).right, potential, nodes_right);
	}

	nodes = nodes_left + nodes_right + 1;
	potential += std::log2(nodes);
}