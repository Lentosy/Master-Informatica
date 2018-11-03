
#include "SplayTreeBottomUp.h"


#include <cmath>


template<typename Priority, typename Value>
void SplayTreeBottomUp<Priority, Value>::add(const Priority & key, const Value & value) {
	BinarySearchTree<Priority, Value>::add(key, value);

	BinarySearchTree<Priority, Value>* position = nullptr;
	Node<Priority, Value>* parent = nullptr;
	BinarySearchTree<Priority, Value>::search(key, parent, position);
	splay(position);
}

template<typename Priority, typename Value>
void SplayTreeBottomUp<Priority, Value>::splay(BinarySearchTree<Priority, Value>*& position) {
	if (!position) {
		return;
	}
}



template<typename Priority, typename Value>
double SplayTreeBottomUp<Priority, Value>::potential() const {
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

template<typename Priority, typename Value>
void SplayTreeBottomUp<Priority, Value>::calculate_potential(const BinarySearchTree<Priority, Value>& splaytree, double & potential, int & nodes) const {
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