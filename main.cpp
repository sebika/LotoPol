#include "include/constants.hpp"
#include "include/utils.hpp"
#include "include/tree.hpp"
#include "include/handler.hpp"

using namespace std;
int main(int argc, char** argv) {

    vector<vector<int>> draws;
    draws = readDatabase("input/database");

    handleCreate(argc, argv, draws);
    handleUpdate(argc, argv, draws);

    Node *root = deSerialize_tree_from_file("output/tree");
    cout << find_delay(root, {04,55,58}) << endl;
    cout << find_delay(root, {1, 4, 5}) << endl;

    return 0;
}
