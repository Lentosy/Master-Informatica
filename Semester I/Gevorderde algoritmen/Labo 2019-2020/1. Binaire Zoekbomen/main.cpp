#include "zoekboom17.cpp"
#include <iostream>
#include <ctime>
#include <exception>



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
void tekenBoomEnToon(Boom<Sleutel, Data>& Boom){
	Boom.teken("Boom.dot");
	system("dot -Tpng Boom.dot -o Boom.jpg && Boom.jpg");
}



void testRotaties(){
	Boom<int, char> boom1 = geefIntranetBoom(); 
	Boom<int, char> boom2 = geefIntranetBoom(); 
	if(boom1 == boom2){
		std::cout << "equal";
	}
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