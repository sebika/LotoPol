#ifndef _TREE
#define _TREE

#include <bits/stdc++.h>
#include "constants.hpp"
#include "utils.hpp"
using namespace std;

// Represents a node of an n-ary tree
struct Node
{
   int key;
   int value;
   vector<Node *>children;
};


Node* createTree(const vector<vector<int>> &draws, int k);
Node* updateTree(const vector<vector<int>> &draws, int k, Node *root, int number_of_draws);
int find_delay(Node *root, const vector<int> &numbers);
void serialize_tree_to_file(Node *root, const char *filename, int offset);
Node* deSerialize_tree_from_file(const char *filename);

#endif
