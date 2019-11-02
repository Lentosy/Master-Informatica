#ifndef __LINEAR_HASHING_HPP
#define __LINEAR_HASHING_HPP

#include <vector>
using std::vector;
#include <functional>
using std::hash;
#include <utility>
using std::move;
#include <cmath>
using std::pow;
#include <unordered_map>
using std::unordered_map;

const int BUCKET_SIZE = 2;

template <class Key, class Data>
class Bucket;

template <class Key, class Data>
class LinearHashTable;

template <class Key, class Data>
class Bucket
{
    friend class LinearHashTable<Key, Data>;

  public:
    Bucket()
    {
        m = 0;
        mapping.reserve(BUCKET_SIZE);
    };
    virtual ~Bucket() = default;
    Bucket(const Bucket<Key, Data> &) = default;
    Bucket<Key, Data> &operator=(const Bucket<Key, Data> &) = default;
    Bucket(Bucket<Key, Data> &&) = default;
    Bucket<Key, Data> &operator=(Bucket<Key, Data> &&) = default;

    const Data *getData(const Key &key)
    {
        auto p = mapping.find(key);
        if (p != mapping.end())
        {
            return &p->second;
        }
        else
            return nullptr;
    }

    bool full() const
    {
        return mapping.size() + overflow_mapping.size() >= BUCKET_SIZE;
    }

    void insert(const Key &key, const Data &data)
    {
        if (mapping.size() < BUCKET_SIZE)
        {
            mapping.insert({key, data});
        }
        else
        {
            overflow_mapping.insert({key, data});
        }
        m++;
    }

    void erase(const Key &key)
    {
        if (mapping.erase(key) == 0)
        {
            overflow_mapping.erase(key);
        }
        m--;
    }

  private:
    int m;
    // These underlying data structures are not according to the specification, which requires a sorted list, needs rework
    // to be compliant.
    unordered_map<Key, Data> mapping;
    // my overflow mapping is unbounded, this is not in accordance with the definition or with an implementation for hard drives
    unordered_map<Key, Data> overflow_mapping;
};

template <class Key, class Data>
class LinearHashTable
{
  public:
    LinearHashTable() = default;
    virtual ~LinearHashTable() = default;
    LinearHashTable(const LinearHashTable<Key, Data> &) = default;
    LinearHashTable<Key, Data> &operator=(const LinearHashTable<Key, Data> &) = default;
    LinearHashTable(LinearHashTable<Key, Data> &&) = default;
    LinearHashTable<Key, Data> &operator=(LinearHashTable<Key, Data> &&) = default;
    LinearHashTable(double _split_ratio, int _initial_bucket_nr) : initial_bucket_nr{_initial_bucket_nr}, split_ratio{_split_ratio}
    {
        step_pointer = 0;
        current_level = 0;
        buckets = vector<Bucket<Key, Data>>(initial_bucket_nr);
    }

    void insert(const Key &, const Data &);
    int search(const Key &);

  private:
    vector<Bucket<Key, Data>> buckets;
    int step_pointer;
    int current_level;
    int initial_bucket_nr;
    double split_ratio;
};

template <class Key, class Data>
int LinearHashTable<Key, Data>::search(const Key &key)
{
    hash<Key> hash_functor;
    int index;
    size_t hashed_value = hash_functor(key);
    if (hashed_value % (unsigned int)(initial_bucket_nr * pow(2, current_level)) < step_pointer)
    {
        index = hashed_value % (unsigned int)(initial_bucket_nr * pow(2, current_level + 1));
    }
    else
    {
        index = hashed_value % (unsigned int)(initial_bucket_nr * pow(2, current_level));
    }
    return index;
}

template <class Key, class Data>
void LinearHashTable<Key, Data>::insert(const Key &key, const Data &data)
{
    int index = search(key);

    if (buckets[index].full())
    {
        buckets.push_back(Bucket<Key, Data>());
        for (auto &pair : buckets[step_pointer].mapping)
        {
            int idx = search(pair.first);
            if (idx != step_pointer)
            {
                buckets[idx].insert(pair.first, pair.second);
                buckets[step_pointer].erase(pair.first);
            }
        }
        for (auto &pair : buckets[step_pointer].overflow_mapping)
        {
            int idx = search(pair.first);
            if (idx != step_pointer)
            {
                buckets[idx].insert(pair.first, pair.second);
                buckets[step_pointer].erase(pair.first);
            }
        }
        buckets[index].insert(key, data);

        if (step_pointer == (initial_bucket_nr * pow(2, current_level) - 1))
        {
            step_pointer = 0;
            current_level++;
        }
        else
        {
            step_pointer++;
        }
    }
    else
    {
        buckets[index].insert(key, data);
    }
}

#endif
