#include <iostream>
#include <queue>
#include "knuthmorrispratt.h"

KnuthMorrisPratt::KnuthMorrisPratt(const uchar * naald, uint naaldlengte) {
	this->naald = naald;
	this->naaldlengte = naaldlengte;
	prefixfunctie(prefixwaarden, naald, naaldlengte);
	//kmpPrefixfunctie(kmpPrefixwaarden, prefixwaarden, naald, naaldlengte);
}

// implementatie van paragraaf 11.2.2.3 'Het Knuth-Morris-Prattalgoritme' op pagina 116 van de cursus
void KnuthMorrisPratt::zoek(std::queue<const uchar*>& plaatsen, const uchar * hooiberg, uint hooiberglengte) const {
	zoek(plaatsen, hooiberg, hooiberglengte);
	/*
	int naaldindex = 0;
	for (int hooibergindex = 0; hooibergindex < hooiberglengte; hooibergindex++) {
		if (*(naald + naaldindex) == *(hooiberg + hooibergindex)) {
			naaldindex++;
			if (naaldindex == naaldlengte) {
				plaatsen.push(hooiberg + hooibergindex - naaldlengte);
				naaldindex = 0;
			}
		} else {
			naaldindex = kmpPrefixwaarden[naaldindex];
		}
	}
	*/	
}

// implementatie van paragraaf 11.2.2.2 'Eenvoudige lineaire methode' op pagina 116 van de cursus
// private methode ; dient enkel voor testdoeleinden
void KnuthMorrisPratt::zoekEenvoudig(std::queue<const uchar*>& plaatsen, const uchar * hooiberg, uint hooiberglengte) const{
	int lengte_vorige_prefix = 0;

	//elk karakter overlopen in de hooiberg
	for (size_t i = 1; i <= hooiberglengte; i++) {
		// zolang dat naald[i] != hooiberg[j] en lengte_vorige_prefix > 0
		while (lengte_vorige_prefix > 0 && naald[lengte_vorige_prefix] != hooiberg[i - 1])
			lengte_vorige_prefix = prefixwaarden[lengte_vorige_prefix];
		lengte_vorige_prefix++;
		if (lengte_vorige_prefix == naaldlengte) // prefixlengte == naaldlengte, de naald is gevonden
			plaatsen.push(hooiberg + i - naaldlengte);	
	}
}

void KnuthMorrisPratt::prefixfunctie(std::vector<int>& prefixwaarden, const uchar* naald, uint naaldlengte) const {
	prefixwaarden.resize(naaldlengte + 1);
	prefixwaarden[0] = -1;
	prefixwaarden[1] = 0;

	for (size_t i = 2; i <= naaldlengte; i++) {
		int lengte_vorige_prefix = prefixwaarden[i - 1];
		while (lengte_vorige_prefix > 0 && naald[i - 1] != naald[lengte_vorige_prefix]) {
			lengte_vorige_prefix = prefixwaarden[lengte_vorige_prefix];
		}
		if (naald[i - 1] == naald[lengte_vorige_prefix]) {
			lengte_vorige_prefix++;
		}
		prefixwaarden[i] = lengte_vorige_prefix;
	}
}

void KnuthMorrisPratt::kmpPrefixfunctie(std::vector<int>& kmpPrefixwaarden, std::vector<int>& prefixwaarden,const uchar * naald, uint naaldlengte) const {
	// q' bepalen uit q (kmpPrefixwaarden naald)
	prefixwaarden.resize(prefixwaarden.size());
	kmpPrefixwaarden[0] = -1;
	kmpPrefixwaarden[1] = 0;

	for (int i = 2; i < this->prefixwaarden.size(); i++) {
		if (*(naald + kmpPrefixwaarden[i]) == *(naald + i)) {
			if (kmpPrefixwaarden[kmpPrefixwaarden[i]] == -1) {
				kmpPrefixwaarden[i] = 0;
			} else {
				kmpPrefixwaarden[i] = kmpPrefixwaarden[kmpPrefixwaarden[i]];
			}
		} else {
			kmpPrefixwaarden[i] = kmpPrefixwaarden[i];
		}
	}
}
