#include "include/tree.hpp"

/*
    Utility function to create a new tree node

    @param: key represents the number
    @param: val represents the value stored in the number
*/
Node *newNode(int key, int value)
{
   Node *temp = new Node;
   temp->key = key;
   temp->value = value;
   return temp;
}

/*
    Generate all combinations of NUMBERS_PER_DRAW taken `k` to find
    all delays for every set of numbers that were in atleast one draw.

    @param: the draws from the database
    @param: depth of the tree
    @return: the root of the tree
*/
Node* createTreeFromDatabase(const vector<vector<int>> &draws, int k)
{
    vector<bool> v(NUMBERS_PER_DRAW);
    vector<vector<int>> combinations;
    Node *root = newNode(EMPTY, BIG_DELAY);

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

    cout << "\n=========\nINFO: Generating tree from database with depth: [" << k << "]\n";

    // Iterate through the draws and get the delays
    int number_of_draws = draws.size();
    for (int i = 0; i < number_of_draws; ++i) {

        if (i % 1000 == 0 && i > 0) {
            cout << " -> Done " << i << " lines\n";
        }

        int no_comb = combinations.size();
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
                    Node *new_node = newNode(current_number, BIG_DELAY);
                    current_node->children.push_back(new_node);
                    current_node = new_node;
                }
                else {
                    // Insert the key if it is not found
                    current_node = current_node->children[found];
                }

                // Update the delay if that is the case
                current_node->value = (current_node->value < i) ? current_node->value : i;
            }
        }
    }
    return root;
}

/*
    Finds the delay for a combination of numbers.
    Eg: find_delay(root, {4, 55, 58})

    @param: the root of the tree
    @param: a vector containing the desired numbers
    @return: the delay
*/
int find_delay(Node *root, const vector<int> &numbers)
{
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
    return current_node->value;
}

/*
    This function stores the given N-ary tree in a file pointed by fp

    @param: the root of the tree
    @param: the file pointer
*/
void serialize(Node *root, FILE *fp)
{
    // Base case
    if (root == NULL)
        return;


    // Else, store current node and recur for its children
    int no_children = root->children.size();
    fprintf(fp, "%d %d ", root->key, root->value);
    for (int i = 0; i < no_children; i++)
        serialize(root->children[i],  fp);

    // Store marker at the end of children
    fprintf(fp, "%d ", MARKER);
}

/*
    This is a wrapper for `serialize` function

    @param: the root of the tree
    @param: the file pointer
*/
void serialize_tree_to_file(Node *root, const char *filename)
{
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL) perror("CRITICAL: Error opening the file or creating it\n");
    else {
        cout << "\n=========\nINFO: Serializing the tree to: " << filename << endl;
        serialize(root, fp);
        cout << "INFO: Done!\nINFO: Closing the file\n=========\n";
        fclose(fp);
    }
}

/*
    This function constructs N-ary tree from a file pointed by `fp`.

    @param: the root where the tree will be saved
    @param: the file pointer
*/
void deSerialize(Node *&root, FILE *fp)
{
    int stack_capacity = 1000, stack_size = 0;
    Node *stack[stack_capacity];
    for (int i = 0; i < stack_capacity; ++i)
        stack[i] = NULL;

    int key, val;
    if (fscanf(fp, "%d %d ", &key, &val) == 2) {
        root = newNode(key, val);
        while(fscanf(fp, "%d ", &key) == 1) {
            if (key == MARKER) {
                Node *childNode = stack[--stack_size];
                if (stack_size > 0) {
                    Node *parentNode = stack[stack_size-1];
                    parentNode->children.push_back(childNode);
                }
                else {
                    root->children.push_back(childNode);
                }
            }
            else {
                if (fscanf(fp, "%d ", &val) == 1)
                    stack[stack_size++] = newNode(key, val);
                else
                    perror("CRITICAL: Something went wrong while parsing the file\n");
            }
        }
    }
    else {
        perror("CRITICAL: Something went wrong while parsing the file\n");
    }
}

/*
    This is a wrapper for `deSerialize` function

    @param: the root where the tree will be saved
    @param: the file pointer
*/
void deSerialize_tree_from_file(Node *&root, const char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) perror("CRITICAL: Error opening the file\n");
    else {
        cout << "\n=========\nINFO: Deserializing the tree\n";
        deSerialize(root, fp);
        cout << "INFO: Done!\nINFO: Closing the file\n=========\n";
        fclose(fp);
    }
}
