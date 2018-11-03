#pragma once

#include "BinarySearchTree.h"

#include <vector>
#include <memory>

/*
*
* Class SplayTreeBottomUp
*
* A splay tree attempts to make a series of operations O(lg n). This is achieved
* by adding an extra 'splay' operation when adding, searching or deleting a node.
* The splay operation will rotate a node to the root of the tree. This splay tree is implemented
* as a bottom up splay tree, meaning we can use most of the functionality of a normal binary search tree.
* A node first gets added, searched or deleted. Afterwards the splay operation will do its work.
*
* Assume 'c' the node to add, then there are three possible rotations:
*
* 1) Zig: This rotation gets executed when the parent 'p' of c is the root node.
*         This is the last rotation of the splay operation, making c the root node.
* 2) Zig-Zag: This case occurs when p is not the root node, and c is on the INSIDE of the tree.
*             In this case, we rotate p and c to the so that c becomes the parent of p, and then we rotate c and the original parent 'g' of p, so that c becomes parent of g and p
* 3) Zig-Zig: This case occurs when p is not the root node, and c is on the OUTSIDE of the tree.
*              In this case we rotate g and p, so that p becomes parent of c and g. Then we rotate p and c, so that c becomes parent of p, and p still is parent of g.
*/
template<typename Priority, typename Value>
class SplayTreeBottomUp : public BinarySearchTree<Priority, Value> {
public:
	SplayTreeBottomUp(const std::vector<Priority> keys, const std::vector<Value> values) : BinarySearchTree<Priority, Value>(keys, values) {};

	// adds a key like a normal binary search tree, but then executes the splay-operation on the newly added node
	void add(const Priority& key, const Value& value);
	// searches a key like a normal binary search tree, but then executes the splay-operation on the found node. If no node is found, nothing happens.
	void search(const Priority& key, Node<Priority, Value>*& parent, BinarySearchTree<Priority, Value>*& position);
	// calculates the potential of the splay tree, a lower potential means a better balanced tree.
	double potential() const;

private:
	//executes the splay operation, untill position is the root node of the tree
	void splay(BinarySearchTree<Priority, Value>*& position);
	void calculate_potential(const BinarySearchTree<Priority, Value>& splaytree, double& potential, int& nodes) const;
};