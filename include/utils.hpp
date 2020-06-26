#ifndef _UTILS
#define _UTILS

#include <bits/stdc++.h>
#include "constants.hpp"
using namespace std;

vector<vector<int>> readDatabase(const char* filename);
void updateDatabase(const char* filename,
                    const vector<vector<int>> &new_draws,
                    const vector<vector<int>> &old_draws);
int readInt(const char *prompt);
void readInput(int *total_numbers, int *at_least);
vector<vector<int>> generateCombinations(const int n, const int k);
vector<int> generateNumbers(int howMany);
void printVect(const vector<int> &vect);

#endif
