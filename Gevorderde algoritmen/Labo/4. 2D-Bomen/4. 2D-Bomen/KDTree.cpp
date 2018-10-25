

#include "KDTree.h"
#include <iostream>

void KDTree::add(const Point& p) {
	if (!this) { // current tree is empty
		*this = std::make_unique<KDNode>(p);
		return;
	}
}


void KDTree::print(std::ostream& os) const {
	inorder([&os](const KDNode& node) {
		
	});
	
	
}

void KDTree::inorder(std::function<void(const KDNode&)> visit){
	if (*this) {
		(*this)->left.inorder(visit);
		visit(**this);
		(*this)->right.inorder(visit);
	}
}