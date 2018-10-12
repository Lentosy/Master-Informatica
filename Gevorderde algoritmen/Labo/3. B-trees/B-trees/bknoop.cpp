#include "bknoop.h"
#include "btree.h"

template<class T, class D, unsigned int m>
const Bknoop<T, D, m>& Bknoop<T, D, m>::operator=(const Bknoop<T, D, m>& b) {
	k = b.k;
	isblad = b.isblad;
	for (unsigned int i = 0; i < k; i++) {
		sleutel[i] = b.sleutel[i];
		data[i] = b.data[i];
	}
	if (!isblad) {
		for (unsigned int i = 0; i <= k; i++) {
			index[i] = b.index[i];
		}
	}
	return *this;
};


template<class T, class D, unsigned int m>
int Bknoop<T, D, m>::geefIndexVanSleutel(const T & s) const {
	int i = 0;
	while (i < k && sleutel[i] != s) {
		i++;
	}
	return i;
}
