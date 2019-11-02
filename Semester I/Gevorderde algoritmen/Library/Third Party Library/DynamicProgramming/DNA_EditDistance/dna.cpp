#include "dna.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

void test_top_down();
void test_bottom_up();

int main(int argc, char **argv)
{
    cout<<"Testing bottom up"<<endl;
    test_bottom_up();
    cout<<"Testing top down"<<endl;
    test_top_down();    
}

void test_top_down() {
     vector<DNAsequence> chimp_dna;
    ifstream file{"chimp.dna"};
    DNAsequence chimp;
    while (file >> chimp)
    {
        chimp_dna.push_back(chimp);
    }
    file.close();
    file.clear();

    file.open("human.dna");
    DNAsequence human;
    auto start_time = chrono::steady_clock::now();
    int i = 0;
    while (file >> human)
    {
        int min_index = 0;
        int min_distance = numeric_limits<int>::max();
        for (int j = 0; j < static_cast<int>(chimp_dna.size()); j++)
        {
            int distance = human.d_top_down(chimp_dna[j]);
            if (distance < min_distance)
            {
                min_distance = distance;
                min_index = j;
            }
        }
        cout << "Human " << i << " matches chimp " << min_index << " with distance " << min_distance << endl;
        i++;
    }

    auto finish_time = chrono::steady_clock::now();
    chrono::duration<double> diff = finish_time - start_time;

    file.close();
    file.clear();
    cout << "Total time needed for DNA comparisons: " << diff.count() << " s" << endl;
}

void test_bottom_up() {
     vector<DNAsequence> chimp_dna;
    ifstream file{"chimp.dna"};
    DNAsequence chimp;
    while (file >> chimp)
    {
        chimp_dna.push_back(chimp);
    }
    file.close();
    file.clear();

    file.open("human.dna");
    DNAsequence human;
    auto start_time = chrono::steady_clock::now();
    int i = 0;
    while (file >> human)
    {
        int min_index = 0;
        int min_distance = numeric_limits<int>::max();
        for (int j = 0; j < static_cast<int>(chimp_dna.size()); j++)
        {
            int distance = human.d_bottom_up(chimp_dna[j]);
            if (distance < min_distance)
            {
                min_distance = distance;
                min_index = j;
            }
        }
        cout << "Human " << i << " matches chimp " << min_index << " with distance " << min_distance << endl;
        i++;
    }

    auto finish_time = chrono::steady_clock::now();
    chrono::duration<double> diff = finish_time - start_time;

    file.close();
    file.clear();
    cout << "Total time needed for DNA comparisons: " << diff.count() << " s" << endl;
}