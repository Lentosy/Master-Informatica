#pragma once
#include "SearchAlgorithm.h"


class PrefixFunction : SearchAlgorithm {
public:
	PrefixFunction(const uchar* pattern, uint patternLength);
	void search(std::queue<const uchar*>& positions, const uchar* text, uint textLength) const;

private:
	std::vector<int> prefixTable;
};


PrefixFunction::PrefixFunction(const uchar* pattern, uint patternLength) : SearchAlgorithm(pattern, patternLength) {
	prefixTable.resize(patternLength + 1);

	prefixTable[0] = -1; // prefixTable[0], or the prefix count for the first letter is not defined
	prefixTable[1] =  0;  

	for (int i = 2; i <= patternLength; i++) {
		int lengthPreviousPrefix = prefixTable[i - 1];

		while(this->pattern[lengthPreviousPrefix] != this->pattern[i - 1] && lengthPreviousPrefix > 0) 
			lengthPreviousPrefix = prefixTable[lengthPreviousPrefix];
		
		 
		if (this->pattern[i - 1] == this->pattern[lengthPreviousPrefix])
			lengthPreviousPrefix++;
		
		prefixTable[i] = lengthPreviousPrefix;
	}
}

void PrefixFunction::search(std::queue<const uchar*>& positions, const uchar* text, uint textLength) const {
	int lengthPreviousPrefix = 0;

	for (int i = 1; i < textLength; i++) {

		while (this->pattern[lengthPreviousPrefix] != text[i - 1] && lengthPreviousPrefix > 0) 
			lengthPreviousPrefix = this->prefixTable[lengthPreviousPrefix];
		
		lengthPreviousPrefix++;

		if (lengthPreviousPrefix == this->patternLength) 
			positions.push(text + i - this->patternLength);
		
	}
	
}
