#include "zoekboom17.cpp"
#include <iostream>
#include <ctime>
#include <exception>



// Geeft de boom die op de figuur van de roteeroperatie staat
ZoekBoom<int, char> geefIntranetBoom() {
	ZoekBoom<int, char> boom;
	boom.voegtoe(5, 'p');
	boom.voegtoe(3, 'c');
	boom.voegtoe(2, 'a');
	boom.voegtoe(4, 'b');
	boom.voegtoe(6, 'g');
	return boom;
}

// Genereert een willekeurige boom waarbij de sleutel een willekeurig getal is en de data de positie aanduidt wanneer deze knoop toegevoegd werd. Duplicatie sleutels zijn toegestaan
ZoekBoom<int, int> geefRandomBoom(int aantalKnopen = 10){
	srand(time(nullptr));
	ZoekBoom<int, int> boom;
	for(int i = 0; i < aantalKnopen; i++){
		boom.voegtoe(rand() % aantalKnopen, i, true);
	}
	return boom;
}

// Tekent de boom in dot-formaat en vormt dit .dot bestand om naar een jpg.
// Enkel mogelijk als dot programma beschikbaar is

template<class Sleutel, class Data>
void tekenBoomEnToon(ZoekBoom<Sleutel, Data>& boom){
	boom.teken("boom.dot");
	system("dot -Tpng boom.dot -o boom.jpg && boom.jpg");
}

int main(void) {
	try{
		ZoekBoom<int, char> boom = geefIntranetBoom();
		boom.maakEvenwichtig();
		tekenBoomEnToon(boom);
	} catch(std::exception& e){
		std::cout << e.what();
	}
	


	
	

	return 0;
}