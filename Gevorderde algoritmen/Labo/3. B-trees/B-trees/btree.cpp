

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
}

template<class T, class D, unsigned int m>
int Btree<T, D, m>::zoek(const T& sleutel, Bknoop<T, D, m>& knoop) const {

	knoop = &wortel;
	int i = 0;
	while (...) {
		while (sleutel >= plaats->wortel.sleutel[i] && i < m) {
			if (sleutel == plaats->wortel.sleutel[i]) {
				return i;
			}
			i++;
		}
		schijf.lees(knoop, wortel.index[i + 1]);
	}





}