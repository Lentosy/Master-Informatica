#include "BinarySearchTree.h"

#include <memory>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>

template<typename Priority, typename Value>
BinarySearchTree<Priority, Value>::BinarySearchTree(const std::vector<Priority> keys, const std::vector<Value> values) {
	if (keys.size() != values.size()) {
		std::string error = __FUNCTION__;
		error += ": size() of keys and values are not equal";
		throw error;
	}

	for (size_t i = 0; i < keys.size(); i++) {
		BinarySearchTree<Priority, Value>* position;
		Node<Priority, Value>* parent;
		search(keys[i], parent, position);
		if (!*position) {
			*position = std::make_unique<Node<Priority, Value>>(keys[i], values[i]);
			(*position)->parent = parent;
		}
	}
}



template<typename Priority, typename Value>
void BinarySearchTree<Priority, Value>::add(const Priority & key, const Value & value) {
	BinarySearchTree<Priority, Value>* position;
	Node<Priority, Value>* parent;
	search(key, parent, position);
	if (!*position) {
		*position = std::make_unique<Node<Priority, Value>>(key, value);
		(*position)->parent = parent;
	} else {
		std::string error = __FUNCTION__;
		error += ": Key already exists";
		throw error;
	}
}

template<typename Priority, typename Value>
Value BinarySearchTree<Priority, Value>::search(const Priority & key) {
	BinarySearchTree<Priority, Value>* position;
	search(key, position);
	if (*position) {
		return (*position)->value;
	} else {
		return Value();
	}
}

template<typename Priority, typename Value>
void BinarySearchTree<Priority, Value>::remove(const Priority & key) {
	BinarySearchTree<Priority, Value>* position;
	Node<Priority, Value>* parent;
	search(key, parent, position);
	if (*position) {
		//the node to remove is a leaf, easy
		if ((*position)->left == nullptr && (*position)->right == nullptr) {
			(*position).reset();
		}
		// todo, de rest...


	}
}

template<typename Priority, typename Value>
void BinarySearchTree<Priority, Value>::print(std::ostream& os) const {
	inorder([&os](const Node<Priority, Value>& node) {

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

template<typename Priority, typename Value>
void BinarySearchTree<Priority, Value>::inorder(std::function<void(const Node<Priority, Value>&)> visit) const {
	if (*this) {
		(*this)->left.inorder(visit);
		visit(**this);
		(*this)->right.inorder(visit);
	}
}

template<typename Priority, typename Value>
void BinarySearchTree<Priority, Value>::getDotCode(const char * filename) const {
	std::ofstream out(filename);
	int nullcounter = 0;
	out << "digraph {";
	out << "node[shape=circle];\n";
	this->getDotCodeRecursive(out, nullcounter);
	out << "}";
}

template<typename Priority, typename Value>
std::string BinarySearchTree<Priority, Value>::getDotCodeRecursive(std::ostream & os, int & nullcounter) const {
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


template<typename Priority, typename Value>
void BinarySearchTree<Priority, Value>::rotate(bool toLeft) {
	BinarySearchTree<Priority, Value> child = std::move((*this)->giveChild(!toLeft));
	(*this)->giveChild(!toLeft) = std::move(child->giveChild(toLeft));
	child->giveChild(toLeft) = std::move(*this);
	*this = std::move(child);

	(*this)->parent = (*this)->giveChild(toLeft)->parent;
	(*this)->giveChild(toLeft)->parent = this->get();
	if ((*this)->giveChild(toLeft)->parent = this->get()) {
		(*this)->giveChild(toLeft)->giveChild(!toLeft)->parent = (*this)->giveChild(toLeft).get();
	}
}

template<typename Priority, typename Value>
bool BinarySearchTree<Priority, Value>::representative() const {
	const Priority& previous = nullptr;
	std::string error = __FUNCTION__;
	if (*this && (*this)->ouder != nullptr) {

		error += " root has a poiner to a parent\n";
		throw error;
	}
	inorder([&previous](const Node<Priority, Value>& node) {
		if (previous && node.key < *previous) {
			error += " wrong order\n";
			throw error;
		}

	});
}

template<typename Priority, typename Value>
void BinarySearchTree<Priority, Value>::search(const Priority & key, Node<Priority, Value>*& parent, BinarySearchTree<Priority, Value>*& position) {
	position = this;
	parent = nullptr;
	while (*position && (*position)->key != key) {
		parent = position->get();
		position = &((*position)->giveChild((*position)->key > key));
	}
}




template<typename Priority, typename Value>
BinarySearchTree<Priority, Value>& Node<Priority, Value>::giveChild(bool takeLeft) {
	if (takeLeft) {
		return left;
	} else {
		return right;
	}
}

