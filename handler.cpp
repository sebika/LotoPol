#include "include/handler.hpp"

void handleCreate(int argc, char** argv, const vector<vector<int>> &draws)
{
    /*
        Command: `make createTree`

        If you want to build the tree from scratch
        By default the height of the tree should be [5]
        (for depth [6] you need more the 16Gb of memory)
    */
    if (argc == 2 && strncmp(argv[1], "create", 6) == 0) {
        char output_file[20];
        strcpy(output_file, "output/tree");

        for (int depth = 1; depth <= 5; ++depth) {
            Node *root = createTree(draws, depth);
            output_file[11] = depth + 48;
            output_file[12] = 0;
            serialize_tree_to_file(root, output_file, 0);
            cout << " + Tree" << depth << " created successfully\n";
        }

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
    if (argc == 2 && strncmp(argv[1], "update", 6) == 0) {
        cout << "\n=========\nINFO: Reading input/update file\n";
        vector<vector<int>> new_draws = readDatabase("input/update");

        updateDatabase("input/database", new_draws, draws);
        int number_of_draws = new_draws.size();
        draws = readDatabase("input/database");

        char file[20];
        strcpy(file, "output/tree");
        strcpy(file, "output/tree");
        for (int depth = 1; depth <= 5; ++depth) {
            file[11] = depth + 48;
            file[12] = 0;
            Node *root = deSerialize_tree_from_file(file);
            root = updateTree(draws, depth, root, number_of_draws);
            serialize_tree_to_file(root, file, number_of_draws);
            cout << " + Tree" << depth << " updated successfully\n";

        }
        exit(EXIT_SUCCESS);
    }
    else
        cout << " - Skipping tree update\n";
}
