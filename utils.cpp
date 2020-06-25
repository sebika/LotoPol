#include "include/utils.hpp"

/*
    Updates the corresponding file

    Generate all combinations of NUMBERS_PER_DRAW taken `k` to find
    all delays for every set of numbers that were in atleast one draw.
*/
void updateDatabaseInfo(vector<vector<int>> draws, int k) {

    vector<bool> v(NUMBERS_PER_DRAW);
    vector<vector<int>> combinations;
    Map delays;
    Map::iterator it;

    string output_filename = "delays/" + to_string(k) + ':' + to_string(k);
    ofstream out;
    out.open(output_filename.c_str());

    fill(v.begin(), v.begin()+k, true);
    do {
        // Generate the combination and save the result in `combinations`
        vector<int> indices;
        for (int i = 0; i < NUMBERS_PER_DRAW; ++i)
            if (v[i]) {
                indices.push_back(i);
            }
        combinations.push_back(indices);
    } while (prev_permutation(v.begin(), v.end()));

    // Iterate through the draws and get the delays
    int number_of_draws = draws.size();
    for (int i = 0; i < number_of_draws; ++i) {
        int no_comb = combinations.size();
        for (int current_comb = 0; current_comb < no_comb; ++current_comb) {
            /* 
                Compute the key for the map
                Every number has 2 digits (for memory purposes)
                The key has the following format:
                    Eg: for the numbers 01 13 15 17 -> key = "01131517"
            */
            char* key = (char *)malloc(sizeof(char)*k*2);
            int key_len = 0;
            for (int j = 0; j < k; ++j) {
                int chosen_number = draws[i][combinations[current_comb][j]];
                // First digit
                key[key_len++] = chosen_number / 10 + 48;
                // Second digit
                key[key_len++] = chosen_number % 10 + 48;
            }
            // Add terminator at the end of the string
            key[key_len] = 0;

            // Update the map if the current key doesn't exist
            auto it = delays.find(key);
            if (it == delays.end()) {
                delays[key] = i;
                out << key << " " << i << endl;
            }
            else
                free(key);
        }
    }
}

vector<vector<int>> readDatabase(const char* filename) {
    vector<vector<int>> draws;
    ifstream fin;
    fin.open(filename);
    if (!fin) {
        cout << "Unable to open file"<< endl;
        fin.close();
        exit(1);
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