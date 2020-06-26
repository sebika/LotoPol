#ifndef _UTILS
#define _UTILS

#include <bits/stdc++.h>
#include "constants.hpp"
using namespace std;

vector<vector<int>> readDatabase(const char* filename);
void updateDatabase(const char* filename,
                    const vector<vector<int>> &new_draws,
                    const vector<vector<int>> &old_draws);

#endif
