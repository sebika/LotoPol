#include "include/utils.hpp"


Node *newNode(int key);
bool cmp_nodes(Node *a, Node *b);
int find_delay(Node *root, vector<int> numbers);


/*
    Generate all combinations of NUMBERS_PER_DRAW taken `k` to find
    all delays for every set of numbers that were in atleast one draw.
*/
void updateDatabaseInfo(vector<vector<int>> draws, int k) {
    vector<bool> v(NUMBERS_PER_DRAW);
    vector<vector<int>> combinations;
    Node *root = newNode(EMPTY);

    string output_filename = "delays/" + to_string(k) + ':' + to_string(k);
    ofstream out;
    out.open(output_filename.c_str());

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

    // Iterate through the draws and get the delays
    int number_of_draws = draws.size();
    for (int i = 0; i < number_of_draws; ++i) {
        int no_comb = combinations.size();
        if (i % 1000 == 0) cout << i << endl;

        for (int current_comb = 0; current_comb < no_comb; ++current_comb) {
            // The current node
            Node *current_node = root;
            for (int j = 0; j < k; ++j) {
                int current_number = draws[i][combinations[current_comb][j]];

                // Find the current number through the children of the current_node
                int found = -1;
                int no_children = current_node->children.size();
                for (int child = 0; child < no_children; ++child) {
                    if (current_node->children[child]->key == current_number) {
                        found = child;
                        break;
                    }
                }

                if (found == -1) {
                    // Insert the key if it is not found
                    Node *new_node = newNode(current_number);
                    current_node->children.push_back(new_node);
                    current_node = new_node;
                }
                else {
                    // Insert the key if it is not found
                    current_node = current_node->children[found];
                }

                // Update the delay if that is the case
                current_node->delay = (current_node->delay < i) ? current_node->delay : i;
            }
        }
    }

    cout << find_delay(root, {34,58,63,75}) << endl;
}

bool cmp_nodes(Node *a, Node *b)
{
   return (a->key < b->key);
}

// Utility function to create a new tree node 
Node *newNode(int key) 
{ 
   Node *temp = new Node;
   temp->key = key;
   temp->delay = BIG_DELAY;
   return temp;
}

int find_delay(Node *root, vector<int> numbers) {
    int n = numbers.size();
    Node* current_node = root;
    for (int i = 0; i < n; ++i) {
        bool found = 0;
        int no_children = current_node->children.size();
        for (int j = 0; j < no_children; ++j) {
            if (current_node->children[j]->key == numbers[i]) {
                found = true;
                current_node = current_node->children[j];
                break;
            }
        }
        if(!found)
            return -1;
    }
    return current_node->delay;
}

vector<vector<int>> readDatabase(const char* filename) {
    vector<vector<int>> draws;
    ifstream fin;
    fin.open(filename);
    if (!fin) {
        cout << "Unable to open file"<< endl;
        fin.close();
        exit(1);
    }
    else {
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
    }
    fin.close();
    return draws;
}