#include "include/constants.hpp"
#include "include/utils.hpp"

using namespace std;
int main() {

    vector<vector<int>> draws;
    draws = readDatabase("database");

    int k;
    char response[10];
    cout << "-> k = ";
    cin >> k;
    cout << "===== You want to update delays/" << k << ":" << k << " file? =====  [yes/no]: ";
    cin >> response;

    if (strncmp(response, "yes", 3) == 0) {
        updateDatabaseInfo(draws, k);
        cout << "===== File delays/" << k << ":" << k << " updated =====\n";
    }    

    return 0;
}