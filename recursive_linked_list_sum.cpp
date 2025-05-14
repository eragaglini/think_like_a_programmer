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

int positive_tail_recursive_sum(linkdListInt lst, int acc = 0)
{
    if (lst == NULL) return acc;
    acc = acc + (lst->data > 0 ? lst->data : 0);
    return positive_tail_recursive_sum(lst->next, acc);
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
    int array[] = {-3, 0, 1, 2, -5, 4, -1, 6, -2, 3, 7, -8, 9, -4, 10, -6, 11, 12, -9, 13, -7, 14, 15, -10, 16, 17, -11, 18, 19, -12};
    int size = sizeof(array) / sizeof(int);

    linkdListInt list1 = init_linkd_list(array, size);

    output(list1);
    cout << endl;

    cout << "Result: " << positive_tail_recursive_sum(list1) << endl;

    delete_linkd_list(list1);

    return 0;
}
