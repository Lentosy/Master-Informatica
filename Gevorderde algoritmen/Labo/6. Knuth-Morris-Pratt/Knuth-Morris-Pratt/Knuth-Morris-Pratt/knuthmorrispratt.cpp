#include <iostream>
#include "knuthmorrispratt.h"

KnuthMorrisPratt::KnuthMorrisPratt(const uchar * naald, uint naaldlengte) {
	this->naald = naald;
	this->naaldlengte = naaldlengte;
	prefixFunctie(prefixwaarden);
}

void KnuthMorrisPratt::zoek(std::queue<const uchar*>& plaats, const uchar * hooiberg, uint hooiberglengte) {
	for (int i = 0; i < prefixwaarden.size(); i++) {
		///zolang dat P(q(i)) == P(i)
	}
}

void KnuthMorrisPratt::prefixFunctie(std::vector<int>& q) {
	q.push_back(-1);
	q.push_back(0);
	for (int i = 2; i <= naaldlengte; i++) {
		int vorig = q[i - 1];
		while (vorig > 0 && naald[i - 1] != naald[vorig]) {
			vorig = q[i - 1];
		}
		if (naald[i - 1] == naald[vorig]) {
			vorig++;
		}
		q.push_back(vorig);
	}
}
