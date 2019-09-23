#include "SearchAlgorithm.h"
#include <queue>
#include <cmath>
#include <iostream>

class KarpRabin : public SearchAlgorithm {
public:
	KarpRabin(const uchar* pattern, uint patternLength);
	void search(std::queue<const uchar*>& positions, const uchar* text, uint textLength) const;

private:
	int getFingerPrint(const uchar* string) const;

	int radix, modulusR;
	int patternFingerprint;
};

void KarpRabin::search(std::queue<const uchar*>& positions, const uchar* text, uint textLength) const {
	for (int j = 0; j <= textLength - this->patternLength; j++) {
		int fingerprint = this->getFingerPrint(text + j);

		if (fingerprint == this->patternFingerprint) { // pattern POSSIBLY starts at position T_i

			int i = 0;
			while(this->pattern[i] == text[j + i])
				i++;
			
			if (i == this->patternLength) 
				positions.push(text + j);	
		}
	}
}

int KarpRabin::getFingerPrint(const uchar* string) const {
	int fingerprint = 0;
	for (int i = 0; i < this->patternLength; i++) {
		// term = P[i]d*^(p - i - 1
		int term = string[i] * pow(this->radix, this->patternLength - i - 1);
		fingerprint += (term % this->modulusR);
	}
	return fingerprint;
}

KarpRabin::KarpRabin(const uchar* pattern, uint patternLength) : SearchAlgorithm(pattern, patternLength) {

	this->radix = 26; // only alfabetical characters for now
	this->modulusR = 113; // random r

	this->patternFingerprint = this->getFingerPrint(pattern);
}
