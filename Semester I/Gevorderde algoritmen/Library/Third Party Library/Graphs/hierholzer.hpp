#ifndef HIERHOLZER_HPP
#define HIERHOLZER_HPP

#include "multigraph.hpp"
#include <map>
using std::map;
#include <list>
using std::list;
#include <stack>
using std::stack;
#include <vector>
using std::vector;

class Hierholzer
{
  public:
    Hierholzer(MultiGraph<UNDIRECTED> &graaf)
    { //Controleren of de graaf wel een Euler-circuit heeft
        int oneven = 0;
        int van, naar;
        for (int i = 0; i < graaf.aantalKnopen(); i++)
        {
            int teller = 0;
            for (auto it = graaf[i].begin(); it != graaf[i].end(); it++)
                teller += it->second.size();

            if (teller % 2 != 0)
            {
                oneven++;
                if (oneven == 1)
                    van = i;
                else
                    naar = i;
            }
        }

        //Als er geen knopen zijn met oneven aantal verbindingen, dan is knoop 0 het begin en eindpunt, en is het euler circuit volledig gesloten.
        if (oneven == 0)
        {
            van = naar = 0;
            oneven = 2; //Zodat we ook door het volgende if statement graken.
        }

        if (oneven == 2)
        {
            stack<int> S;
            vector<bool> visited(graaf.aantalVerbindingen(), false);
            S.push(van);
            while (!S.empty())
            {
                int allesBezochtKnoop = -1;
                int allesBezochtEdge = -1;
                // iterate over all neighbors of S.top()
                // the 2nd part allesBezochtKnoop == -1 could be replaced by allesBezochtEdge == -1
                // it is merely important to stop the loop as soon as we found a neighbor's edge that wasn't visited
                for (auto it = graaf[S.top()].begin(); it != graaf[S.top()].end() && allesBezochtKnoop == -1; it++)
                {
                    // look through all the edges
                    for (int i = 0; i < it->second.size(); i++)
                    {
                        // if we haven't visited an edge of the neighbor, capture the neighbor's vertex number and the edge number
                        if (visited[it->second[i]] == false)
                        {
                            allesBezochtKnoop = it->first;
                            allesBezochtEdge = it->second[i];
                        }
                    }
                }
                // if allesBezochtKnoop remained -1 then all the edges of all the neighbors of S.top were visited
                if (allesBezochtKnoop == -1)
                {
                    path.push_back(S.top());
                    S.pop();
                }
                // mark the neighbor's edge that stopped the for loop as visited 
                // and include the neighbor's vertex as a new point of interest
                // the algorithm will however not immediately pick up at the neighbor vertex
                // it will first test other neighbors of the currently tested vertex
                else
                {
                    S.push(allesBezochtKnoop);
                    visited[allesBezochtEdge] = true;
                }
            }
        }
    }

  public:
    std::list<int> path;
};

#endif