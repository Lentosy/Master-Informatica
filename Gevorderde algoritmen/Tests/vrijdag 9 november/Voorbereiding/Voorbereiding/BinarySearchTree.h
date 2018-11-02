#pragma once


#include <memory>
#include <vector>
#include <functional>
#include <iostream>
#include <string>
#include <utility>




template<typename Key, typename Value>
class Node;

/*
*
* Class BinarySearchTree
*
* Binary search tree which does not allow duplicate values
*
*/
template<typename Key, typename Value>
class BinarySearchTree : public std::unique_ptr<Node<Key, Value>> {
	using std::unique_ptr<Node<Key, Value>>::unique_ptr;
public:
	// Builds a binary tree based on the given keys and values in level order
	BinarySearchTree(const std::vector<Key> keys, const std::vector<Value> values);
	BinarySearchTree(std::unique_ptr<Node<Key, Value>>&& o) : std::unique_ptr<Node<Key, Value>>(move(o)) {}

	// adds a new node
	void add(const Key& key, const Value& value);
	// gets the value of the key
	Value search(const Key& key);
	//deletes the node with the specified key
	void remove(const Key& key);
	// gives a textual representation of the tree
	void print(std::ostream& os) const;
	//travels the tree in inorder mode and calls the visit function for the node
	void inorder(std::function<void(const Node<Key, Value>&)> visit) const;
	//prints the .dot representation of the file to the specified filename
	void getDotCode(const char * filename) const;
protected:
	//rotates the (sub)tree
	void rotate(bool toLeft);
	// wether or not the tree is valid
	bool representative() const;
	void search(const Key& key, Node<Key, Value>*& parent, BinarySearchTree<Key, Value>*& position);
	std::string getDotCodeRecursive(std::ostream& os, int& nullcounter) const;
};


template<typename Key, typename Value>
class Node {
	friend class BinarySearchTree<Key, Value>;
public:
	Node(const Key& k, const Value& v) : key{ k }, value{ v } {};
	Node(Key&& k, Value&& v) : key{ std::move(k) }, value{ std::move(v) } {};
	BinarySearchTree<Key, Value>& giveChild(bool takeLeft);
	Node<Key, Value>* parent;
	BinarySearchTree<Key, Value> left, right;
	Key key;
	Value value;
};