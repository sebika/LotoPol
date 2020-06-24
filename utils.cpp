#include "include/utils.hpp"

/*
    Find how for how many draws 1 number, 2 numbers,
    3 numbers, 4 numbers and 5 numbers didn't show up
    together in a single draw.
*/
void getDatabaseInfo(vector<vector<int>> draws) {
    int nr = 0;
    for (int k = 1; k <= 5; ++k) {
        vector<bool> v(MAX_NUMBER);
        fill(v.begin(), v.begin()+k, true);

        do {
            nr ++;
        } while (prev_permutation(v.begin(), v.end()));
    }
    cout << nr << endl;
}