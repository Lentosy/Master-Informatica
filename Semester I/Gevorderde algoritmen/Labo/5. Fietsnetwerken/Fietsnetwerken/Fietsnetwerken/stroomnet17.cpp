#include "stroomnet17.h"
#include <string>
#include "tinyxml.h"
using std::cout;
using std::endl;

template<class T>
void tekenStroomnetwerk(Stroomnetwerk<T>& stroomnetwerk, const char * cBestandsnaam, bool open_bestand) {
	std::string bestandsnaam(cBestandsnaam);
	
	std::string dotPad = bestandsnaam + ".dot";
	stroomnetwerk.teken(dotPad.c_str());
	std::string jpgPad = bestandsnaam + ".jpg";
	
	std::string commandstring = "dot -Tpng " + dotPad + " -o " + jpgPad;
	system(commandstring.c_str());
	if (open_bestand) {
		system(jpgPad.c_str());
	}
}

void losFietsnetwerkOp() {
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

	GraafMetTakdata <GERICHT, int> gr(180);

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
			gr.voegVerbindingToe(van, naar, afstand);

		}
	}
	int x = 5;
}

void testVoorbeeld() {
	GraafMetTakdata <GERICHT, int> gr(8);
	gr.voegVerbindingToe(1, 2, 7);
	gr.voegVerbindingToe(7, 1, 2);
	gr.voegVerbindingToe(7, 3, 6);
	gr.voegVerbindingToe(3, 4, 7);
	gr.voegVerbindingToe(4, 5, 1);
	gr.voegVerbindingToe(2, 5, 4);
	gr.voegVerbindingToe(1, 0, 9);
	gr.voegVerbindingToe(0, 2, 3);
	gr.voegVerbindingToe(0, 7, 5);
	gr.voegVerbindingToe(0, 6, 6);
	gr.voegVerbindingToe(5, 6, 6);
	gr.voegVerbindingToe(6, 3, 2);
	gr.voegVerbindingToe(6, 4, 8);
	Stroomnetwerk<int> sn(gr, 1, 4);
	//tekenStroomnetwerk(sn, "sn", false);

	Stroomnetwerk<int> oplossing = sn.geefStroom();
	//tekenStroomnetwerk(oplossing, "oplossing", true);
	std::cout << oplossing.geefCapaciteit();
	assert(oplossing.geefCapaciteit() == 13);
}

int main() {
	testVoorbeeld();
	return 0;
}
