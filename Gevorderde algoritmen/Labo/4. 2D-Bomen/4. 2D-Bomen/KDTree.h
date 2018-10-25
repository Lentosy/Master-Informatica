#pragma once

#include "KDNode.h"
#include <memory>
#include <functional>
//template<class P> // voor later
class KDTree : public std::unique_ptr<KDNode> {
	using std::unique_ptr<KDNode>::unique_ptr;
public:	
	KDTree() {};
	Point search(int x, int y) const;
	
	void add(const Point& p);
	void print(std::ostream& os) const;
	void inorder(std::function<void(const KDNode& k)> visit);


};