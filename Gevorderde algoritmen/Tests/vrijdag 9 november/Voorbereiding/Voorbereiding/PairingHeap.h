#pragma once

#include <memory>
#include <utility>

// in theory we could inherit from a binary tree class, but there is not enough time...

/*
*
* Class PairingHeap
*
* A pairing heap is priorityqueue (smaller number is higher priority) which supports the following operations:
*   In O(log n) time:
*		1)  deleteMin: remove the root and merge its subtrees.
*   In (amortized) O(1) time:
*       1)  findMin : return the top element of the heap
*       2)  merge   : compare two root elements, the smaller remains the root of the result, the larger element and its subtree is appended as a child of this root.
*       3)  insert  : create a new heap for the inserted element and merge into the original heap. 
*/
template<class Key, class Value>
class PairingHeap : std::unique_ptr<Node<Key, Value>> {
public:
	using std::unique_ptr<Node<Key, Value>>::unique_ptr;

	void deleteMin();
	Value findMin() const;
	void insert(const Key& key, const Value& val);
	void merge(PairingHeap<Key, Value>& other);

};



template<class Key, class Value>
class Node {
	friend class PairingHeap<Key, Value>;
public:
	Node(const Key& k, const Value& v) : key{ k }, value{ v }  {}
	Node(Key&& k, Value&& v) : key{ std::move(k) }, value{ std::move(v) } {}
	Key key;
	Value value;
	PairinHeap<Key, Value> leftChild, rightBrother;
};