#include "grootstecapaciteitenpadzoeker.hpp"
#include "kortstepadzoeker.hpp"
#include "langpadzoeker.hpp"
#include "flownet.hpp"
#include "stroomnetwerkgenerator.hpp"

#include <iostream>
#include <memory>

using namespace std;

int main(int argc, char ** argv)
{
    GraphWithEdgeData <DIRECTED,int> gr(8);
    gr.insertEdge(1,2,7 );
    gr.insertEdge(7,1,2 );
    gr.insertEdge(7,3,6 );
    gr.insertEdge(3,4,7 );
    gr.insertEdge(4,5,1 );
    gr.insertEdge(2,5,4 );
    gr.insertEdge(1,0,9 );
    gr.insertEdge(0,2,3 );
    gr.insertEdge(0,7,5 );
    gr.insertEdge(0,6,6 );
    gr.insertEdge(5,6,6 );
    gr.insertEdge(6,3,2 );
    gr.insertEdge(6,4,8 );
    GraphWithEdgeData <DIRECTED,int> gr2(gr);
    Pad<int> pad;
    unique_ptr<VolgendPadZoeker<int>> volgendpadzoeker = make_unique<GrootsteCapaciteitenPadZoeker<int>>();
    Stroomnetwerk<int> sn(gr,1,4,volgendpadzoeker.get());
    cout<<sn<<endl;
    assert(sn.geef_capaciteit()==13);
    cout << "Done..." << endl;
}

/* https://stackoverflow.com/questions/19453217/why-are-back-edges-required-in-the-ford-fulkerson-algorithm#19720139
 *
 * Back edges are necessary when doing the Ford-Fulkerson algorithm in case the path that you choose ends up not being a
 * part of the overall flow.
 * As an example where back edges are necessary, consider this flow network:
 *
 *     s
 *    / \
 *   a   b
 *    \ / \
 *     c   d
 *      \ /
 *       t
 *
 * Assume that all edges point down and that all edges have capacity 1 and that you want to find a flow from s to t.
 * Suppose on the first iteration of Ford-Fulkerson that you take the path s -> b -> c -> t. At this point, you've
 * pushed one unit of flow from s to t. If you don't add in any back edges, you're left with this:
 *
 *     s
 *    /
 *   a   b
 *    \   \
 *     c   d
 *        /
 *       t
 *
 * There are no more s-t paths, but that doesn't mean you have a max flow. You can push two units of flow from s to t by
 * sending one along the path s -> a -> c -> t and the other along the path s -> b -> d -> t. Without any back edges in
 * the residual flow network, you would never discover this other path.
 *
 * Hope this helps!
 */