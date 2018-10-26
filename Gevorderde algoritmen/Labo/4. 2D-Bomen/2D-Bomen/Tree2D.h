#ifndef __TREE2D_h
#define __TREE2D_h

#include "Point.h"
#include <iostream>
#include <memory>
#include <string>
#include <functional>

class Node2D;
class Tree2D : public std::unique_ptr<Node2D> {
	using std::unique_ptr<Node2D>::unique_ptr;
public:
	void add(const Point& point);
	Point searchClosest(const Point& point, int& amountVisited);
	void print(std::ostream& os) const;
	void inorder(std::function<void(const Node2D&)> visit) const;
	void draw(const char * filename, int maxdepth) const;
	int depth() const;
private:
	Tree2D* search(const Point& point);
	std::string drawrecursive(std::ostream& os, int& nullcounter, int maxdepth) const;
	void searchClosestRecursive(const Point& searchPoint, Point& best, int& amountVisited, int level);
};

class Node2D {
	friend class Tree2D;
public:
	Node2D() {};
	Node2D(const Point& pt) : point(pt) {};
	Point point;
	Tree2D& giveChild(bool leftchild);
	Tree2D left, right;
};




#endif