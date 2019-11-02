#include <iostream>
#include <fstream>
#include <vector>
#include "bintree.hpp"

using namespace std;

int main()
{
    ifstream invoer("jacht.txt");
    if (!invoer)
    {
        cerr << "Invoerbestand niet gevonden" << endl;
        return -1;
    }
    else
    {
        BinTree<string> bt;
        invoer >> bt;

        vector<string> inorder;
        vector<string> preorder;
        vector<string> postorder;

        auto inorderfct = [&inorder](string &&waarde) { inorder.push_back(move(waarde)); };
        auto preorderfct = [&preorder](string &&waarde) { preorder.push_back(move(waarde)); };
        auto postorderfct = [&postorder](string &&waarde) { postorder.push_back(move(waarde)); };

        cout<<"Tree content (BFS):"<<endl;
        auto bfsfct = [](string &&waarde) {cout<<waarde<<" . ";};
        bt.BFS(bfsfct);
        cout<<endl;

        cout<<"Writing to file:"<<endl;
        bt.output_to_stream(cout);

        // bt.DFS(preorderfct, inorderfct, postorderfct);

        bt.DFS(preorderfct, Order::Pre);
        cout << "Preorder DFS traversal yields Question: ";
        for (const string &word : preorder)
        {
            cout << word << " ";
        }

        bt.DFS(inorderfct, Order::In);
        cout << endl;
        cout << "Inorder DFS traversal yields Answer: ";
        for (const string &word : inorder)
        {
            cout << word << " ";
        }
        cout << endl;
    }
    invoer.close();
    return 0;
}
