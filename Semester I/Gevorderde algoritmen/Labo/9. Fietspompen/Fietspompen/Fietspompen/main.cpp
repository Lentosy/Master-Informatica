#include "graaf.h"
#include "probprob.h"
#include "tinyxml.h"
#include <iostream>


void opdracht(std::vector<int>& knoopnummers) {
	TiXmlDocument doc("fietsgraaf.xml");
	bool loadOkay = doc.LoadFile();
	assert(loadOkay);
	TiXmlNode* netwerk;
	netwerk = doc.RootElement();
	assert(netwerk);
	//cout << netwerk->Value() << "\n";
	//Alternatief:
	//        for (TiXmlElement* knooppunt=netwerk->FirstChildElement();
	//                   knooppunt!=0;knooppunt=knooppunt->NextSiblingElement()){

	Graaf <ONGERICHT> gr(180);

	for (TiXmlNode* knooppunt = netwerk->FirstChild(); knooppunt != 0; knooppunt = knooppunt->NextSibling()) {
		//cout << knooppunt->Value() << "\n";
		//schrijfAttributen(dynamic_cast<TiXmlElement*>(knooppunt));
		for (TiXmlNode* route = knooppunt->FirstChild(); route != 0; route = route->NextSibling()) {
			//cout << route->Value() << "\n";
			//schrijfAttributen(dynamic_cast<TiXmlElement*>(route));
			TiXmlAttribute* attr = (dynamic_cast<TiXmlElement*>(route))->FirstAttribute();
			int van = std::stoi((dynamic_cast<TiXmlElement*>(knooppunt))->FirstAttribute()->Value());
			int naar = std::stoi(attr->Value());
			attr = attr->Next();
			double afstand = std::stod(attr->Value());
			//cout << van << "->" << naar << ", " << afstand << endl;
			try {
				gr.voegVerbindingToe(van, naar);
			} catch (GraafExceptie ex) {
			
			}

		}
	}

	Fietspompen vc(gr);
	knoopnummers = vc.geefOptimum(5000);
	
}

void testSuite(std::vector<int>& knoopnummers) {
	Graaf<RichtType::ONGERICHT> graaf;



	int A = graaf.voegKnoopToe();
	int B = graaf.voegKnoopToe();
	int C = graaf.voegKnoopToe();
	int D = graaf.voegKnoopToe();
	int E = graaf.voegKnoopToe();
	int F = graaf.voegKnoopToe();

	graaf.voegVerbindingToe(A, B);
	graaf.voegVerbindingToe(A, C);
	graaf.voegVerbindingToe(B, C);
	graaf.voegVerbindingToe(B, D);
	graaf.voegVerbindingToe(B, E);
	graaf.voegVerbindingToe(B, F);
	graaf.voegVerbindingToe(E, F);

	Fietspompen vc(graaf);
	knoopnummers = vc.geefOptimum(1000000);

}

int main(void) {

	std::vector<int> knoopnummers;
	clock_t t = clock();
	testSuite(knoopnummers);
	
	opdracht(knoopnummers);

	std::cout << "Zet een fietspomp op knopen: \n";
	for (int i = 0; i < knoopnummers.size(); i++) {
		std::cout << (char)(knoopnummers[i] + 'A') << "\n";
	}
	std::cout << "Aantal fietspompen : " << knoopnummers.size() << "\n";
	std::cout << (clock() - t) / CLOCKS_PER_SEC;

}