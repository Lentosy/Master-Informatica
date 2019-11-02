#ifndef STROOMNETWERKGENERATOR_HPP
#define STROOMNETWERKGENERATOR_HPP
#include <random>

#include "../Graphs/graph.hpp"

class Stroomnetwerkgenerator
{
public:
    virtual GraphWithEdgeData<DIRECTED, int>* nieuw_stroomnetwerk(int aantal_knopen, double takkans, int max_gewicht)
    {
        GraphWithEdgeData<DIRECTED, int>* nieuwe_graaf = new GraphWithEdgeData<DIRECTED, int>(aantal_knopen);

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> welke_takdata(0, max_gewicht);
        std::uniform_real_distribution<double> is_er_verbinding(0, 1);

        for (int i = 0; i < aantal_knopen; i++)
        {
            for (int j = 0; j < aantal_knopen; j++)
            {
                if ((j != i) && (is_er_verbinding(mt) < takkans))
                {
                    nieuwe_graaf->insertEdge(i, j, welke_takdata(mt));
                }
            }
        }

        return nieuwe_graaf;
    }
};

#endif