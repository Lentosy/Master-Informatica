#ifndef BELLMANFORD_HPP
#define BELLMANFORD_HPP

#define WITH_QUEUE 0

#include "graph.hpp"
#include <deque>
using std::deque;
#include <vector>
using std::vector;
#include <limits>
using std::numeric_limits;

class BellmanFord
{
  public:
    BellmanFord() = default;
    BellmanFord(GraphWithEdgeData<DIRECTED, int> &G, int s, vector<int> &P, vector<int> &D)
    {
        D = vector<int>(G.numberOfVertices(), numeric_limits<int>::max());
        P = vector<int>(G.numberOfVertices(), -1);
        P[s] = 0;
        D[s] = 0;

        std::stack<int> S;
        S.push(s);
        while (!S.empty())
        {
            int current = S.top();
            S.pop();
            for (auto it = G[current].begin(); it != G[current].end(); it++)
            {
                if (D[it->first] > D[current] + *G.getEdgeData(current, it->first))
                {
                    D[it->first] = D[current] + *G.getEdgeData(current, it->first);
                    P[it->first] = current;
                    S.push(it->first);
                }
            }
        }
    }

    void BellmanFord_Pape(GraphWithEdgeData<DIRECTED, int> &G, int s, vector<int> &P, vector<int> &D)
    {
        D = vector<int>(G.numberOfVertices(), numeric_limits<int>::max());
        P = vector<int>(G.numberOfVertices(), -1);
        P[s] = 0;
        D[s] = 0;
        std::deque<int> deque;
        vector<bool> hasBeenInDeque(G.numberOfVertices(), false);
        deque.push_back(s);
        hasBeenInDeque[s] = true;
        while (!deque.empty())
        {
            int current = deque.front();
            deque.pop_front();

            for (auto it = G[current].begin(); it != G[current].end(); it++)
            {
                if (D[it->first] > D[current] + *G.getEdgeData(current, it->first))
                {
                    D[it->first] = D[current] + *G.getEdgeData(current, it->first);
                    P[it->first] = current;
                    if (hasBeenInDeque[it->first])
                    {
                        deque.push_front(it->first);
                    }
                    else
                    {
                        deque.push_back(it->first);
                    }
                }
            }
        }
    }
};

#endif