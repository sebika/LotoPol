#include "include/utils.hpp"

/*
    @param: the filename
*/
vector<vector<int>> readDatabase(const char* filename) {
    vector<vector<int>> draws;
    ifstream fin;
    fin.open(filename);
    if (!fin) {
        perror("CRITICAL: Cannot open the requested file\n");
    }
    else {
        cout << "\n=========\nINFO: Reading database\n";
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
        cout << "INFO: Done!\nINFO: Closing the file\n=========\n";
    }
    fin.close();
    return draws;
}

/*
    @param: the filename
    @param: new_draws that need to be appended at the beginning of the file
    @param: old_draws that existed in the file before the update
*/
void updateDatabase(const char* filename,
                    const vector<vector<int>> &new_draws,
                    const vector<vector<int>> &old_draws)
{
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL) perror("CRITICAL: Error opening the file or creating it\n");
    else {
        cout << "INFO: Updating input/database file\n";
        int n = new_draws.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < NUMBERS_PER_DRAW-1; ++j)
                fprintf(fp, "%d%d ", new_draws[i][j]/10, new_draws[i][j]%10);
            int last_number = new_draws[i][NUMBERS_PER_DRAW-1];
            fprintf(fp, "%d%d\n", last_number/10, last_number%10);
        }

        n = old_draws.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < NUMBERS_PER_DRAW-1; ++j)
                fprintf(fp, "%d%d ", old_draws[i][j]/10, old_draws[i][j]%10);
            int last_number = old_draws[i][NUMBERS_PER_DRAW-1];
            fprintf(fp, "%d%d\n", last_number/10, last_number%10);
        }
        cout << "INFO: Done. Closing file\n";
        fclose(fp);

        cout << "INFO: Removing contents of input/update file\n";
        ofstream ofs;
        ofs.open("input/update", std::ofstream::out | std::ofstream::trunc);
        ofs.close();
        cout << "INFO: Done. Closing file\n";
    }
}
