#ifndef KNUTH_MORRIS_PRATT_H
#define KNUTH_MORRIS_PRATT_H
#include <queue>
#include <vector>
typedef unsigned int uint;
typedef unsigned char uchar;
class KnuthMorrisPratt{
public:
    KnuthMorrisPratt(const uchar* naald,uint naaldlengte);
    void zoek(std::queue<const uchar*>& plaats,
                     const uchar* hooiberg, uint hooiberglengte) const;


private:
	void zoekEenvoudig(std::queue<const uchar*>& plaats, const uchar* hooiberg, uint hooiberglengte) const;
	void prefixfunctie(std::vector<int>& prefixwaarden, const uchar* naald, uint naaldlengte) const;

	const uchar* naald;
	uint naaldlengte;
	std::vector<int> prefixwaarden;
	
};
   
#endif
