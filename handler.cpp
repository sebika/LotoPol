#include "include/handler.hpp"

void handleCreate(int argc, char** argv, const vector<vector<int>> &draws)
{
    /*
        Command: `make createTree`

        If you want to build the tree from scratch
        By default the height of the tree should be [5]
        (for depth [6] you need more the 16Gb of memory)
    */
    if (argc == 3 && strncmp(argv[1], "create", 6) == 0) {
        Node *root = createTree(draws, atoi(argv[2]));
        serialize_tree_to_file(root, "output/tree", 0);
        cout << " + Tree created successfully\n";
        exit(EXIT_SUCCESS);
    }
    else
        cout << "\n - Skipping tree create\n";

}

void handleUpdate(int argc, char** argv, vector<vector<int>> &draws)
{
    /*
        Command: `make updateTree`

        Updates the existing tree by `number_of_draws` lines
        from database
    */
    if (argc == 3 && strncmp(argv[1], "update", 6) == 0) {
        cout << "\n=========\nINFO: Reading input/update file\n";
        vector<vector<int>> new_draws = readDatabase("input/update");

        updateDatabase("input/database", new_draws, draws);
        int number_of_draws = new_draws.size();
        draws = readDatabase("input/database");

        Node *root = deSerialize_tree_from_file("output/tree");
        root = updateTree(draws, atoi(argv[2]), root, number_of_draws);
        serialize_tree_to_file(root, "output/tree", number_of_draws);
        cout << " + Tree updated successfully\n";
        exit(EXIT_SUCCESS);
    }
    else
        cout << " - Skipping tree update\n";
}
