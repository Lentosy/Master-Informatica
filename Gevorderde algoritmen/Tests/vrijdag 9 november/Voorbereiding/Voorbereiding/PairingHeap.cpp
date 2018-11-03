#include "PairingHeap.h"

#include <algorithm>
#include <utility>
#include <memory>
#include <iostream>


template<typename Priority, typename Value>
PairingHeap<Priority, Value>::PairingHeap(const Priority & priority, const Value & val) {
	*this = std::make_unique<HeapNode<Priority, Value>>(priority, val);
}

template<typename Priority, typename Value>
void PairingHeap<Priority, Value>::insert(const Priority & priority, const Value & val) {
	PairingHeap<Priority, Value> newHeap = std::make_unique<HeapNode<Priority, Value>>(priority, val);
	this->merge(newHeap);

}

template<typename Priority, typename Value>
void PairingHeap<Priority, Value>::merge(PairingHeap<Priority, Value>& other) {

	if (!other) {
		return;
	}

	if (!*this) {
		std::swap((*this), other);
		return;
	}

	if ((*this)->priority < other.get()->priority) {
		
	}

}

template<typename Priority, typename Value>
void PairingHeap<Priority, Value>::print(std::ostream & os) {
	os << "(" << (*this)->priority << ";" << (*this)->value << ")\n";
}
