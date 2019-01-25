
#include "Tree2D.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>



/// Constructor that takes a file containing an x and y value per line
Tree2D::Tree2D(const char * filename) {
	std::ifstream in(filename);
	int x, y;
	while (in.good()) {
		in >> x >> y;
		add(Point(x, y));
	}
	in.close();
}

Point Tree2D::nearestNeighbourSearch(const Point& point, int& amountVisited) {
	Point best;
	nearestNeighbourSearchRecursive(point, best, amountVisited, true);
	return best;
}

void Tree2D::nearestNeighbourSearchRecursive(const Point& searchPoint, Point& best, int& amountVisited, bool xAlignment) {
	if (!*this) return;

	amountVisited++;

	unsigned int bestDistance = best.quadDistance(searchPoint);
	unsigned int currentDistance = (*this)->point.quadDistance(searchPoint);

	if (currentDistance < bestDistance) {
		best = (*this)->point;
	}

	
	// bepaal volgende knoop op basis van alignment en afhankelijk ofdat het zoekpunt links of rechts zal zitten
	Tree2D* next;
	xAlignment
		? next = &((*this)->giveChild(searchPoint.x < (*this)->point.x))
		: next = &((*this)->giveChild(searchPoint.y < (*this)->point.y));

	next->nearestNeighbourSearchRecursive(searchPoint, best, amountVisited, !xAlignment);

	unsigned int a = 0;
	xAlignment
		? a = ((*this)->point.x - searchPoint.x)
		: a = ((*this)->point.y - searchPoint.y);

	a *= a;

	if (a < bestDistance) {
		xAlignment // inverse keuze maken nu, indien zoekpunt in linkerdeelboom zou zitten, bekijken we nu rechterdeelboom
			? next = &((*this)->giveChild(!(searchPoint.x < (*this)->point.x)))
			: next = &((*this)->giveChild(!(searchPoint.y < (*this)->point.y)));
		next->nearestNeighbourSearchRecursive(searchPoint, best, amountVisited, !xAlignment);
	}
}

Tree2D* Tree2D::search(const Point & point) {
	if (!*this) return nullptr; // boom is ledig

	Tree2D* current = this;
	bool xAlignment = true;

	while (*current && (*current)->point != point) {
		xAlignment
			? current = &((*current)->giveChild((*current)->point.x > point.x))
			: current = &((*current)->giveChild((*current)->point.y > point.y));
	}
	return current;
}




void Tree2D::add(const Point & point) {
	if (!*this) { // huidige boom is ledig
		*this = std::make_unique<Node2D>(point);
		return;
	}

	Tree2D* current = search(point);
	// in geval dat de punten gelijk zijn, moet de rechterknoop ingevuld worden,
	// maar deze rechterknoop kan al ingevuld zijn met hetzelfde punt.
	// Dus blijven het rechterkind nemen todat we ergens een nullptr tegenkomen
	while (*current && (*current)->point == point) {
		current = &((*current)->giveChild(false));
	}
	(*current) = std::make_unique<Node2D>(point);
}

int Tree2D::depth() const {
	if (*this) {
		return 1 + std::max((*this)->left.depth(), (*this)->right.depth());
	}
	else {
		return 0;
	}
}

void Tree2D::draw(const char * filename, int maxdepth) const {
	std::ofstream out(filename);
	int nullcounter = 0;
	out << "digraph {\n";
	this->drawrecursive(out, nullcounter, maxdepth);
	out << "}";
}

std::string Tree2D::drawrecursive(std::ostream& os, int& nullcounter, int maxdepth) const {
	int rightMaxDepth = maxdepth; // for the right subtrees, maxdepth itself is used for the left subtrees
	std::ostringstream rootstring;
	if (!*this || maxdepth == 0) {
		rootstring << "null" << ++nullcounter;
		os << rootstring.str() << " [shape=point];\n";
	}
	else {
		rootstring << '"' << (*this)->point << '"';
		os << rootstring.str() << "[label=\"" << (*this)->point << "\"]";
		os << ";\n";
		std::string leftchild = (*this)->left.drawrecursive(os, nullcounter, --maxdepth);
		std::string rightchild = (*this)->right.drawrecursive(os, nullcounter, --rightMaxDepth);
		os << rootstring.str() << " -> " << leftchild << ";\n";
		os << rootstring.str() << " -> " << rightchild << ";\n";
	};
	return rootstring.str();
}

void Tree2D::print(std::ostream& os) const {
	inorder([&os](const Node2D& node) {
		os << node.point;
		os << "\n  L: ";
		if (node.left)
			os << node.left->point;
		else
			os << "-----";
		os << "\n  R: ";
		if (node.right)
			os << node.right->point;
		else
			os << "-----";
		os << "\n";
	});

}

void Tree2D::inorder(std::function<void(const Node2D&)> visit) const {
	if (*this) {
		(*this)->left.inorder(visit);
		visit(**this);
		(*this)->right.inorder(visit);
	}
}

Tree2D & Node2D::giveChild(bool leftchild) {
	return leftchild ? this->left : this->right;
}
