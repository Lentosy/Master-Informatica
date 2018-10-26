
#include "Tree2D.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

Point Tree2D::searchClosest(const Point& point, int& amountVisited) {
	Point best = (*this)->point;
	int level = 0;
	searchClosestRecursive(point, best, amountVisited, level);
	return best;
}

void Tree2D::searchClosestRecursive(const Point& searchPoint, Point& best, int& amountVisited, int level) {
	
}

Tree2D* Tree2D::search(const Point & point) {
	if (!*this) return nullptr; // boom is ledig

	Tree2D* current = this;
	bool xAlignment = true;

	while (*current && (*current)->point != point) {
		xAlignment
			? current = &((*current)->giveChild(((*current)->point.x > point.x)))
			: current = &((*current)->giveChild(((*current)->point.y > point.y)));
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
		std::string linkskind = (*this)->left.drawrecursive(os, nullcounter, --maxdepth);
		std::string rechtskind = (*this)->right.drawrecursive(os, nullcounter, --rightMaxDepth);
		os << rootstring.str() << " -> " << linkskind << ";\n";
		os << rootstring.str() << " -> " << rechtskind << ";\n";
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

Tree2D & Node2D::giveChild(bool leftchild)
{
	return leftchild ? this->left : this->right;
}
