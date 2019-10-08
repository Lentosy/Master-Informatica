#include "splayboom.cpp"
#include <iostream>
#include <string>
#include <fstream>

void testSplay1Tot100EnZoek1BottomUp(){
    std::cout << "*** " << __FUNCTION__ << " ***\n";
    SplayboomBottomUp<int, int> boom;
    for(int i = 1; i < 100; i++){
        boom.voegtoe(i, i);
    }
    

    /* Controleer of de boom de juiste structuur heeft na het toevoegen */
    Boom<int, int> testVoegtoe;
    for(int i = 99; i > 0; i--){
        testVoegtoe.voegtoe(i, i);
    }
    assert(boom == testVoegtoe);

    /* Controleer of de boom de juiste structuur heeft na het zoeken naar de sleutel 1 */
    Boom<int, int> testZoek1;
    testZoek1.voegtoe(1, 1);
    for(int i = 98; i > 1; i -= 2){
        testZoek1.voegtoe(i, i);
        testZoek1.voegtoe(i + 1, i + 1);
    }
    Knoop<int, int>* k = boom.zoek(1);
    assert(k->sleutel == 1);
    assert(boom == testZoek1);

    std::cout << "\tTEST OK\n";
}

void testSplay50BottomUp(){

    std::cout << "*** " << __FUNCTION__ << " ***\n";

    int c = 50;
    SplayboomBottomUp<int, int> boom;
    boom.voegtoe(c, c);
    for(int i = 1; i < c; i++){
        boom.voegtoe(c + i, c + i);
        boom.voegtoe(c - i, c - i);
    }

    /* Controleer of de boom de juiste structuur heeft na het toevoegen */
    Boom<int, int> testBoom;
    testBoom.voegtoe(1, 1);
    testBoom.voegtoe(2, 2);
    testBoom.voegtoe(99, 98);
    testBoom.voegtoe(98, 98);
    for(int i = 3; i < c; i++){
        testBoom.voegtoe(i, i);
        testBoom.voegtoe(c*2 - i, c*2 - i);
    }
    testBoom.voegtoe(c, c);
    assert(boom == testBoom);

    /* Controleer of de boom de juiste structuur heeft na het zoeken naar de sleutel 1 */
    Boom<int, int> testZoek50;
    testZoek50.voegtoe(c, c);
    testZoek50.voegtoe(2, 2);
    testZoek50.voegtoe(1, 1);
    for(int i = 3; i < c; i++){
        testZoek50.voegtoe(i, i);
    }
    testZoek50.voegtoe(98,98);
    testZoek50.voegtoe(99,99);
    for(int i = 3; i < c; i++){
        testZoek50.voegtoe(c*2 - i, c*2 -i);
    }
    Knoop<int, int>* k = boom.zoek(50);
    assert(k->sleutel == 50);
    assert(boom == testZoek50);
        std::cout << "\tTEST OK\n";
}

void testShakespeare() {
     std::cout << "*** " << __FUNCTION__ << " ***\n";
    SplayboomBottomUp<string, int> frequentieSplayboom;
    Boom<string, int> frequentieBinaireboom;
    std::ifstream bestand("shakespeare.txt");
    std::string woord;
    int woordAantal = 0;
    int cutoff = 1000;
    while(bestand >> woord && woordAantal < cutoff){
        for(int i = 0; i < woord.size(); i++){
            woord[i] = std::tolower(woord[i]);
        }
        Knoop<string, int>* woordKnoop = frequentieSplayboom.zoek(woord);
        if(woordKnoop != nullptr){
            // de data bij de binaire boom maakt niet uit
            woordKnoop->data++;
        } else {
            frequentieSplayboom.voegtoe(woord, 1, false);
            frequentieBinaireboom.voegtoe(woord, 1, false);
        }
        woordAantal++;
    }

    std::cout << "\tDiepte splayboom    = " << frequentieSplayboom.geefDiepte() << "\n";
    std::cout << "\tDiepte binaire boom = " << frequentieBinaireboom.geefDiepte() << "\n"; 

    std::cout << "\t20 maal zoeken naar 'unthrift':\n";

    Knoop<string, int>* binKnoop = frequentieBinaireboom.zoek("unthrift");
    int ouderAantalBinaireboom = 0;
    while(binKnoop->ouder){
        binKnoop = binKnoop->ouder;
        ouderAantalBinaireboom++;
    }

    // Omdat we bij de splayboom eerst de diepte moeten achterhalen kunnen we de normale zoekfunctie niet gebruiken (want die voert de splay uit), we implementeren hem dus hier opnieuw
    int ouderAantalSplayboom = 0;
    Boom<string, int>* plaats = &frequentieSplayboom;
	while (*plaats && (*plaats)->sleutel != "unthrift") {
		if ((*plaats)->sleutel < "unthrift")
			plaats = &(*plaats)->rechts;
		else
			plaats = &(*plaats)->links;

        ouderAantalSplayboom++;
	};
    // de gezochte knoop staat dan vanboven, dus kunnen we gewoon 19 bijtellen (de overige zoekoperaties)


    std::cout << "\t\tAantal knopen bezocht in binaire boom: " << ouderAantalBinaireboom << " * 20 = " << ouderAantalBinaireboom * 20 << "\n";
    std::cout << "\t\tAantal knopen bezocht in splayboom: " << ouderAantalSplayboom << " + (1 * 19) = " << ouderAantalSplayboom + 19 << "\n";

    std::cout << "\tTEST OK\n";

}


void maakOptimaleBinaireZoekboom(const char * bestandsnaam){
    /*
    Je kan ook eens vergelijken met de optimale binaire boom die je kan maken als je de opzoekfrequenties kent.

    Pas je programma zo aan dat je voor elk woord weet hoe dikwijls het wordt opgezocht.
    Stel, met dynamisch programmeren, de optimale zoekboom op.
    Kijk hoe efficiënt de operaties nu zijn.
    */

    SplayboomBottomUp<string, int> frequentieSplayboom;
    std::ifstream bestand(bestandsnaam);
    std::string woord;
    int woordAantal = 0;
    int cutoff = 100;
    while(bestand >> woord && woordAantal < cutoff){
        for(int i = 0; i < woord.size(); i++){
            woord[i] = std::tolower(woord[i]);
        }
        Knoop<string, int>* woordKnoop = frequentieSplayboom.zoek(woord);
        // bij binaire boom gaan we data niet bijhouden, is nutteloos omdat structuur enkel afhangt van de sleutels
        if(woordKnoop != nullptr){
            woordKnoop->data++;
        } else {
            frequentieSplayboom.voegtoe(woord, 1, false);
        }
        woordAantal++;
    }



    std::vector<std::pair<string, double>> p;
    frequentieSplayboom.inorder([&p, &woordAantal](const Knoop<string, int>& knoop){
        double kans = knoop.data / (double)woordAantal;
        p.push_back(std::make_pair(knoop.sleutel, kans));

    });

    double somDerKansen = 0;
    for(int i = 0; i < p.size(); i++){
        somDerKansen += p[i].second;
    }

    assert((int)somDerKansen == 1);

    // Ik ga er vanaf nu gewoon van uit dat die bladeren b_0, ... b_n van in de cursus onbelangrijk zijn.
    // Ik bepaal dus de optimale binaire zoekboom op basis van de gekende frequenties p_1, ... p_n
    // -> WERKT NIET, we hebben de frequenties q_0, ... q_n nodig
    int n = p.size();

    /* z =  [      0 1 2 ... n
              0  [ . . . ... .]    <-- DEZE RIJ WORDT NIET GEBRUIKT
              1  [ . . . ... .]
              2  [ . . . ... .]
              ...[ . . . ... .]
            n+1  [ . . . ... .]
            ]
    */        
    std::vector<std::vector<double>> z(n+1, std::vector<double>(n)); 
    std::vector<std::vector<double>> g(n+1, std::vector<double>(n)); 
    std::vector<std::vector<double>> r(n, std::vector<double>(n)); 




}


/*
* Geef parameter 'test' mee om testen uit te voeren
*/
int main(int argc, char * argv[]){
    if(argc == 2 && strcmp(argv[1], "test") == 0){
        testSplay1Tot100EnZoek1BottomUp();   
        testSplay50BottomUp(); 
        testShakespeare();
    }

    maakOptimaleBinaireZoekboom("AChristmasCarol.txt");
    return 0;
}