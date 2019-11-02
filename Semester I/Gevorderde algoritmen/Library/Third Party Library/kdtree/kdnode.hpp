#ifndef __KDNODE_HPP
#define __KDNODE_HPP

#include <tuple>
using std::tuple;
using std::tuple_cat;
#include <utility>
using std::move;

template <class... Key>
class KdNode
{
  friend class KdTree<Key...>;

public:
  KdNode() = default;  
  virtual ~KdNode() = default;
  KdNode(const KdNode<Key...> &) = default;
  KdNode<Key...> &operator=(const KdNode<Key...> &) = default;
  KdNode(KdNode<Key...> &&) = default;
  KdNode<Key...> &operator=(KdNode<Key...> &&) = default;
  KdNode(const tuple<Key...> &keys) : dimension_keys{keys} {}
  KdNode(tuple<Key...> &&keys) : dimension_keys{move(keys)} {}

private:
  tuple<Key...> dimension_keys;
  KdTree<Key...> left;
  KdTree<Key...> right;
};

#endif
