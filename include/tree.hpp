#ifndef _TREE
#define _TREE

#include <bits/stdc++.h>
#include "constants.hpp"
using namespace std;

// Represents a node of an n-ary tree
struct Node
{
   int key;
   int value;
   vector<Node *>children;
};

Node* createTreeFromDatabase(const vector<vector<int>> &draws, int k);
int find_delay(Node *root, const vector<int> &numbers);
void serialize_tree_to_file(Node *root, const char *filename);
void deSerialize_tree_from_file(Node *&root, const char *filename);

#endif
