#ifndef _UTILS
#define _UTILS

#include <bits/stdc++.h>
#include "constants.hpp"
using namespace std;

// Represents a node of an n-ary tree 
struct Node 
{ 
   int key;
   int delay;
   vector<Node *>children;
};

void updateDatabaseInfo(vector<vector<int>> draws, int k);
vector<vector<int>> readDatabase(const char* filename);


#endif