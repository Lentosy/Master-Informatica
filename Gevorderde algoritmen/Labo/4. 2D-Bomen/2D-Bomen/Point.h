#ifndef __POINT_h
#define __POINT_h

#include <iostream>
#include <iomanip>
using std::setw;
struct Point {
public:
	int x, y;

	Point() {}
	Point(int _x, int _y) : x(_x), y(_y) {}
	Point(const Point& p) :x(p.x), y(p.y) {}
	void set(int _x, int _y) { x = _x; y = _y; }
	bool operator==(const Point& p) const {
		return p.x == x && p.y == y;
	}
	bool operator!=(const Point& p) const {
		return !(*this == p);
	}

	friend std::ostream& operator<<(std::ostream& os, const Point p2) {
		return os << "(" << setw(3) << p2.x << "," << setw(3) << p2.y << ")";
	}
	//opletten voor overflow!
	unsigned int kwadafstand(const Point& p) const {
		return (p.x - x)*(p.x - x) + (p.y - y)*(p.y - y);
	}
};
#endif

