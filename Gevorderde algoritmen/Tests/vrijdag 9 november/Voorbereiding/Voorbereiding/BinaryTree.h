#pragma once

#include <memory>
#include <vector>

template<typename Key, typename Value>
class Node;

template<typename Key, typename Value>
class BinaryTree : public std::unique_ptr<Node<Key, Value>> {
	using std::unique_ptr<Node<Key, Value>>::unique_ptr;
public:
	BinaryTree(const std::vector<Key> keys, const std::vector<Value> values);
	BinaryTree(std::unique_ptr<Node<Key, Value>>&& o) : std::unique_ptr<Node<Key, Value>>(move(o)) {}
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
	//prints the .dot representation of the tree to the specified filename
	void getDotCode(const char * filename) const;
protected:
	std::string getDotCodeRecursive(std::ostream& os, int& nullcounter) const;
};


template<typename Key, typename Value>
class Node {
	friend class BinaryTree<Key, Value>;
public:
	Node(const Key& k, const Value& v) : key{ k }, value{ v } {};
	Node(Key&& k, Value&& v) : key{ move(k) }, value{ move(v) } {};
	BinaryTree<Key, Value>& giveChild(bool takeLeft);
	Node<Key, Value>* parent;
	BinaryTree<Key, Value> left, right;
	Key key;
	Value value;
};