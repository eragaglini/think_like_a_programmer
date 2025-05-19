#include <iostream>
#include <climits>
#include <algorithm>
// ...existing code...
using namespace std;

struct TreeNode
{
    int value;
    TreeNode *right, *left;

    explicit TreeNode(int val) : value(val),
                                 right(nullptr),
                                 left(nullptr) {};
};
typedef TreeNode *binaryTree;

bool is_bst_util(const binaryTree node, int min_val, int max_val)
{
    if (node == nullptr)
        return true;
    if (node->value <= min_val || node->value >= max_val)
        return false;
    return is_bst_util(node->left, min_val, node->value) &&
           is_bst_util(node->right, node->value, max_val);
}

bool is_binary_search_tree(const binaryTree node)
{
    return is_bst_util(node, INT_MIN, INT_MAX);
}

void insert(binaryTree &node, int val)
{
    if (node == NULL)
    {
        node = new TreeNode(val);
    }
    else if (val > node->value)
    {
        if (node->right && node->right->value > val)
        {
            binaryTree tmp = node;
            node = new TreeNode(val);
            node->left = tmp;
            node->right = tmp->right;
            tmp->right = NULL;
            return;
        }
        insert(node->right, val);
    }
    else
    {
        if ((node->left) && (node->left->value < val))
        {

            binaryTree tmp = node;
            node = new TreeNode(val);
            node->right = tmp;
            node->left = tmp->left;
            tmp->left = NULL;
            return;
        }
        insert(node->left, val);
    }
}

int get_num_of_nodes(const binaryTree &node)
{
    if (node == NULL)
        return 0;
    return 1 + get_num_of_nodes(node->left) + get_num_of_nodes(node->right);
}

int get_sum_of_nodes(const binaryTree &node)
{
    if (node == NULL)
        return 0;
    return node->value + get_sum_of_nodes(node->left) + get_sum_of_nodes(node->right);
}

double average(const binaryTree &node)
{
    return (double)get_sum_of_nodes(node) / (double)get_num_of_nodes(node);
}

void add_values(int arr[], const binaryTree &node, int size, int &index)
{
    if ((index >= size) || (node == NULL))
        return;

    arr[index] = node->value;
    if (node->left)
    {
        index++;
        add_values(arr, node->left, size, index);
    }
    if (node->right)
    {
        index++;
        add_values(arr, node->right, size, index);
    }
}

double array_median(int intArray[], int ARRAY_SIZE)
{

    int from = 0;
    while (intArray[from] < 0)
    {
        /* code */
        from++;
    }
    int to = ARRAY_SIZE - 1;
    while (intArray[to] < 0)
    {
        /* code */
        to--;
    }
    int NEW_ARRAY_SIZE = to - from + 1;
    int newArray[NEW_ARRAY_SIZE];
    int index = 0;
    for (size_t i = from; i <= to; i++)
    {
        /* code */
        newArray[index] = intArray[i];
        index++;
    }

    sort(newArray, newArray + NEW_ARRAY_SIZE);
    if (NEW_ARRAY_SIZE % 2 != 0)
    {
        return newArray[NEW_ARRAY_SIZE / 2];
    }
    else
    {
        return (newArray[NEW_ARRAY_SIZE / 2] + newArray[(NEW_ARRAY_SIZE / 2) - 1]) / 2.0;
    }
}

double median(const binaryTree &node)
{
    int size = get_num_of_nodes(node);
    int arr[size];
    int index = 0;
    add_values(arr, node, size, index);
    return array_median(arr, size);
}

void print_bt(const std::string &prefix, const binaryTree node, bool isLeft)
{
    if (node != nullptr)
    {
        cout << prefix;

        cout << (isLeft ? "├──" : "└──");

        // print the value of the node
        cout << node->value << std::endl;

        // enter the next tree level - left and right branch
        print_bt(prefix + (isLeft ? "│   " : "    "), node->left, true);
        print_bt(prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

void print_bt(const binaryTree node)
{
    print_bt("", node, false);
}

void delete_binary_tree(binaryTree &bt)
{
    if (bt == NULL)
        return;
    binaryTree left = bt->left;
    binaryTree right = bt->right;
    delete bt;
    delete_binary_tree(left);
    delete_binary_tree(right);
}

int main()
{

    binaryTree root = new TreeNode(0);
    root->right = new TreeNode(1);
    root->left = new TreeNode(2);

    auto *node_three = new TreeNode(3);
    auto *node_four = new TreeNode(4);
    auto *node_five = new TreeNode(5);

    root->right->left = node_three;
    root->right->right = node_five;
    root->left->left = node_four;

    print_bt(root);

    if (is_binary_search_tree(root))
    {
        /* code */
        cout << "root is a binary search tree" << endl;
    }
    else
    {
        cout << "root is not a valid binary search tree" << endl;
    }

    delete_binary_tree(root);

    // Example of a valid binary search tree:
    //        10
    //       /  \
    //      5   15
    //     / \    \
    //    2   7   20

    binaryTree bst_root = new TreeNode(10);
    bst_root->left = new TreeNode(5);
    bst_root->right = new TreeNode(15);
    bst_root->left->left = new TreeNode(2);
    bst_root->left->right = new TreeNode(7);
    bst_root->right->right = new TreeNode(20);

    // if (is_binary_search_tree(bst_root))
    //     cout << "bst_root is a binary search tree" << endl;
    // else
    //     cout << "bst_root is not a valid binary search tree" << endl;

    // insert(bst_root, 13);
    // insert(bst_root, 4);
    // insert(bst_root, 1);
    // insert(bst_root, 18);
    // insert(bst_root, 30);
    print_bt(bst_root);

    // if (is_binary_search_tree(bst_root))
    //     cout << "bst_root is a binary search tree" << endl;
    // else
    //     cout << "bst_root is not a valid binary search tree" << endl;

    cout << "Average: " << average(bst_root) << endl;
    cout << "Median: " << median(bst_root) << endl;

    median(bst_root);
    delete_binary_tree(bst_root);

    return 0;
}