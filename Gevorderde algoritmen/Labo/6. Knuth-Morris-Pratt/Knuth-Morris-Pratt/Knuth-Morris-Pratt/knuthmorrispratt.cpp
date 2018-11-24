#include <iostream>
#include <queue>
#include "knuthmorrispratt.h"

KnuthMorrisPratt::KnuthMorrisPratt(const uchar * naald, uint naaldlengte) {
	this->naald = naald;
	this->naaldlengte = naaldlengte;
	prefixfunctie(prefixwaarden, naald, naaldlengte);
}

// implementatie van paragraaf 11.2.2.3 'Het Knuth-Morris-Prattalgoritme' op pagina 116 van de cursus
void KnuthMorrisPratt::zoek(std::queue<const uchar*>& plaats, const uchar * hooiberg, uint hooiberglengte) const {
	
}


// dient enkel voor testdoeleinden
void KnuthMorrisPratt::zoekEenvoudig(std::queue<const uchar*>& plaats, const uchar * hooiberg, uint hooiberglengte) const{
	// implementatie van paragraaf 11.2.2.2 'Eenvoudige lineaire methode' op pagina 116 van de cursus
	//PPPPPPPPP*TTTTTTTTT
	int lengte_vorige_prefix = 0;
	for (size_t i = 1; i <= hooiberglengte; i++) {
		while (lengte_vorige_prefix > 0 && naald[lengte_vorige_prefix] != hooiberg[i - 1])
			lengte_vorige_prefix = prefixwaarden[lengte_vorige_prefix];
		lengte_vorige_prefix++;
		if (lengte_vorige_prefix == naaldlengte) // prefixlengte == naaldlengte, de naald is gevonden
			plaats.push(hooiberg + i - naaldlengte);	
	}
}

void KnuthMorrisPratt::prefixfunctie(std::vector<int>& prefix, const uchar* naald, uint naaldlengte) const {
	prefix.resize(naaldlengte + 1);
	prefix[0] = -1;
	prefix[1] = 0;

	for (size_t i = 2; i <= naaldlengte; i++) {
		int vorige = prefix[i - 1];
		while (vorige > 0 && naald[i - 1] != naald[vorige]) {
			vorige = prefix[vorige];
		}
		if (naald[i - 1] == naald[vorige]) {
			vorige++;
		}
		prefix[i] = vorige;
	}
}
