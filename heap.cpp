#include <iostream>
#include <cmath>
using namespace std;

struct heapNode
{
    int data;
    heapNode *left;
    heapNode *right;
};

typedef heapNode *heap;

void delete_heap(heap &h)
{
    if (h == NULL)
        return;
    heapNode *left = h->left;
    heapNode *right = h->right;
    delete h;
    delete_heap(left);
    delete_heap(right);
}

void get_branch(heap &h, heap &old_heap)
{
    if (old_heap->left != NULL && old_heap->right != NULL)
    {
        /* code */
        if (abs(old_heap->left->data - h->data) > abs(old_heap->right->data - h->data))
        {
            /* code */
            h->right = old_heap->right;
            old_heap->right = NULL;
        }
        else
        {
            h->right = old_heap->left;
            old_heap->left = NULL;
        }
    }

    else if (old_heap->left == NULL)
    {
        /* code */
        h->right = old_heap->right;
        old_heap->right = NULL;
    }
    else
    {
        h->right = old_heap->left;
        old_heap->left = NULL;
    }
}

heap get_node(heap &h, int val)
{
    heap new_heap = new heapNode;
    new_heap->data = val;
    new_heap->left = NULL;
    new_heap->right = NULL;
    return new_heap;
}

void add_val(heap &h, int val)
{
    if (h->left == NULL)
    {
        /* code */
        h->left = get_node(h, val);
    }
    else if (h->right == NULL)
    {
        /* code */
        h->right = get_node(h, val);
    }
    else if (val >= h->left->data)
    {
        heap new_heap = get_node(h, val);
        new_heap->left = h->left;
        get_branch(new_heap, h->left);
        h->left = new_heap;
    }
    else if (val >= h->right->data)
    {
        /* code */
        heap new_heap = get_node(h, val);
        new_heap->left = h->right;
        get_branch(new_heap, h->right);
        h->right = new_heap;
    }
    else
    {
        heap h2 = abs(h->left->data - val) > abs(h->right->data - val) ? h->right : h->left;
        add_val(h2, val);
    }
}

void reshape_heap(heap &h)
{

}

void heapify(int arr[], heap &h, int size, int index = 0)
{
    // nothing more to process
    if (size == index)
        return;
    int val = arr[index];
    // if heap is currently null, we create a new heap with the val
    // at given index
    if (h == NULL)
    {
        /* code */
        h = new heapNode;
        h->data = val;
        h->left = NULL;
        h->right = NULL;
    }
    else
    {
        if (h->data > val)
        {
            /* code */
            add_val(h, val);
        }
        else
        {
            heap old_heap = h;
            h = new heapNode;
            h->data = val;
            h->left = old_heap;
            get_branch(h, old_heap);
        }
    }
    reshape_heap(h);
    heapify(arr, h, size, ++index);
}

void print_bt(const std::string &prefix, const heap node, bool isLeft)
{
    if (node != nullptr)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──");

        // print the value of the node
        std::cout << node->data << std::endl;

        // enter the next tree level - left and right branch
        print_bt(prefix + (isLeft ? "│   " : "    "), node->left, true);
        print_bt(prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

void print_bt(const heap node)
{
    print_bt("", node, false);
}

bool is_heap(const heap node)
{
    if ((node->left == NULL) && (node->right == NULL))
    {
        /* code */
        return true;
    }
    else if ((node->left == NULL) && (node->right != NULL))
    {
        /* code */
        return false;
    }
    else if ((node->left != NULL) && (node->right == NULL))
    {
        /* code */
        return false;
    }
    return (
        (node->data > node->left->data) && (node->data > node->right->data)
    ) && (is_heap(node->left)) && is_heap(node->right);
}

int main()
{
    // Your code here
    int arr[] = {12, 7, 25, 3, 18, 20, 15,};
    int n = sizeof(arr) / sizeof(arr[0]);

    heap h1 = NULL;
    heapify(arr, h1, n);

    print_bt(h1);

    cout << is_heap(h1) << endl;
    delete_heap(h1);
    return 0;
}