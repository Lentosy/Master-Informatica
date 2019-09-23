#pragma once


#include "SearchAlgorithm.h"


class Bruteforce : public SearchAlgorithm {
	using SearchAlgorithm::SearchAlgorithm;
public:
	void search(std::queue<const uchar*>& positions, const uchar* text, unsigned int textLength) const;
};

void Bruteforce::search(std::queue<const uchar*>& positions, const uchar* text, unsigned int textLength) const {
	for (int j = 0; j < textLength - this->patternLength; j++) {
		int i = 0;

		while(this->pattern[i] == text[j + i] && i < this->patternLength)
			i++;
	
		if (i == this->patternLength) 
			positions.push(text + j);
		
	}
}