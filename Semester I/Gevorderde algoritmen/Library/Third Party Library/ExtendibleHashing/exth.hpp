#ifndef __EXTH_HPP
#define __EXTH_HPP

#include <unordered_map>
using std::unordered_map;
#include <vector>
using std::vector;
#include <functional>
using std::hash;
#include <cmath>
using std::pow;
#include <utility>
using std::move;

const int BUCKET_SIZE = 1;

template <class Key, class Data>
class Bucket;

template <class Key, class Data>
class ExtendibleHashTable;

template <class Key, class Data>
class Bucket
{

    friend class ExtendibleHashTable<Key, Data>;

  public:
    Bucket() : local_depth{1} { mapping.reserve(BUCKET_SIZE); };
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
        return mapping.size() == BUCKET_SIZE;
    }

    void insert(const Key &key, const Data &data)
    {
        mapping.insert({key, data});
    }

    void erase(const Key &key)
    {
        mapping.erase(key);
    }

  private:
    int local_depth;
    unordered_map<Key, Data> mapping;
};

template <class Key, class Data>
class ExtendibleHashTable
{
  public:
    ExtendibleHashTable() = default;
    virtual ~ExtendibleHashTable() = default;
    ExtendibleHashTable(const ExtendibleHashTable<Key, Data> &) = default;
    ExtendibleHashTable<Key, Data> &operator=(const ExtendibleHashTable<Key, Data> &) = default;
    ExtendibleHashTable(ExtendibleHashTable<Key, Data> &&) = default;
    ExtendibleHashTable<Key, Data> &operator=(ExtendibleHashTable<Key, Data> &&) = default;
    ExtendibleHashTable(int _global_depth) : global_depth{_global_depth}
    {
        int reserve = 1;
        for (int i = 1; i <= global_depth; i++)
        {
            reserve = 2 * reserve;
        }
        buckets = vector<Bucket<Key, Data>>(reserve);
    }

    void insert(const Key &, const Data &);
    void remove(const Key &);
    Bucket<Key, Data> search(int);
    int get_index(const Key &);

  private:
    int global_depth;
    vector<Bucket<Key, Data>> buckets;
};

template <class Key, class Data>
void ExtendibleHashTable<Key, Data>::insert(const Key &key, const Data &data)
{
    int bucket_index = get_index(key);
    Bucket<Key, Data> bucket = move(search(bucket_index));
    if (bucket.full() && bucket.local_depth == global_depth)
    {
        // insidious bug, if you resize then the pointer to the found bucket may no longer be valid. //buckets.resize(buckets.capacity() * 2);
        int buckets_to_add = buckets.size();
        for (int i = 0; i < buckets_to_add; i++)
        {
            buckets.push_back(Bucket<Key, Data>());
        }
        global_depth += 1;
    }
    if (bucket.full() && bucket.local_depth < global_depth)
    {
        bucket.insert(key, data);
        Bucket<Key, Data> b1;
        Bucket<Key, Data> b2;
        hash<Key> hash_functor;
        for (auto &pair : bucket.mapping)
        {
            size_t hashed_key = hash_functor(pair.first);
            hashed_key = hashed_key & ((1 << global_depth) - 1);
            if ((hashed_key >> bucket.local_depth) & 1 == 1)
            {
                b1.insert(pair.first, pair.second);
            }
            else
            {
                b2.insert(pair.first, pair.second);
            }
        }
        b1.local_depth = bucket.local_depth + 1;
        b2.local_depth = bucket.local_depth + 1;
        if ((bucket_index >> bucket.local_depth) & 1 == 1)
        {
            buckets[bucket_index] = move(b1);
        }
        else
        {
            buckets[bucket_index] = move(b2);
        }
        size_t next_index = bucket_index + pow(2, global_depth - 1);
        if ((next_index >> bucket.local_depth & 1) == 1)
        {
            buckets[bucket_index + pow(2, global_depth - 1)] = move(b1);
        }
        else
        {
            buckets[bucket_index + pow(2, global_depth - 1)] = move(b2);
        }
    }
    else
    {
        bucket.insert(key, data);
        buckets[bucket_index] = move(bucket);
    }
}

template <class Key, class Data>
void ExtendibleHashTable<Key, Data>::remove(const Key &key)
{
}

template <class Key, class Data>
Bucket<Key, Data> ExtendibleHashTable<Key, Data>::search(int index)
{
    return buckets[index];
}

template <class Key, class Data>
int ExtendibleHashTable<Key, Data>::get_index(const Key &key)
{
    hash<Key> hash_functor;
    size_t hashed_key = hash_functor(key);
    // build a sequence of all 1s 1<<global_depth shifts 1 to the left and inserts 0s, so you subtract 1 at the end
    // then bitwise and will keep the number of bits indicated by the mask
    return hashed_key & ((1 << global_depth) - 1);
}

#endif