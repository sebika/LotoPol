#include "include/constants.hpp"
#include "include/reader.hpp"
#include "include/utils.hpp"

using namespace std;
int main() {

    vector<vector<int>> draws;
    draws = readDatabase("database");

    getDatabaseInfo(draws);

    return 0;
}