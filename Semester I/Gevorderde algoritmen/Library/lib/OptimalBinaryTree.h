#pragma once
#include "binarytree.h"
#include <vector>
#include <climits>
#include <iostream>


/**********************************************************************

   Class: OptimalBinaryTree

   Description: Constructs an optimal binary tree for the given keys and probabilities in cubic time.

***************************************************************************/
template <class Key>
class OptimalBinaryTree : public BinaryTree<Key> {
public:
	OptimalBinaryTree(std::vector<Key> keys, std::vector<double> keysProbabilities, std::vector<double> absentKeysProbabilities);
};

template<class Key>
OptimalBinaryTree<Key>::OptimalBinaryTree(std::vector<Key> keys, std::vector<double> p, std::vector<double> q) {
	int n = p.size() - 1; // the amount of keys

	std::vector<std::vector<double>> z(1 + n + 1, std::vector<double>(1 + n));
	std::vector<std::vector<int>> g(1 + n + 1, std::vector<int>(1 + n));
	std::vector<std::vector<int>> r(1 + n, std::vector<int>(1 + n));

	for (int i = 1; i <= n + 1; i++) {
		z[i][i - 1] = q[i - 1];
		g[i][i - 1] = q[i - 1];
	}

	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n - k + 1; i++) {
			int j = i + k - 1;
			std::cout << j << "\n";
			g[i][j] = g[i][j - 1] + p[j] + q[j];
			z[i][j] = INT_MAX;
			for (int w = i; w <= j; w++) {
				double t = z[i][w - 1] + z[w + 1][j] + g[i][j];
				if (t < z[i][j]) {
					z[i][j] = t;
					r[i][j] = w;
				}
			}
		}
	}

	int x = 5;
	

}
