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

// Tekent de boom in dot-formaat en vormt dit .dot bestand om naar een jpg.
// Enkel mogelijk als dot programma beschikbaar is

template<class Sleutel, class Data>
void tekenBoomEnToon(Boom<Sleutel, Data>& boom){
	boom.teken("boom.dot");
	system("dot -Tpng boom.dot -o boom.jpg && boom.jpg");
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

	boom3.teken("dot/boom3-1-actual.dot");
	boom3Stap1.teken("dot/boom3-1-expected.dot");
	system("dot -Tpng dot/boom3-1-actual.dot -o dot/boom3-1-actual.jpg");
	system("dot -Tpng dot/boom3-1-expected.dot -o dot/boom3-1-expected.jpg");
	
	Boom<int, int> boom3Stap2;
	boom3Stap2.voegtoe(8, 0);
	boom3Stap2.voegtoe(4, 0);
	boom3Stap2.voegtoe(9, 0);
	boom3Stap2.voegtoe(3, 0);
	boom3Stap2.voegtoe(5, 0);
	boom3Stap2.voegtoe(7, 0);
	
	boom3->geefKind(true).roteer(Richting::RECHTS);
	assert(boom3 == boom3Stap2);

	boom3.teken("dot/boom3-2-actual.dot");
	boom3Stap2.teken("dot/boom3-2-expected.dot");
	system("dot -Tpng dot/boom3-2-actual.dot -o dot/boom3-2-actual.jpg");
	system("dot -Tpng dot/boom3-2-expected.dot -o dot/boom3-2-expected.jpg");

	Boom<int, int> boom3Stap3;
	boom3Stap3.voegtoe(4, 0);
	boom3Stap3.voegtoe(3, 0);
	boom3Stap3.voegtoe(8, 0);
	boom3Stap3.voegtoe(5, 0);
	boom3Stap3.voegtoe(9, 0);
	boom3Stap3.voegtoe(7, 0);

	boom3.roteer(Richting::RECHTS);
	assert(boom3 == boom3Stap3);

	boom3.teken("dot/boom3-3-actual.dot");
	boom3Stap3.teken("dot/boom3-3-expected.dot");
	system("dot -Tpng dot/boom3-3-actual.dot -o dot/boom3-3-actual.jpg");
	system("dot -Tpng dot/boom3-3-expected.dot -o dot/boom3-3-expected.jpg");

}

int main(void) {
	testRotaties();

	/*
	try{
		Boom<int, char> boom = geefIntranetBoom(); 
		Boom<int, char> boomCopy = boom;
		boomCopy.roteer(Richting::RECHTS);
		std::cout << boomCopy.repOK() << "\n";
		tekenBoomEnToon(boomCopy);
	} catch(std::exception& e){
		std::cout << e.what();
	}*/
	return 0;
}		



		// Welke constructoren/assignment operators worden nu opgeroepen?

		//Boom<int, int> boom1 = geefRandomBoom(5); // MOVE CONSTRUCTOR (een return value van een functie is een r-value en wordt altijd gemoved. Het is de move constructor want object boom1 wordt voor de eerste keer aangemaakt)
		//Boom<int, int> boom2 = boom1; 			// COPY CONSTRUCTOR
		//boom1 = boom2 							// COPY ASSIGNMENT  
		//Boom<int, int> boom3 = std::move(boom1); 	// MOVE CONSTRUCTOR (want object boom3 wordt voor de eerste keer aangemaakt)
		//boom1 = std::move(boom3); 				// MOVE ASSIGNMENT  (want object boom1 bestaat al)