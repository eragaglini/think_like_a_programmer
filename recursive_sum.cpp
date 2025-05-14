#include <iostream>
using namespace std;

int positive_recursive_sum(int array[], int size)
{
    int val = array[0] > 0 ? array[0] : 0;
    if (size == 1) return val;
    return val + positive_recursive_sum(&array[1], size - 1);
}

int positive_tail_recursive_sum(int array[], int size, int acc = 0)
{
    if (size == 1) return acc;
    acc = acc + (array[0] > 0 ? array[0] : 0);
    return positive_tail_recursive_sum(&array[1], size - 1, acc);
}

int main() {
    
    int array[] = {-3, 0, 1, 2, -5, 4, -1, 6, -2, 3, 7, -8, 9, -4, 10, -6, 11, 12, -9, 13, -7, 14, 15, -10, 16, 17, -11, 18, 19, -12};
    int size = sizeof(array) / sizeof(int);
    int positive_sum = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] > 0) {
            positive_sum += array[i];
        }
    }
    cout << "Positive numbers sum: " << positive_sum << endl;
    cout << "Recursive Positive numbers sum: " << positive_recursive_sum(array, size) << endl;
    cout << "Tail Recursive Positive numbers sum: " << positive_recursive_sum(array, size) << endl;


    return 0;
}

