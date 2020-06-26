#include "include/utils.hpp"

vector<vector<int>> readDatabase(const char* filename) {
    vector<vector<int>> draws;
    ifstream fin;
    fin.open(filename);
    if (!fin) {
        perror("\n=== Cannot open the requested file ===\n");
    }
    else {
        int number;
        while (fin >> number) {
            vector<int> row;
            row.push_back(number);
            for (int i = 0; i < NUMBERS_PER_DRAW-1; ++i) {
                fin >> number;
                row.push_back(number);
            }
            draws.push_back(row);
        }
    }
    fin.close();
    return draws;
}
