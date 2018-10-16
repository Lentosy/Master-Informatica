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
bool Bknoop<T, D, m>::bevatSleutel(const T & s) const {
	size_t i = 0;
	while (i < k && s != sleutel[i]) {
		i++;
	};
	return i == k ? false : true;
}

template<class T, class D, unsigned int m>
int Bknoop<T, D, m>::geefIndexVoorSleutel(const T & s) const {
	size_t i = 0;
	while (i < k && s != sleutel[i]) {
		i++;
	}
	return i;
}

template<class T, class D, unsigned int m>
D Bknoop<T, D, m>::geefDataVoorSleutel(const T & s) const {
	return data[geefIndexVoorSleutel(s)];
}

template<class T, class D, unsigned int m>
blokindex Bknoop<T, D, m>::geefBlokindexVoorSleutel(const T & s) const {
	if (s < sleutel[0]) {
		return index[0];
	}
	size_t i = 0;
	while (i < k && s > sleutel[i]) {
		i++;
	};
	return index[i];
}

template<class T, class D, unsigned int m>
void Bknoop<T, D, m>::setDataVoorSleutel(const T & s, const D & d) {
	int index = geefIndexVoorSleutel(s);
	data[index] = d;
}

template<class T, class D, unsigned int m>
void Bknoop<T, D, m>::voegToe(const T & s, const D & d) {
	sleutel[0] = s;
	data[0] = d;
}
