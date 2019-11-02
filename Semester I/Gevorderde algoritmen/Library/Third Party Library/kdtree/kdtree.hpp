#ifndef __KDTREE_HPP
#define __KDTREE_HPP

#include <tuple>
using std::tuple;
#include <vector>
using std::vector;
#include <utility>
using std::move;
#include <memory>
using std::make_unique;
using std::unique_ptr;
#include <cmath>
using std::floor;
using std::max;
#include <algorithm>
using std::sort;

template <class... Key>
class KdNode;

template <class... Key>
class KdTree : public unique_ptr<KdNode<Key...>>
{
  public:
    KdTree() = default;
    virtual ~KdTree() = default;
    KdTree(const KdTree<Key...> &) = default;
    KdTree<Key...> &operator=(const KdTree<Key...> &) = default;
    KdTree(KdTree<Key...> &&) = default;
    KdTree<Key...> &operator=(KdTree<Key...> &&) = default;
    KdTree(int _dim) : unique_ptr<KdNode<Key...>>(make_unique<KdNode<Key...>>()), dimensions{_dim}, mark_delete{false}, level_dimension{0} {} // the unique pointer constructor invocation is vital to proper construction
    // KdTree(int _dim) : dimensions{_dim} {} this is INSUFFICIENT, this won't create a KdNode with proper members, leading to nullpointer exceptions!

    int depth() const;
    int size() const;
   
    void insert(const vector<tuple<Key...>> &);
    void insert(vector<tuple<Key...>> &&);

    void insert(const tuple<Key...> &);
    void insert(tuple<Key...> &&);
    KdTree<Key...> *search(const tuple<Key...> &);

    private:
    void insert(const vector<tuple<Key...>> &, int);
    void insert(vector<tuple<Key...>> &&, int);

  private:
    int dimensions;
    int level_dimension;
    bool mark_delete;
};

template <class... Key>
int KdTree<Key...>::depth() const
{
    if (!*this)
    {
        return -1;
    }
    return max((*this)->left.depth(), (*this)->right.depth()) + 1;
}

template <class... Key>
int KdTree<Key...>::size() const
{
    if (!*this)
    {
        return 0;
    }
    return (*this)->left.size() + (*this)->right.size() + 1;
}

template <class... Key>
tuple<tuple<Key...>, vector<tuple<Key...>>, vector<tuple<Key...>>> split(vector<tuple<Key...>> &&vec, const int &dimension)
{
    sort(begin(vec), end(vec), [&dimension](auto const &t1, auto const &t2) {
        // TERRIBLE HACK THAT ESSENTIALLY LIMITS THE TUPLES TO 4 DIMENSIONS MAX
        // but it's the only way, because get<> uses template arguments, which need to be known at compile time
        // so you can't write a variable in the <>
        // solutions do exist, but only if you intend to loop through the entire tuple
        switch (dimension)
        {
        case 0:
            return std::get<0>(t1) < std::get<0>(t2);
            break;
        case 1:
            return std::get<1>(t1) < std::get<1>(t2);
            break;
        case 2:
            return std::get<2>(t1) < std::get<2>(t2);
            break;
        case 3:
            return std::get<3>(t1) < std::get<3>(t2);
            break;
        default:
            return std::get<0>(t1) < std::get<0>(t2);
            break;
        }
    });
    int median_index = floor(vec.size() / 2.0);
    return std::make_tuple<tuple<Key...>, vector<tuple<Key...>>, vector<tuple<Key...>>>(tuple<Key...>(move(vec[median_index])), vector<tuple<Key...>>(vec.begin(), vec.begin() + median_index), vector<tuple<Key...>>(vec.begin() + median_index + 1, vec.end()));
}

template <class... Key>
void KdTree<Key...>::insert(vector<tuple<Key...>> &&data, int dim)
{    
    this->level_dimension = dim % dimensions;
    auto [median, left_part, right_part] = move(split(move(data), dim % dimensions));

    (*this)->dimension_keys = move(median);
    if (left_part.size() > 0)
    {
        (*this)->left = KdTree<Key...>(dimensions);
        (*this)->left.level_dimension = (dim + 1) % dimensions;
        (*this)->left.insert(move(left_part), dim + 1);
    }
    if (right_part.size() > 0)
    {
        (*this)->right = KdTree<Key...>(dimensions);
        (*this)->right.level_dimension = (dim + 1) % dimensions;
        (*this)->right.insert(move(right_part), dim + 1);
    }
}

template <class... Key>
void KdTree<Key...>::insert(vector<tuple<Key...>> &&data)
{       
    KdTree<Key...> *location = search(data[0]);
    int dim = location->level_dimension;
    location->level_dimension = dim % dimensions;

    auto [median, left_part, right_part] = move(split(move(data), dim % dimensions));

    (*location)->dimension_keys = move(median);
    if (left_part.size() > 0)
    {
        (*location)->left = KdTree<Key...>(dimensions);
        (*location)->left.level_dimension = (dim + 1) % dimensions;
        (*location)->left.insert(move(left_part), dim + 1);
    }
    if (right_part.size() > 0)
    {
        (*location)->right = KdTree<Key...>(dimensions);
        (*location)->right.level_dimension = (dim + 1) % dimensions;
        (*location)->right.insert(move(right_part), dim + 1);
    }
}

template <class... Key>
void KdTree<Key...>::insert(tuple<Key...> &&to_insert)
{
    KdTree<Key...> *location = search(to_insert);
    int dim = location->level_dimension;
    location->level_dimension = dim % dimensions;
    (*location)->dimension_keys = move(to_insert);
    (*location)->left = KdTree<Key...>(dimensions);
    (*location)->left.level_dimension = dim + 1 % dimensions;
    (*location)->right = KdTree<Key...>(dimensions);
    (*location)->right.level_dimension = dim + 1 % dimensions;
}

template <class... Key>
KdTree<Key...> *KdTree<Key...>::search(const tuple<Key...> &searched_keys)
{
    if (!*this)
    {
        return nullptr;
    }
    KdTree<Key...> tx(dimensions);
    if ((*this)->dimension_keys == tx->dimension_keys && !(*this)->left && !(*this)->right)
    {
        return this;
    }
    else if ((*this)->dimension_keys == searched_keys)
    {
        return this;
    }
    switch (this->level_dimension)
    {
    case 0:
    {
        bool smaller = std::get<0>(searched_keys) < std::get<0>((*this)->dimension_keys);
        if (smaller)
        {
            return (*this)->left.search(searched_keys);
        }
        else
        {
            return (*this)->right.search(searched_keys);
        }
        break;
    }
    case 1:
    {
        bool smaller = std::get<1>(searched_keys) < std::get<1>((*this)->dimension_keys);
        if (smaller)
        {
            return (*this)->left.search(searched_keys);
        }
        else
        {
            return (*this)->right.search(searched_keys);
        }

        break;
    }
    case 2:
    {
        bool smaller = std::get<2>(searched_keys) < std::get<2>((*this)->dimension_keys);
        if (smaller)
        {
            return (*this)->left.search(searched_keys);
        }
        else
        {
            return (*this)->right.search(searched_keys);
        }

        break;
    }

    case 3:
    {

        bool smaller = std::get<3>(searched_keys) < std::get<3>((*this)->dimension_keys);
        if (smaller)
        {
            return (*this)->left.search(searched_keys);
        }
        else
        {
            return (*this)->right.search(searched_keys);
        }

        break;
    }

    default:
    {
        bool smaller = std::get<0>(searched_keys) < std::get<0>((*this)->dimension_keys);
        if (smaller)
        {
            return (*this)->left.search(searched_keys);
        }
        else
        {
            return (*this)->right.search(searched_keys);
        }

        break;
    }
    }
}

#endif