#include "include/utils.hpp"
#include "include/randutils.hpp"

extern randutils::mt19937_rng rng;

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

/*
    Reads a 2 digit number
    @param: display the prompt before you read
    @return: the number
*/
int readInt(const char *prompt) {
    char buf[100];
    cout << " -> " << prompt;
    while(1) {
        cin >> buf;
        if(strlen(buf) == 1 && buf[0] > '0' && buf[0] <= '9')
            return buf[0]-48;
        if(strlen(buf) == 2 &&
          buf[0] >= '0' && buf[0] <= '9' &&
          buf[1] >= '0' && buf[1] <= '9')
            return (buf[0]-48)*10 + buf[1]-48;
        cout << " ! Please enter a 2 digit number. (preferred <= 10)\n -> " << prompt;
    }
}


/*
    Reads the desired input and stores the result
    in the parameters
*/
void readInput(int *total_numbers, int *at_least) {
    cout << "Enter a 2 digit number. (preferred <= 10)\n";
    (*total_numbers) = readInt("total_numbers = ");
    (*at_least) = readInt("at_least = ");
    while ((*at_least) > (*total_numbers)) {
        cout << " ! at_least should be <= total_numbers\n";
        (*at_least) = readInt("at_least = ");
    }
}

vector<vector<int>> generateCombinations(const int n, const int k) {
    vector<bool> v(n);
    vector<vector<int>> combinations;

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
    return combinations;
}

/*
    Generate distinct pseudo-random numbers between 1 and MAX_NUMBER
    Numbers are generated in ascending order
    @param: howMany numbers you want to generate

*/
vector<int> generateNumbers(int howMany) {

    vector<int> numbers(howMany, 0);
    int size = 0;
    while (size < howMany) {
        int number = rng.uniform(1,MAX_NUMBER);
        bool different = true;
        for (int i = 0; i < size; ++i)
            if (numbers[i] == number) {
                different = false;
                break;
            }
        if (different)
            numbers[size++] = number;
    }
    sort(numbers.begin(), numbers.end());
    return numbers;
}

/*
    Prints a vector
*/
void printVect(const vector<int> &vect) {
    int n = vect.size();
    for (int i = 0; i < n; ++i)
        cout << vect[i] << " ";
    cout << endl;
}
