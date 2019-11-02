#ifndef KOSARAJU_HPP
#define KOSARAJU_HPP

#include "graph.hpp"
#include <stack>
using std::stack;
#include <vector>
using std::vector;
#include <utility>
using std::move;

class Kosaraju
{
  public:
    Kosaraju(Graph<DirectionType::DIRECTED> &g) : graph(g)
    {
        inverted = move(g.transpose(g));
    }

    void findSCCs()
    {
        stack<int> finished;
        vector<bool> visited(graph.numberOfVertices(), false);

        for (int i = 0; i < inverted.numberOfVertices(); i++)
        {
            if (!visited[i])
            {
                recursion(i, finished, visited);
            }
        }

        visited = vector<bool>(graph.numberOfVertices(), false);
        int filler = 0;
        while (!finished.empty())
        {
            if (!visited[finished.top()])
            {
                vector<int> SCC;
                stack<int> local_dfs_stack;
                local_dfs_stack.push(finished.top());
                while (!local_dfs_stack.empty())
                {
                    int k = local_dfs_stack.top();
                    local_dfs_stack.pop();
                    if (!visited[k])
                    {
                        visited[k] = true;
                        SCC.push_back(k);
                        for (auto it = graph[k].begin(); it != graph[k].end(); it++)
                        {
                            local_dfs_stack.push(it->first);
                        }
                    }
                }
                SCCs.push_back(move(SCC));
            }
            finished.pop();
        }
    }

  private:
    void recursion(int current, stack<int> &finished, vector<bool> &visited)
    {
        // This is DFS on inverted, with postorder numbering, the first step of Kosaraju's algorithm
        if (!visited[current])
        {
            visited[current] = true;
            for (auto it = inverted[current].begin(); it != inverted[current].end(); it++)
            {
                recursion(it->first, finished, visited);
            }
            finished.push(current); // this is postorder numbering, because the node is only added after the neighbors and their neighbors etc are done
        }
    }
    Graph<DirectionType::DIRECTED> graph;
    Graph<DirectionType::DIRECTED> inverted;

  public:
    vector<vector<int>> SCCs; // Strongly connected components
};

#endif