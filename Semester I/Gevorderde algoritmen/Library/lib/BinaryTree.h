#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <functional>
#include <queue>
#include <sstream>

// Class pre-declaration
template <class Key>
class Node;



/**********************************************************************

   Class: BinaryTree

   Description: This class describes a binary tree where duplicate keys are not allowed. 
                Inheriting this tree is only useful when the same Node class is used to represent a node in the tree.
				Red black trees for example cannot be inherited from this class.

***************************************************************************/
template <class Key>
class BinaryTree : public std::unique_ptr<Node<Key>> {

	using std::unique_ptr<Node<Key>>::unique_ptr;

public:

	/* Constructors */
	BinaryTree(const BinaryTree<Key>&) = delete;
	BinaryTree(BinaryTree<Key>&&);
	BinaryTree& operator=(const BinaryTree<Key>&) = delete;
	BinaryTree& operator=(BinaryTree<Key>&&);


	/* Tree operations */
	BinaryTree<Key>* search(const Key&);
	void add(const Key&);
	void rotate(bool toLeft);

	/* Output */
	virtual std::string dotcode() const;
	void write(std::ostream& os) const;

	/* Tree properties*/
	int depth() const;

	/* Tree traversal*/
	void inorder(std::function<void(const Node<Key>&)> visit) const;
	void preorder(std::function<void(const Node<Key>&)> visit) const;
	void postorder(std::function<void(const Node<Key>&)> visit) const;

};


template <class Key>
class Node {
	friend class BinaryTree<Key>;
public:
	Node(const Key& k) : key(k) {};
	const Key key;
	BinaryTree<Key> left, right;
	BinaryTree<Key>& giveChild(bool left);
};




template <class Key>
BinaryTree<Key>::BinaryTree(BinaryTree<Key>&& other) : std::unique_ptr<Node<Key>>(std::move(other)) {}

template <class Key>
BinaryTree<Key>& BinaryTree<Key>::operator=(BinaryTree<Key>&& other) {
	std::unique_ptr<Node<Key>>::operator=(std::move(other));
	return *this;
}

template <class Key>
int BinaryTree<Key>::depth() const {
	if (*this) {
		return 1 + std::max((*this)->left.depth(), (*this)->right.depth());
	}
	return 0;
}

template <class Key>
BinaryTree<Key>& Node<Key>::giveChild(bool left) {
	if (left) {
		return this->left;
	}
	return this->right;
}

template <class Key>
void BinaryTree<Key>::rotate(bool toLeft) {
	BinaryTree<Key> child = std::move((*this)->giveChild(!toLeft));
	(*this)->giveChild(!toLeft) = std::move(child->giveChild(toLeft));
	child->giveChild(toLeft) = std::move(*this);
	*this = std::move(child);
}


/*
* Returns a dotcode which can be used for graphviz.
*/
template <class Key>
std::string BinaryTree<Key>::dotcode() const {

	std::stringstream out;

	out << "digraph BST {\n";

	if (!*this) {
		out << "null[shape=point];\n";
	}
	else {
		// breadth-first traversal
		std::queue<const BinaryTree<Key>*> queue;
		queue.push(this);
		int nullptrCount = 0; // counter needed to differentiate the null pointers 

		while (!queue.empty()) {
			// handle current node
			const BinaryTree<Key>* currentNode = queue.front();
			queue.pop();

			if (*currentNode) {
				const Key& currentNodeKey = (*currentNode)->key;
				out << currentNodeKey << "\n";
				// iterate over both childs
				for (const BinaryTree<Key>* child : { &((*currentNode)->left), &((*currentNode)->right) }) {
					if (*child) {
						const Key& childKey = (*child)->key;
						out << currentNodeKey << " -> " << childKey << "\n";
						queue.push(child);
					}
					else {
						out << "null" << nullptrCount << "[shape=point];\n";
						out << currentNodeKey << " -> " << "null" << nullptrCount << ";\n";
						nullptrCount++;
					}
				}
			}
		}
	}
	out << "}\n";
	return out.str();
}

/*
* Write tree to given outputstream in inorder.
*/
template <class Key>
void BinaryTree<Key>::write(std::ostream& os) const {
	inorder([&os](const Node<Key>& node) {

		os << node.key << " : " << node.data;

		os << "\n\tLeft child: ";
		node.left ? os << node.left->key : os << "-----"; // write left child if it exists, otherwise just dashed lines

		os << "\n\tRight child: ";
		node.right ? os << node.right->key : os << "-----"; // write right child if it exists, otherwise just dashed lines

		os << "\n";
	});
}



/*
* Searches in the tree for the key and return the subtree for which this key is the root node.
*/
template <class Key>
BinaryTree<Key>* BinaryTree<Key>::search(const Key& key) {
	BinaryTree<Key>* location = this;
	while (*location && (*location)->key != key) {
		if (key > (*location)->key) {
			location = &((*location)->right);
		}
		else {
			location = &((*location)->left);
		}
	}
	return location;
}


/*
* Adds the given key and corresponding data to the tree, given that a node with that key does not already exists.
*/
template <class Key>
void BinaryTree<Key>::add(const Key& key) {
	BinaryTree<Key>* location = this->search(key);
	if (!*location)
		(*location) = std::make_unique<Node<Key>>(key);
	else
		throw "Key already exists";
}





/*
* Different traversal methods
*/

template <class Key>
void BinaryTree<Key>::inorder(std::function<void(const Node<Key>&)> visit) const {
	if (*this) {
		(*this)->left.inorder(visit);
		visit(**this);
		(*this)->right.inorder(visit);
	}
}

template <class Key>
void BinaryTree<Key>::preorder(std::function<void(const Node<Key>&)> visit) const {
	if (*this) {
		visit(**this);
		(*this)->left.inorder(visit);
		(*this)->right.inorder(visit);
	}
}

template <class Key>
void BinaryTree<Key>::postorder(std::function<void(const Node<Key>&)> visit) const {
	if (*this) {
		(*this)->left.inorder(visit);
		(*this)->right.inorder(visit);
		visit(**this);

	}
}