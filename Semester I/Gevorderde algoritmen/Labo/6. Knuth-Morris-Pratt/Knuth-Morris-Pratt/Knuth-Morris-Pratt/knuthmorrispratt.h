#ifndef KNUTH_MORRIS_PRATT_H
#define KNUTH_MORRIS_PRATT_H
#include <queue>
#include <vector>
typedef unsigned int uint;
typedef unsigned char uchar;
class KnuthMorrisPratt{
public:
    KnuthMorrisPratt(const uchar* naald,uint naaldlengte);
	// zoeken volgens het Knuth-Morris-Pratt algoritme
    void zoek(std::queue<const uchar*>& plaatsen,
                     const uchar* hooiberg, uint hooiberglengte) const;


private:
	// zal een eenvoudige lineaire zoekmethode toepassen. Dient enkel voor testdoeleinden
	void zoekEenvoudig(std::queue<const uchar*>& plaatsen, const uchar* hooiberg, uint hooiberglengte) const;
	// De prefixfunctie van de naald bepalen
	void prefixfunctie(std::vector<int>& prefixwaarden, const uchar* naald, uint naaldlengte) const;
	// Bepaalt de prefixwaarden voor het Knuth-Morris-Pratt algoritme
	void kmpPrefixfunctie(std::vector<int>& kmpPrefixwaarden, std::vector<int>& prefixwaarden,  const uchar* naald, uint naaldlengte) const;

	const uchar* naald;
	uint naaldlengte;
	std::vector<int> prefixwaarden; // de normale prefixfunctie
	std::vector<int> kmpPrefixwaarden; // de q', vanuit de cursus, gebaseerd op de prefixwaarden
	
};
   
#endif
