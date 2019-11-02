#include <iostream>
#include <memory>
#include "bst14.hpp"

using namespace std;

bool creationTest();
bool sizeTest();
bool depthTest();
bool rotateTest();
bool balanceTest();

void print_break();

int main(int argc, char **argv)
{
    creationTest() ? cout << "Creation test succeeded" << endl : cerr << "Creation test failed" << endl;    
    sizeTest() ? cout << "Size test succeeded" << endl : cerr << "Size test failed" << endl;
    depthTest() ? cout << "Depth test succeeded" << endl : cerr << "Depth test failed" << endl;
    rotateTest() ? cout << "Rotate test succeeded"<<endl:cerr<<"Rotate test failed"<<endl;
    balanceTest() ? cout << "Balance test succeeded"<<endl:cerr<<"Balance test failed"<<endl;
    return 0;
}

bool creationTest()
{
    BST<int, int> t;
    t.add(10, 1);
    t.add(5, 2);
    t.add(15, 3);
    //cout << "t1\t";
    //t.output(cout);
    BST<int, int> t2 = move(t);
    //cout << "t1\t";
    //t.output(cout);
    //cout << "t2\t";
    //t2.output(cout);
    //BST<int,int> t3 = t2;
    BST<int, int> t4;
    t4 = move(t2);
    //cout << "t2\t";
    //cout << "t4\t";
    //t4.output(cout);
    //t4 = t3;

    BST<int, int> nodeptr = std::make_unique<BSTnode<int, int>>();
    t4 = move(nodeptr);
    return true;
}

bool sizeTest()
{
    BST<int, double> t1;
    t1.add(5, 3.9);
    t1.add(9, 2.5);
    t1.add(12, 2.0);
    t1.add(4, 1.9);

    BST<int, int> t2;

    return t1.size() == 4 && t2.size() == 0;
}

bool depthTest()
{
    BST<int, int> t1;
    t1.add(100, 1);
    t1.add(200, 2);
    t1.add(300, 3);
    t1.add(400, 6);
    t1.add(350, 7);
    t1.add(25, 4);
    t1.add(50, 5);

    BST<int, int> t2;
    t2.add(100, 100);
    t2.add(50, 50);
    t2.add(60, 60);
    t2.add(70, 70);
    t2.add(80, 80);
    t2.add(65, 65);
    t2.add(200, 200);
    t2.add(150, 150);
    t2.add(250, 250);

    BST<int, int> t3;
    t3.add(100, 100);

    return t1.depth() == 4 && t2.depth() == 4 && t3.depth() == 0;
}

bool rotateTest(){    
    BST<int,int> t1;
    t1.add(6,6);
    t1.add(8,8);
    t1.add(4,4);
    t1.add(3,3);
    t1.add(5,5);
    t1.add(7,7);
    t1.add(9,9);   
    t1.pretty_print();
    print_break();
    t1.rotate(true);
    t1.pretty_print();
    print_break();
    t1.rotate(false);
    t1.pretty_print();
    print_break();
    t1->getChild(false).rotate(true);
    t1.pretty_print();
    print_break();

    BST<int,int> t2;
    t2.add(2,2);
    t2.add(3,3);    
    t2.add(1,1);
    t2.pretty_print();
    print_break();
    t2.rotate(false);
    t2.pretty_print();
    print_break();        

    return true;
}

bool balanceTest(){
    BST<int,int> t1;
    t1.add(6,6);
    t1.add(8,8);
    t1.add(4,4);
    t1.add(3,3);
    t1.add(5,5);
    t1.add(7,7);
    t1.add(9,9);   
    t1.pretty_print();
    print_break();
    t1.makeImbalanced();
    t1.pretty_print();
    print_break();
    t1.makeBalanced();
    t1.pretty_print();
    print_break();

    t1.add(10,10);
    t1.makeImbalanced();
    t1.pretty_print();
    print_break();
    t1.makeBalanced();
    t1.pretty_print();
    print_break();


    return true;
}

void print_break() {
    cout<< "\n===========\n";
}