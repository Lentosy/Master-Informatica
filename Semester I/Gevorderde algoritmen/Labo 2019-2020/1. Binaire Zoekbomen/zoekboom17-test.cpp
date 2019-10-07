#include "zoekboom17.cpp"
#include <iostream>
#include <ctime>
#include <exception>
#include <cassert>
#include <sys/stat.h>


// Geeft de boom die op de figuur van de roteeroperatie staat
Boom<int, char> geefIntranetBoom() {
	Boom<int, char> boom;
	boom.voegtoe(5, 'p');
	boom.voegtoe(3, 'c');
	boom.voegtoe(2, 'a');
	boom.voegtoe(4, 'b');
	boom.voegtoe(6, 'g');
	return boom;
}

// Genereert een willekeurige boom waarbij de sleutel een willekeurig getal is en de data de positie aanduidt wanneer deze knoop toegevoegd werd. Duplicatie sleutels zijn toegestaan
Boom<int, int> geefRandomBoom(int aantalKnopen = 10){
	srand(time(nullptr));
	Boom<int, int> boom;
	for(int i = 0; i < aantalKnopen; i++){
		boom.voegtoe(rand() % aantalKnopen, i, true);
	}
	return boom;
}

void testRotaties(){
	/* VOORBEELD VAN INTRANET */ 
	Boom<int, char> boom1 = geefIntranetBoom(); 
	Boom<int, char> boom2;
	boom2.voegtoe(3, 'c');
	boom2.voegtoe(2, 'a');
	boom2.voegtoe(5, 'p');
	boom2.voegtoe(4, 'b');
	boom2.voegtoe(6, 'g');
	boom1.roteer(Richting::RECHTS);
	assert(boom1 == boom2);
	boom1.roteer(Richting::LINKS);
	assert(boom1 == geefIntranetBoom());

	/* EIGEN VOORBEELD */
	Boom<int, int> boom3;
	boom3.voegtoe(8, 0);
	boom3.voegtoe(5, 0);
	boom3.voegtoe(9, 0);
	boom3.voegtoe(3, 0);
	boom3.voegtoe(7, 0);
	boom3.voegtoe(4, 0); // We gaan deze laatste knoop tot de wortel roteren, zoals een splayboom en elk tussenresultaat wordt gecontroleerd of deze de juiste boom oplevert

	Boom<int, int> boom3Stap1;
	boom3Stap1.voegtoe(8, 0);
	boom3Stap1.voegtoe(5, 0);
	boom3Stap1.voegtoe(9, 0);
	boom3Stap1.voegtoe(4, 0);
	boom3Stap1.voegtoe(7, 0);
	boom3Stap1.voegtoe(3, 0);

	boom3->geefKind(true)->geefKind(true).roteer(Richting::LINKS);
	assert(boom3 == boom3Stap1);
	assert(boom3.repOK());
	
	Boom<int, int> boom3Stap2;
	boom3Stap2.voegtoe(8, 0);
	boom3Stap2.voegtoe(4, 0);
	boom3Stap2.voegtoe(9, 0);
	boom3Stap2.voegtoe(3, 0);
	boom3Stap2.voegtoe(5, 0);
	boom3Stap2.voegtoe(7, 0);
	
	boom3->geefKind(true).roteer(Richting::RECHTS);
	assert(boom3 == boom3Stap2);
	assert(boom3.repOK());

	Boom<int, int> boom3Stap3;
	boom3Stap3.voegtoe(4, 0);
	boom3Stap3.voegtoe(3, 0);
	boom3Stap3.voegtoe(8, 0);
	boom3Stap3.voegtoe(5, 0);
	boom3Stap3.voegtoe(9, 0);
	boom3Stap3.voegtoe(7, 0);

	boom3.roteer(Richting::RECHTS);
	assert(boom3 == boom3Stap3);
	assert(boom3.repOK());

	std::cout << "rotaties OK\n";
}

void testMaakOnevenwichtig(){
	
    Boom<int, char> boom;
    boom.maakOnevenwichtig(Richting::LINKS); // -> BUG
    assert(boom == nullptr);

    boom = geefIntranetBoom(); 
    Boom<int, char> boomLinksOnevenwichtig;
    boomLinksOnevenwichtig.voegtoe(6, 'g');
    boomLinksOnevenwichtig.voegtoe(5, 'p');
    boomLinksOnevenwichtig.voegtoe(4, 'b');
	boomLinksOnevenwichtig.voegtoe(3, 'c');
	boomLinksOnevenwichtig.voegtoe(2, 'a');
	
    boom.maakOnevenwichtig(Richting::LINKS);

    assert(boom == boomLinksOnevenwichtig);
    assert(boom.repOK());

    boom = geefIntranetBoom(); 
    Boom<int, char> boomRechtsOnevenwichtig;
    boomRechtsOnevenwichtig.voegtoe(2, 'a');
    boomRechtsOnevenwichtig.voegtoe(3, 'c');
    boomRechtsOnevenwichtig.voegtoe(4, 'b');
    boomRechtsOnevenwichtig.voegtoe(5, 'p');
    boomRechtsOnevenwichtig.voegtoe(6, 'g');
	
    boom.maakOnevenwichtig(Richting::RECHTS);

    assert(boom == boomRechtsOnevenwichtig);
    assert(boom.repOK());

	std::cout << "maak onevenwichtig OK\n";

}

int main(void) {
	testRotaties();
    testMaakOnevenwichtig();

	return 0;
}		