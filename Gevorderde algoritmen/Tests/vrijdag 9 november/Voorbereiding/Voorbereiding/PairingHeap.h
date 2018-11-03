#pragma once

#include <memory>
#include <utility>
#include <iostream>

// in theory we could inherit from a binary tree class, but there is not enough time...

/*
* A pairing heap is priorityqueue (smaller number is higher priority) which supports the following operations:
*   In O(log n) time:
*		1)  deleteMin: remove the root and merge its subtrees.
*   In (amortized) O(1) time:
*       1)  findMin : return the top element of the heap
*       2)  merge   : compare two root elements, the smaller remains the root of the result, the larger element and its subtree is appended as a child of this root.
*       3)  insert  : create a new heap for the inserted element and merge into the original heap.
*/

template<typename Priority, typename Value>
class HeapNode;

template<typename Priority, typename Value>
class PairingHeap : public std::unique_ptr<HeapNode<Priority, Value>> {
public:
	using std::unique_ptr<HeapNode<Priority, Value>>::unique_ptr;

	// constructor that builds a heap consisting of one element, neccesary for the 'insert' operation.
	PairingHeap(const Priority& priority, const Value& val);

	//important operations

	void deleteMin();
	Value findMin() const;
	void insert(const Priority& priority, const Value& val);
	void merge(PairingHeap<Priority, Value>& other);

	//helpers
	void print(std::ostream& os);
};



template<class Priority, class Value>
class HeapNode {
	friend class PairingHeap<Priority, Value>;
public:
	HeapNode(const Priority& p, const Value& v) : priority{ p }, value{ v }  {}
	HeapNode(Priority&& p, Value&& v) : priority{ std::move(p) }, value{ std::move(v) } {}
	Priority priority;
	Value value;
	PairingHeap<Priority, Value> leftChild, rightSibling;
};