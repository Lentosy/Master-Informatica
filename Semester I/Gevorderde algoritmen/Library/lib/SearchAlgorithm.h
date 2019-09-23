#pragma once
#include <queue>

typedef unsigned int uint;
typedef unsigned char uchar;

class SearchAlgorithm {
public:
	SearchAlgorithm(const uchar* pattern, uint patternLength);
	virtual void search(std::queue<const uchar*>& positions, const uchar* text, unsigned int textLength) const = 0;

protected:
	const uchar* pattern;
	unsigned int patternLength;

};

SearchAlgorithm::SearchAlgorithm(const uchar* pattern, uint patternLength) {
	this->pattern = pattern;
	this->patternLength = patternLength;
}
