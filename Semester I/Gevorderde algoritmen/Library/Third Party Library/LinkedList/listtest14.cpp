// testing program for the c++14 linked list implementation
#include <iostream>
#include <cstdlib>
#include "list14.hpp"
#include <string>

using std::cout;
using std::string;
int nodesCreated = 0;
int nodesRemoved = 0;

List<int> createList()
{
    List<int> l;
    l.add(int(7));
    l.add(int(45));
    l.add(int(15));
    l.add(int(45));
    l.add(int(25));
    l.add(int(35));
    l.add(int(45));
    l.add(int(55));
    nodesCreated += 8;
    return l;
};

int main(int argc, char **argv)
{
    {
        cout << "Creating bare list, called l1" << endl;
        List<int> l1;
        l1 = createList();
        l1.output(cout);
        cout << endl;
        ListNode<int>::control(nodesCreated, nodesRemoved);
        cout<<endl<<endl;

        cout << "Removing two nodes" << endl;
        l1.remove(45);
        nodesRemoved++;
        
        l1.remove(123);
        
        ListNode<int>::control(nodesCreated, nodesRemoved);
        cout<<endl<<endl;

        //    //    for (auto s:l)
        //    //        cout<<s<<"\n";
        //    //    l.output(cout);

        cout << "Calling createList() without assigning the result" << endl;
        createList();
        nodesRemoved += 8;
        ListNode<int>::control(nodesCreated, nodesRemoved);
        cout<<endl<<endl;

        cout << "Calling createList() as the constructor argument for a List<int>, called l2" << endl;
        List<int> l2(createList());
        ListNode<int>::control(nodesCreated, nodesRemoved);
        cout<<endl<<endl;

        cout << "Assigning l1 to l2" << endl;
        l2 = l1;
        if (l2 != l1)
        {
            cout << "copy yields a different list" << endl;
            exit(-1);
        }
        else
        {
            cout << "copy yields the same list, YAY!" << endl;
        }
        cout << "The content of l1" << endl;
        l1.output(cout);
        cout << "The content of l2" << endl;
        l2.output(cout);
        cout << "\n";
        nodesRemoved += 8;
        nodesCreated += 7;
        ListNode<int>::control(nodesCreated, nodesRemoved);
        cout<<endl<<endl;

        cout << "Assigning l1 to l2 again" << endl;
        l2 = l1;
        nodesCreated += 7;
        nodesRemoved += 7;
        ListNode<int>::control(nodesCreated, nodesRemoved);
        cout<<endl<<endl;

        cout << "Assigning l2 to itself" << endl;
        l2 = l2;
        l2.output(cout);
        ListNode<int>::control(nodesCreated, nodesRemoved);
        cout<<endl<<endl;

        
        cout << "Creating a new, empty List<int>, called l3" << endl;
        List<int> l3;
        cout << "Adding one element to l3" << endl;
        l3.add(int(99));
        nodesCreated++;
        ListNode<int>::control(nodesCreated, nodesRemoved);
        cout<<endl<<endl;

        cout << "l3 = l2 = l1 statement" << endl;
        l3 = l2 = l1;
        nodesRemoved += 8;
        nodesCreated += 14;
        ListNode<int>::control(nodesCreated, nodesRemoved);
        cout<<endl<<endl;

        cout << "Calling insertion sort on the list" << endl;
        l2.insertionsort();
        cout << "Does this look sorted?" << endl;
        cout << "Content of l2:" << endl;
        l2.output(cout);
        cout << endl;
        ListNode<int>::control(nodesCreated, nodesRemoved);
        cout<<endl<<endl;

        cout << "verwijderen" << endl;
        cout << "Content of l1:" << endl;
        l1.output(cout);
        cout << endl;
        l1.remove(45);
        l1.remove(45);
        l1.remove(45);
        l1.remove(45);
        nodesRemoved += 2;
        cout << "Content of l1:" << endl;
        l1.output(cout);
        cout << endl;
        ListNode<int>::control(nodesCreated, nodesRemoved);
        cout<<endl<<endl;

        cout << "swappen" << endl;
        swap(l2, l1);
        ListNode<int>::control(nodesCreated, nodesRemoved);
        //        l2.output(cout);
        //        cout<<"\n";
    }
    nodesRemoved += 19;
    ListNode<int>::control(nodesCreated, nodesRemoved);
    return 0;
}
