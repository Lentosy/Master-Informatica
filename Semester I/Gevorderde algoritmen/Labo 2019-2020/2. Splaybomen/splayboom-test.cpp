#include "splayboom.cpp"
#include <iostream>
#include <string>
#include <fstream>

void testSplay1Tot100EnZoek1(){
    Splayboom<int, int> boom;
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
    boom.zoek(1);
    assert(boom == testZoek1);

    std::cout << "Test 1 OK\n";
}

void testSplay50(){
    int c = 50;

    Splayboom<int, int> boom;
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
    boom.zoek(50);
    assert(boom == testZoek50);
    std::cout << "Test 2 OK\n";
}


void testShakespeare() {
    Splayboom<string, int> frequentieSplayboom;
    Boom<string, int> frequentieBinaireBoom;
    std::ifstream file("shakespeare.txt");
    std::string word;
    int wordCount = 0;
    int totalWords = 100;
    
    while(file >> word && wordCount < totalWords){
        for(int i = 0; i < word.size(); i++){
            word[i] = std::tolower(word[i]);
        }
        Knoop<string, int>* woordKnoop = frequentieSplayboom.zoek(word);
        // bij binaire boom gaan we data niet bijhouden, is nutteloos omdat structuur enkel afhangt van de sleutels
        if(woordKnoop != nullptr){
            woordKnoop->data++;
        } else {
      //      frequentieBinaireBoom.voegtoe(word, 1, false);
            frequentieSplayboom.voegtoe(word, 1, false);
        }
        wordCount++;
    }

    std::cout << "Diepte splayboom    = " << frequentieSplayboom.geefDiepte() << "\n";
    //std::cout << "Diepte binaire boom = " << frequentieBinaireBoom.geefDiepte() << "\n";

    std::vector<std::pair<string, double>> p;
    frequentieSplayboom.inorder([&p, &totalWords](const Knoop<string, int>& knoop){
        double kans = knoop.data / (double)totalWords;
     //   std::cout << knoop.data << "\n";
        p.push_back(std::make_pair(knoop.sleutel, kans ));

    });

    double sumChances = 0;
    for(int i = 0; i < p.size(); i++){
        sumChances += p[i].second;
    }

    std::cout << sumChances << "\n";
    
    frequentieSplayboom.teken("dot/splayboom-shakespeare.dot");
}


int main(void){
    testSplay1Tot100EnZoek1();   
    testSplay50(); 
    testShakespeare();

    return 0;
}