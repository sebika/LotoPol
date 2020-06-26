#include "include/constants.hpp"
#include "include/utils.hpp"
#include "include/tree.hpp"

using namespace std;
int main() {

    vector<vector<int>> draws;
    draws = readDatabase("input/database");

    Node *root = createTreeFromDatabase(draws, 5);
    serialize_tree_to_file(root, "output/tree");

    root = NULL;
    deSerialize_tree_from_file(root, "output/tree");
    cout << find_delay(root, {04,55,58}) << endl;

    return 0;
}
