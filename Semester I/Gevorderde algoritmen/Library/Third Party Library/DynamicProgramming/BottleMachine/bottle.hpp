#ifndef __BOTTLE_HPP
#define __BOTTLE_HPP

#include <limits>
#include <unordered_map>
using std::unordered_map;
#include <vector>
using std::vector;

class BottleMachine
{
  public:
    int min_nr_bottles_td(int, const vector<int> &);    

  private:
    int min_nr_bottles_td_op(int, const vector<int> &, unordered_map<int, int> &);    
};

int BottleMachine::min_nr_bottles_td(int content, const vector<int> &bottle_types)
{
    if (content < 0 || bottle_types.empty())
    {
        return 0;
    }
    unordered_map<int, int> solutions;
    int min_nr = min_nr_bottles_td_op(content, bottle_types, solutions);

    if (min_nr == -1)
    {
        return 0;
    }
    return min_nr;
}

int BottleMachine::min_nr_bottles_td_op(int content, const vector<int> &bottle_types, unordered_map<int, int> &solutions)
{
    // trivial
    if (content < 0)
    {
        return -1;
    }
    // trivial
    else if (content == 0)
    {
        return 0;
    }
    // recall
    auto found_content = solutions.find(content);
    if (found_content != solutions.end())
    {
        return found_content->second;
    }

    int min_nr = std::numeric_limits<int>::max();
    for (int bottle_type : bottle_types)
    {
        int current_nr = min_nr_bottles_td_op(content - bottle_type, bottle_types, solutions);
        if (current_nr != -1 && current_nr < min_nr)
        {
            min_nr = current_nr;
        }
    }
    // no min_nr hasn't changed, filling volume was impossible
    if (min_nr == std::numeric_limits<int>::max())
    {
        solutions[content] = -1;
    }
    // there is a way to fill the volume, also this solution will always work one bottle at a time
    else
    {
        solutions[content] = min_nr + 1;
    }
    return solutions[content];
}

#endif