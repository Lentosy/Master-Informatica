#pragma once


#include <memory>
#include <vector>
#include <functional>
#include <iostream>
#include <string>
#include <utility>




template<typename Priority, typename Value>
class Node;

/*
*
* Class BinarySearchTree
*
* Binary search tree which does not allow duplicate values
*
*/
template<typename Priority, typename Value>
class BinarySearchTree : public std::unique_ptr<Node<Priority, Value>> {
	using std::unique_ptr<Node<Priority, Value>>::unique_ptr;
public:
	// Builds a binary tree based on the given keys and values in level order
	BinarySearchTree(const std::vector<Priority> keys, const std::vector<Value> values);
	BinarySearchTree(std::unique_ptr<Node<Priority, Value>>&& o) : std::unique_ptr<Node<Priority, Value>>(move(o)) {}

	// adds a new node
	void add(const Priority& key, const Value& value);
	// gets the value of the key
	Value search(const Priority& key);
	//deletes the node with the specified key
	void remove(const Priority& key);
	// gives a textual representation of the tree
	void print(std::ostream& os) const;
	//travels the tree in inorder mode and calls the visit function for the node
	void inorder(std::function<void(const Node<Priority, Value>&)> visit) const;
	//prints the .dot representation of the file to the specified filename
	void getDotCode(const char * filename) const;
protected:
	//rotates the (sub)tree
	void rotate(bool toLeft);
	// wether or not the tree is valid
	bool representative() const;
	void search(const Priority& key, Node<Priority, Value>*& parent, BinarySearchTree<Priority, Value>*& position);
	std::string getDotCodeRecursive(std::ostream& os, int& nullcounter) const;
};


template<typename Priority, typename Value>
class Node {
	friend class BinarySearchTree<Priority, Value>;
public:
	Node(const Priority& k, const Value& v) : key{ k }, value{ v } {};
	Node(Priority&& k, Value&& v) : key{ std::move(k) }, value{ std::move(v) } {};
	BinarySearchTree<Priority, Value>& giveChild(bool takeLeft);
	Node<Priority, Value>* parent;
	BinarySearchTree<Priority, Value> left, right;
	Priority key;
	Value value;
};