#pragma once


#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

#include <iomanip>

class DNASequence : public std::string {
public:
	DNASequence() = default;
	DNASequence(const std::string& sequence) : std::string{ sequence } {}


	int mutationDistance(const DNASequence& other) const;


private:
	void printDistancesMatrix(const std::vector<std::vector<int>>& LCS, const DNASequence& other) const;
};


int DNASequence::mutationDistance(const DNASequence& other) const {
	const int THIS_MATRIX_SIZE = this->size() + 1;
	const int OTHER_MATRIX_SIZE = other.size() + 1;

	std::vector<std::vector<int>> LCS(THIS_MATRIX_SIZE, std::vector<int>(OTHER_MATRIX_SIZE, 0));

	for (int i = 0; i < THIS_MATRIX_SIZE; i++) {
		for (int j = 0; j < OTHER_MATRIX_SIZE; j++) {

			if (i == 0 || j == 0) {
				LCS[i][j] = 0;
			} else {
				if (this->operator[](i - 1) == other[j - 1]) { // todo, something wrong here with indices, this is due to the fact that the matrix size has one extra row  and column
					LCS[i][j] = LCS[i - 1][j - 1] + 1;
				} else {
					LCS[i][j] = std::max(LCS[i][j - 1], LCS[i - 1][j]);
				}
			}
		}
	}
	printDistancesMatrix(LCS, other);
	return LCS[THIS_MATRIX_SIZE - 1][OTHER_MATRIX_SIZE - 1];
}

void DNASequence::printDistancesMatrix(const std::vector<std::vector<int>>& LCS, const DNASequence& other) const {
	const int THIS_MATRIX_SIZE = LCS.size();
	const int OTHER_MATRIX_SIZE = LCS[0].size();
	std::cout << "    ";
	for (int i = 0; i < OTHER_MATRIX_SIZE; i++) {
		std::cout << other[i] << " ";
	}

	std::cout << "\n";


	std::cout << "  ";
	for (int j = 0; j < OTHER_MATRIX_SIZE; j++) {
		std::cout << LCS[0][j] << " ";
	}
	std::cout << "\n";


	for (int i = 1; i < THIS_MATRIX_SIZE; i++) {
		std::cout << this->operator[](i - 1) << " ";
		for (int j = 0; j < OTHER_MATRIX_SIZE; j++) {
			std::cout << LCS[i][j] << " ";
		}
		std::cout << "\n";
	}
}