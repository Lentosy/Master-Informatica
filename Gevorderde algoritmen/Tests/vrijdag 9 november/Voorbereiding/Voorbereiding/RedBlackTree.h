#pragma once

#include "BinarySearchTree.h"

/*
*
* Class RedBlackTree
*
* A red black tree. This is a self balancing binary search tree with the following properties:
*   1) A node can have one of two colors, red or black
*   2) The root node is always black
*   3) A red node can not have a red child, out of this property follows:
*   4) A red node always has two black children.
*   5) A null leaf (called virtual node) is black
*   6) The black depth from any given node is the same for all the paths from that node to every leaf.
*   7) A subtree is minimal half as deep as the other subtree.
*
*   The height of a red black tree is always O(lg n).
*
*/

template <typename Priority, typename Value>
class RedBlackTree : BinarySearchTree<Priority, Value> {

};