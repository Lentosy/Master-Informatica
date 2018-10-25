#pragma once

#include "Point.h"
#include <utility>

class KDNode {
	friend class KDtree;
public:
	KDNode() {};
	KDNode(const Point& pt) : point{ pt } {};
	KDNode(int x, int y) : point{ Point(x, y) } {};
	Point point;
	KDTree left, right;

};

