#include "include/constants.hpp"
#include "include/utils.hpp"
#include "include/tree.hpp"
#include <unistd.h>

using namespace std;
int main(int argc, char** argv) {

    vector<vector<int>> draws;
    draws = readDatabase("input/database");

    /*
        Command: `make createTree`

        If you want to build the tree from scratch
        By default the height of the tree should be [5]
        (for depth [6] you need more the 16Gb of memory)
    */
    if (argc == 3 && strncmp(argv[1], "create", 6) == 0) {
        Node *root = createTree(draws, atoi(argv[2]));
        serialize_tree_to_file(root, "output/tree", 0);
        return 0;
    }

    /*
        Command: `make updateTree`

        Updates the existing tree by `number_of_draws` lines
        from database
    */
    if (argc == 3 && strncmp(argv[1], "update", 6) == 0) {
        int number_of_draws;
        cout << " -> How many lines you want to update from database?\n -> ";
        cin >> number_of_draws;
        Node *root = deSerialize_tree_from_file("output/tree");
        root = updateTree(draws, atoi(argv[2]), root, number_of_draws);
        serialize_tree_to_file(root, "output/tree", number_of_draws);
        return 0;
    }

    Node *root = deSerialize_tree_from_file("output/tree");
    cout << find_delay(root, {04,55,58}) << endl;
    cout << find_delay(root, {1, 4, 5}) << endl;

    return 0;
}
