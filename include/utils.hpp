#ifndef _UTILS
#define _UTILS

#include <bits/stdc++.h>
#include "constants.hpp"
using namespace std;

struct cmp_str
{
   bool operator()(char *a, char *b) const
   {
      return strcmp(a, b) < 0;
   }
};

typedef map<char *, int, cmp_str> Map;

void updateDatabaseInfo(vector<vector<int>> draws, int k);
vector<vector<int>> readDatabase(const char* filename);


#endif