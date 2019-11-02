// This header contains the code for the following classes
//
//
//    Graph<DirectionType>: base class without data on the edges / vertices
//    GraphWithEdgeData<DirectionType,EdgeData>
//    GraphWithVertexData<DirectionType,VertexData>
//    GraphWithNodeAndEdgeData<DirectionType,VertexData,EdgeData>
//
//
// Plus a GraphException class
/**********************************************************************

   Class: Graph

   description: Graph is the base class for a hierarchy of sparse graphs (meaning adjacency list).
                  The hierarchy contains classes for graphs with data on the nodes and or edges.
                  The data is stored in vectors as to enable searching with the indices.
                  
        regarding vertices: Vertices are numbered sequentially. It is not possible to remove individual nodes.
                            You can erase the entire graph with the remove() function and nodes may be inserted one by one
              
        regarding edges: Edges may freely be added or removed. Each edge has a number and a stack is maintained if numbers open up
                         after deletion. If no number is available on that stack then a new number is used.
        
                     highest_edge_number kan nooit verkleinen, en de
                      vector met takdata zal altijd highest_edge_number elementen bevatten.


 ***************************************************************************/

#ifndef __GRAPH_H
#define __GRAPH_H

#include <exception>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

enum DirectionType
{
    DIRECTED,
    UNDIRECTED
};

class GraphException : public std::logic_error
{
  public:
    GraphException(const std::string &message_) : std::logic_error(message_)
    {
    }
};

std::ostream &operator<<(std::ostream &os, const GraphException &exc)
{
    return os << exc.what();
}

template <DirectionType RT>
class Graph
{
  public:
    // Vertex.first = vertex number of neighbor, Vertex.second = edge number
    typedef std::map<int, int> Vertex;

    // Constructs a graph with n vertices, without edges
    Graph(int n = 0);

    // Returns true for a DIRECTED graph or false if UNDIRECTED
    bool isDirected() const;

    bool isConnected(const Graph<RT> &);

    int isEulerian(const Graph<RT> &);

    Graph<RT> transpose(Graph<RT> &);

    bool isStronglyConnected(Graph<RT> &);

    // Adds a new 'empty' vertex (one without edges)
    // Returns the vertex number of the new node
    virtual int insertVertex();

    // Adds an edge between the nodes with numbers from and to
    // Throws a GraphException if the edge already exists or if the vertex numbers are invalid
    // Returns the edge number of the new edge
    // In an UNDIRECTED graph this function will add 2 edges u->v & v->u, however with the same edge number
    virtual int insertEdge(int from, int to);

    // Removes the edge between the nodes with numbers from and to, including the 2nd edge if called on an UNDIRECTED graph.
    // Throws a GraphException if the node numbers are invalid, however no exception if thrown if the edge didn't exist
    // It doesn't renumber the remaining edges after deletion
    virtual void removeEdge(int from, int to);

    // Returns the number of vertices in the graph
    int numberOfVertices() const;

    // Returns the number of edges in the graph
    // In undirected graphs, the edges are NOT counted twice.
    int numberOfEdges() const;

    // Returns the edge number of the edge between from and to
    // Returns -1 if there is no edge between from and to
    // Throws a GraphExcpetion if a node number is invalid
    // Complexity is O(log(E)) with E the number of edges originating at the from vertex
    int edgeNumber(int from, int to) const;

    // Removes all vertices and edges and resets the edge count
    virtual void remove();

    // Access to the vertices

    const Vertex &operator[](int i) const
    {
        return vertices[i];
    }

    // this one may be used as lvalue, while the const one doens't allow this
    Vertex &operator[](int i)
    {
        return vertices[i];
    }

    // Writes a representation of the graph to the supplied output stream
    virtual void output(std::ostream &os) const;

    // Writes the data of the vertex with number v to os
    virtual void outputVertex(std::ostream &os, int v) const;

    // Writes the data of the edge with number e to os
    virtual void outputEdge(std::ostream &os, int e) const;

    std::string generate_dot_code() const;

  protected:
    void checkVertexNumber(int v) const; // throw if v is invalid
    void addEdgeToDatastructure(int from, int to, int edge_number);
    void removeEdgeFromDatastructure(int from, int to);
    void DFS(const Graph<RT> &graph,
             int vertex_nr,
             std::vector<bool> &already_visisted,
             std::function<void(int vertex_nr)> prefix_function,
             std::function<void(int vertex_nr)> postfix_function);

  protected:
    std::vector<Vertex> vertices;
    int highest_edge_number;
    DirectionType direction_type;
    std::stack<int> reusable_edge_numbers;
};

template <DirectionType RT>
std::ostream &operator<<(std::ostream &os, const Graph<RT> &g);

// --- implementation ---
template <DirectionType RT>
bool Graph<RT>::isConnected(const Graph<RT> &graph)
{
    throw "not supported";
}

template <>
bool Graph<UNDIRECTED>::isConnected(const Graph<UNDIRECTED> &graph)
{
    std::vector<bool> visited(vertices.size(), false);
    int i = 0;
    while (i < vertices.size() && vertices[i].size() == 0)
    {
        i++;
    }
    if (i == vertices.size())
    {
        // there are vertices, but no edges, every vertex is a connected component
        return true;
    }
    auto lambda = [](int) -> void {};
    DFS(graph, i, visited, lambda, lambda);
    i = 0;
    while (i < vertices.size())
    {
        if (vertices[i].size() > 0 && visited[i] == false)
        {
            return false;
        }
        i++;
    }
    return true;
}

template <>
int Graph<UNDIRECTED>::isEulerian(const Graph<UNDIRECTED> &graph)
{
    // return 0: not Eulerian
    // return 1: semi-Eulerian, has an Eulerian path, but no Eurlerian circuit
    // return 2: Eulerian, has a Eulerian circuit
    if (!isConnected(graph))
    {
        return 0;
    }
    int odd = 0;
    for (int i = 0; i < graph.numberOfVertices(); i++)
    {
        if (graph[i].size() & 1)
        {
            odd++;
        }
    }
    if (odd > 2)
    {
        return 0;
    }
    // odd == 2 -> semi-eulerian, meaning the endpoints have an odd number of neighbors
    // odd == 0 -> eulerian, meaning all nodes have even numbers of neighbors
    return odd ? 1 : 2;
}

template <DirectionType RT>
Graph<RT> Graph<RT>::transpose(Graph<RT> &)
{
    throw "Not supported";
}

template <>
Graph<DIRECTED> Graph<DIRECTED>::transpose(Graph<DIRECTED> &graph)
{
    Graph<DIRECTED> g(graph.numberOfVertices());
    int i = 0;
    while (i < g.numberOfVertices())
    {
        for (const auto &neighbor : vertices[i])
        {
            g.insertEdge(neighbor.first, i);
        }
        i++;
    }
    return g;
}

template <DirectionType RT>
bool Graph<RT>::isStronglyConnected(Graph<RT> &g)
{
    throw "Not supported";
}

template <>
bool Graph<DIRECTED>::isStronglyConnected(Graph<DIRECTED> &g)
{
    // note that this function only tells you if the directed graph is stronlgy connected
    // it does not return the components, nor has the machinery to keep track of them
    Graph<DIRECTED> transposed = std::move(transpose(g));
    bool transposed_connected = isConnected(transposed);

    if (transposed_connected)
    {
        return isConnected(g);
    }
    else
    {
        return false;
    }
}

template <DirectionType RT>
std::string Graph<RT>::generate_dot_code() const
{
    throw "Not supported";
}

template <>
std::string Graph<DIRECTED>::generate_dot_code() const
{
    std::stringstream out;

    out << "digraph graph {" << std::endl;

    for (int i = 0; i < numberOfVertices(); i++)
    {
        const auto &vertex = (*this)[i];

        for (const auto &it : vertex)
        {
            out << "\t" << i << " -> " << it.first << std::endl;
        }
    }

    out << "}" << std::endl;

    return out.str();
}

template <DirectionType RT>
void Graph<RT>::DFS(const Graph<RT> &graph,
                    int vertex_nr,
                    std::vector<bool> &already_visisted,
                    std::function<void(int vertex_nr)> prefix_function,
                    std::function<void(int vertex_nr)> postfix_function)
{
    if (already_visisted[vertex_nr])
    {
        return;
    }

    prefix_function(vertex_nr);

    already_visisted[vertex_nr] = true;
    for (const auto &neighbor : graph[vertex_nr])
    {
        DFS(graph, neighbor.first, already_visisted, prefix_function, postfix_function);
    }

    postfix_function(vertex_nr);
}

template <DirectionType RT>
void Graph<RT>::checkVertexNumber(int v) const
{
    if (v < 0 || (size_t)v >= vertices.size())
        throw GraphException("invalid vertex number");
}

template <DirectionType RT>
Graph<RT>::Graph(int n) : vertices(n), highest_edge_number(0)
{
}

template <DirectionType RT>
bool Graph<RT>::isDirected() const
{
    return true;
} // for a DIRECTED GRAPH

template <>
bool Graph<UNDIRECTED>::isDirected() const
{
    return false;
} // for an UNDIRECTED GRAPH

template <DirectionType RT>
int Graph<RT>::insertVertex()
{
    // the new vertex index is the index in the vertices vector
    int n = vertices.size();
    vertices.resize(n + 1); // resize will use the default constructor (add an empty map)
    return n;
}

template <DirectionType RT>
int Graph<RT>::insertEdge(int from, int to)
{
    checkVertexNumber(from);
    checkVertexNumber(to);

    if (vertices[from].count(to) > 0)
    {
        std::ostringstream out;
        out << "edge " << from << "-" << to << " already exists";
        throw GraphException(out.str());
    }
    else
    {
        int edgeNumber;
        if (!reusable_edge_numbers.empty())
        {
            edgeNumber = reusable_edge_numbers.top();
            reusable_edge_numbers.pop();
        }
        else
            edgeNumber = highest_edge_number++;
        addEdgeToDatastructure(from, to, edgeNumber);
        return edgeNumber;
    }
}

template <DirectionType RT> // voor gerichte graph
void Graph<RT>::addEdgeToDatastructure(int from, int to, int edgeNumber)
{
    vertices[from][to] = edgeNumber;
}

template <>
void Graph<UNDIRECTED>::addEdgeToDatastructure(int from, int to, int edgeNumber)
{
    vertices[from][to] = edgeNumber;
    vertices[to][from] = edgeNumber;
}

template <DirectionType RT>
void Graph<RT>::removeEdge(int from, int to)
{
    checkVertexNumber(from);
    checkVertexNumber(to);
    if (vertices[from].find(to) != vertices[from].end())
    { // edge exists
        reusable_edge_numbers.push(vertices[from][to]);
        removeEdgeFromDatastructure(from, to);
    }
    // does not throw exception if the edge doesn't exist
}

template <DirectionType RT>
void Graph<RT>::removeEdgeFromDatastructure(int from, int to)
{
    vertices[from].erase(to);
}

template <>
void Graph<UNDIRECTED>::removeEdgeFromDatastructure(int from, int to)
{
    vertices[from].erase(to);
    vertices[to].erase(from);
}

template <DirectionType RT>
int Graph<RT>::numberOfVertices() const
{
    return vertices.size();
}

template <DirectionType RT>
int Graph<RT>::numberOfEdges() const
{
    return highest_edge_number - reusable_edge_numbers.size();
}

template <DirectionType RT>
int Graph<RT>::edgeNumber(int from, int to) const
{
    checkVertexNumber(from);
    checkVertexNumber(to);
    Vertex::const_iterator verbindingit = vertices[from].find(to);

    if (verbindingit == vertices[from].end())
        return -1;
    else
        return (*verbindingit).second;
}

template <DirectionType RT>
void Graph<RT>::remove()
{
    vertices.clear();
    highest_edge_number = 0;
    while (!reusable_edge_numbers.empty())
        reusable_edge_numbers.pop();
}

template <DirectionType RT>
void Graph<RT>::output(std::ostream &os) const
{
    os << "Graph: " << numberOfVertices() << " vertices and " << numberOfEdges() << " edges:" << std::endl;
    for (int v = 0; v < numberOfVertices(); v++)
        outputVertex(os, v);
}

template <DirectionType RT>
void Graph<RT>::outputVertex(std::ostream &os, int v) const
{
    os << "vertex " << v << ":" << std::endl;
    for (Vertex::const_iterator it = vertices[v].begin(); it != vertices[v].end(); ++it)
    {
        os << "  ->" << it->first;
        outputEdge(os, it->second);
    }
}

template <DirectionType RT>
void Graph<RT>::outputEdge(std::ostream &os, int v) const
{
    os << " via " << v << std::endl;
}

template <DirectionType RT>
std::ostream &operator<<(std::ostream &os, const Graph<RT> &g)
{
    g.output(os);
    return os;
}

template <DirectionType RT, class EdgeData>
class GraphWithEdgeData : public virtual Graph<RT>
{
  public:
    // Constructs a graph of the given direction type with n vertices, no edges
    GraphWithEdgeData(int n = 0) : Graph<RT>(n){};
    // Note: it is only possible to have a insertion function where you don't immediately supply EdgeData
    // if the EdgeData class has a default constructor
    virtual int insertEdge(int from, int to);
    virtual int insertEdge(int from, int to, const EdgeData &);
    // Note: removeEdge is taken from Graph without changes

    // Returns a pointer to the EdgeData if the edge exists, nullptr otherwise
    // Note: pointers returned by getEdgeData are invalid if a new edge gets inserted
    const EdgeData *getEdgeData(int from, int to) const;
    EdgeData *getEdgeData(int from, int to);

    virtual void remove();

    // Now includes the data stored for the edge in the output to os
    virtual void outputEdge(std::ostream &os, int v) const;

  protected:
    std::vector<EdgeData> edgedata_vector;
};

template <DirectionType RT, class EdgeData>
int GraphWithEdgeData<RT, EdgeData>::insertEdge(int from, int to)
{
    return this->insertEdge(from, to, EdgeData());
}

template <DirectionType RT, class EdgeData>
int GraphWithEdgeData<RT, EdgeData>::insertEdge(int from, int to, const EdgeData &td)
{
    bool is_new_edge_number = this->reusable_edge_numbers.empty();
    int edge_number = Graph<RT>::insertEdge(from, to);
    if (is_new_edge_number)
    {
        edgedata_vector.push_back(td);
    }
    else
    {
        edgedata_vector[edge_number] = td;
    }

    return edge_number;
}

template <DirectionType RT, class EdgeData>
const EdgeData *GraphWithEdgeData<RT, EdgeData>::getEdgeData(int from, int to) const
{
    int edge_number = this->edgeNumber(from, to);
    if (edge_number != -1)
        return &edgedata_vector[edge_number];
    else
        return 0;
}

template <DirectionType RT, class EdgeData>
EdgeData *GraphWithEdgeData<RT, EdgeData>::getEdgeData(int from, int to)
{
    int edge_number = this->edgeNumber(from, to);
    if (edge_number != -1)
        return &edgedata_vector[edge_number];
    else
        return 0;
}

template <DirectionType RT, class EdgeData>
void GraphWithEdgeData<RT, EdgeData>::remove()
{
    Graph<RT>::remove();
    edgedata_vector.clear();
}

template <DirectionType RT, class EdgeData>
void GraphWithEdgeData<RT, EdgeData>::outputEdge(std::ostream &os, int v) const
{
    os << " via " << v << "(Data: " << edgedata_vector[v] << ")" << std::endl;
}

template <DirectionType RT, class VertexData>
class GraphWithVertexData : public virtual Graph<RT>
{
  public:
    template <class InputIterator>
    GraphWithVertexData(InputIterator start, InputIterator end);

    GraphWithVertexData() : Graph<RT>(){};

    virtual int insertVertex();
    virtual int insertVertex(const VertexData &);

    const VertexData *getVertexData(int knoopnr) const;
    VertexData *getVertexData(int knoopnr);
    virtual void remove();
    virtual void outputVertex(std::ostream &os, int v) const;

  protected:
    std::vector<VertexData> vertexdata_vector;
};

template <DirectionType RT, class VertexData>
template <class InputIterator>
GraphWithVertexData<RT, VertexData>::GraphWithVertexData(InputIterator start, InputIterator end) : Graph<RT>(0)
{
    for (; start != end; start++)
        insertVertex(*start);
}

template <DirectionType RT, class VertexData>
int GraphWithVertexData<RT, VertexData>::insertVertex()
{
    return this->insertVertex(VertexData());
}

template <DirectionType RT, class VertexData>
int GraphWithVertexData<RT, VertexData>::insertVertex(const VertexData &kd)
{
    int ret = Graph<RT>::insertVertex();
    vertexdata_vector.push_back(kd);
    return ret;
}

template <DirectionType RT, class VertexData>
const VertexData *GraphWithVertexData<RT, VertexData>::getVertexData(int edge_number) const
{
    this->checkVertexNumber(edge_number);
    return &vertexdata_vector[edge_number];
}

template <DirectionType RT, class VertexData>
VertexData *GraphWithVertexData<RT, VertexData>::getVertexData(int edge_number)
{
    this->checkVertexNumber(edge_number);
    return &vertexdata_vector[edge_number];
}

template <DirectionType RT, class VertexData>
void GraphWithVertexData<RT, VertexData>::remove()
{
    Graph<RT>::remove();
    vertexdata_vector.clear();
}

template <DirectionType RT, class VertexData>
void GraphWithVertexData<RT, VertexData>::outputVertex(std::ostream &os, int v) const
{
    os << "vertex " << v << "(Data: " << vertexdata_vector[v] << "):" << std::endl;
    for (std::map<int, int>::const_iterator it = this->vertices[v].begin(); it != this->vertices[v].end(); ++it)
    {
        os << "  ->" << it->first;
        this->outputEdge(os, it->second);
    }
}

template <DirectionType RT, class VertexData, class EdgeData>
class GraphWithNodeAndEdgeData : public GraphWithVertexData<RT, VertexData>, public GraphWithEdgeData<RT, EdgeData>
{
  public:
    template <class InputIterator>
    GraphWithNodeAndEdgeData(InputIterator start, InputIterator end) : GraphWithVertexData<RT, VertexData>(start, end){};

    GraphWithNodeAndEdgeData() : GraphWithVertexData<RT, VertexData>(){};

    virtual void remove()
    {
        GraphWithVertexData<RT, VertexData>::remove();
        this->edgedata_vector.clear();
    }
};

#endif // __GRAPH_H