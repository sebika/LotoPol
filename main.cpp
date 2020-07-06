#include "include/constants.hpp"
#include "include/utils.hpp"
#include "include/tree.hpp"
#include "include/handler.hpp"
#include "include/randutils.hpp"

randutils::mt19937_rng rng;

using namespace std;
int main(int argc, char** argv) {

    //mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    // Read info from database
    vector<vector<int>> draws;
    draws = readDatabase("input/database");

    // Handle different args
    handleCreate(argc, argv, draws);
    handleUpdate(argc, argv, draws);

    // Get the input from the user
    int total_numbers, at_least;
    readInput(&total_numbers, &at_least);

    // The depth of the tree needs to be equal to `at_least` variable
    char input_file[20];
    strcpy(input_file, "output/tree");
    input_file[11] = at_least + 48;
    input_file[12] = 0;
    // Fetch the n-ary tree
    Node *root = deSerialize_tree_from_file(input_file);

    // Generate the required combinations
    vector<vector<int>> combinations = generateCombinations(total_numbers, at_least);
    int no_combinations = combinations.size();

    vector<int> numbers(total_numbers, -1);
    vector<int> chosen_numbers(at_least, -1);
    int chosen_number_size;

    int best_delay = -1;
    while (1) {
        // Find possible candidates
        numbers = generateNumbers(total_numbers);

        int min_delay = BIG_DELAY;
        for (int comb = 0; comb < no_combinations; ++comb) {
            chosen_number_size = 0;
            for (int i = 0; i < at_least; ++i)
                chosen_numbers[chosen_number_size++] = numbers[combinations[comb][i]];

            int delay = find_delay(root, chosen_numbers);

            min_delay = (min_delay < delay) ? min_delay : delay;
            if (min_delay < best_delay) break;
        }

        // Find the numbers with the biggest delay
        if (best_delay < min_delay) {
            best_delay = min_delay;
            cout << best_delay << " -> ";
            printVect(numbers);
        }
    }

    return 0;
}
