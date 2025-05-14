#include <iostream>

using namespace std;

struct listNodeInt
{
    int data;
    listNodeInt *next;
};

typedef listNodeInt *linkdListInt;

void output_data(const linkdListInt &s)
{
    if (s == NULL)
        return;
    cout << s->data << ",";
    output_data(s->next);
}

void output(const linkdListInt &s)
{
    cout << "[";
    output_data(s);
    cout << "]";
}

int tail_recursive_count_occurrences(linkdListInt &s, int target, int acc = 0)
{
    if (s == NULL) return acc;
    return tail_recursive_count_occurrences(s->next, target, acc + (s->data == target ? 1 : 0));
}

linkdListInt init_linkd_list(int array[], int size, int index = 0)
{
    if (index == size) return NULL;
    
    listNodeInt *newNode = new listNodeInt;
    newNode->data = array[index];
    newNode->next = init_linkd_list(array, size, index + 1);
    return newNode;
}

void delete_linkd_list(linkdListInt& list) {
    while (list != NULL) {
        listNodeInt* next = list->next;
        delete list;
        list = next;
    }
}

int main()
{
    int array[] = {-3, 0, 1, 11, -5, 4, -1, 6, -2, 3, 7, -8, 9, -4, 10, -6, 11, 12, -9, 13, -7, 14, 15, -10, 16, 11, -11, 18, 19, -12};
    int size = sizeof(array) / sizeof(int);

    linkdListInt list1 = init_linkd_list(array, size);

    output(list1);
    cout << endl;

    cout << "Result: " << tail_recursive_count_occurrences(list1, 11) << endl;

    delete_linkd_list(list1);

    return 0;
}
