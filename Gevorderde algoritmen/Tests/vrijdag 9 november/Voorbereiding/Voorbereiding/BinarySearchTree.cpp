#include "BinarySearchTree.h"

#include <memory>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree(const std::vector<Key> keys, const std::vector<Value> values) {
	if (keys.size() != values.size()) {
		std::string error = __FUNCTION__;
		error += ": size() of keys and values are not equal";
		throw error;
	}

	for (size_t i = 0; i < keys.size(); i++) {
		BinarySearchTree<Key, Value>* position;
		Node<Key, Value>* parent;
		search(keys[i], parent, position);
		if (!*position) {
			*position = std::make_unique<Node<Key, Value>>(keys[i], values[i]);
			(*position)->parent = parent;
		}
	}
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::add(const Key & key, const Value & value) {
	BinarySearchTree<Key, Value>* position;
	Node<Key, Value>* parent;
	search(key, parent, position);
	if (!*position) {
		*position = std::make_unique<Node<Key, Value>>(key, value);
		(*position)->parent = parent;
	} else {
		std::string error = __FUNCTION__;
		error += ": Key already exists";
		throw error;
	}
}

template<typename Key, typename Value>
Value BinarySearchTree<Key, Value>::search(const Key & key) {
	BinarySearchTree<Key, Value>* position;
	search(key, position);
	if (*position) {
		return (*position)->value;
	} else {
		return Value();
	}
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key & key) {
	BinarySearchTree<Key, Value>* position;
	Node<Key, Value>* parent;
	search(key, parent, position);
	if (*position) {
		//the node to remove is a leaf, easy
		if ((*position)->left == nullptr && (*position)->right == nullptr) {
			(*position).reset();
		}
		// todo, de rest...


	}
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print(std::ostream& os) const {
	inorder([&os](const Node<Key, Value>& node) {

		os << "(" << node.key << ";" << node.value << ")";
		os << "\n Left Child: ";
		node.left
			? os << "(" << node.left->key << ";" << node.left->value << ")"
			: os << "-----------";
		os << "\n Right child: ";
		node.right
			? os << "(" << node.right->key << ";" << node.right->value << ")"
			: os << "-----------";
		os << "\n";
	});
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::inorder(std::function<void(const Node<Key, Value>&)> visit) const {
	if (*this) {
		(*this)->left.inorder(visit);
		visit(**this);
		(*this)->right.inorder(visit);
	}
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::getDotCode(const char * filename) const {
	std::ofstream out(filename);
	int nullcounter = 0;
	out << "digraph {";
	out << "node[shape=circle];\n";
	this->getDotCodeRecursive(out, nullcounter);
	out << "}";
}

template<typename Key, typename Value>
std::string BinarySearchTree<Key, Value>::getDotCodeRecursive(std::ostream & os, int & nullcounter) const {
	std::ostringstream node;
	if (!*this) {
		node << "null" << ++nullcounter;
		os << node.str() << "[shape=point];\n";
	} else {
		node << (*this)->key;
		os << node.str() << "[label=\"" << (*this)->key << "  [" << (*this)->value << "]\"];\n";
		std::string leftChild = (*this)->left.getDotCodeRecursive(os, nullcounter);
		std::string rightChild = (*this)->right.getDotCodeRecursive(os, nullcounter);
		os << node.str() << " -> " << leftChild << ";\n";
		os << node.str() << " -> " << rightChild << ";\n";
	}

	return node.str();
}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::rotate(bool toLeft) {
	BinarySearchTree<Key, Value> child = std::move((*this)->giveChild(!toLeft));
	(*this)->giveChild(!toLeft) = std::move(child->giveChild(toLeft));
	child->giveChild(toLeft) = std::move(*this);
	*this = std::move(child);

	(*this)->parent = (*this)->giveChild(toLeft)->parent;
	(*this)->giveChild(toLeft)->parent = this->get();
	if ((*this)->giveChild(toLeft)->parent = this->get()) {
		(*this)->giveChild(toLeft)->giveChild(!toLeft)->parent = (*this)->giveChild(toLeft).get();
	}
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::representative() const {
	const Key& previous = nullptr;
	std::string error = __FUNCTION__;
	if (*this && (*this)->ouder != nullptr) {

		error += " root has a poiner to a parent\n";
		throw error;
	}
	inorder([&previous](const Node<Key, Value>& node) {
		if (previous && node.key < *previous) {
			error += " wrong order\n";
			throw error;
		}

	});
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::search(const Key & key, Node<Key, Value>*& parent, BinarySearchTree<Key, Value>*& position) {
	position = this;
	parent = nullptr;
	while (*position && (*position)->key != key) {
		parent = position->get();
		position = &((*position)->giveChild((*position)->key > key));
	}
}




template<typename Key, typename Value>
BinarySearchTree<Key, Value>& Node<Key, Value>::giveChild(bool takeLeft) {
	if (takeLeft) {
		return left;
	} else {
		return right;
	}
}

