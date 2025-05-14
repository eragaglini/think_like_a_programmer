#include <iostream>
using namespace std;

int iterative_count_occurrences(int array[], int size, int target)
{
    int count = 0;
    for (size_t i = 0; i < size; i++)
    {
        /* code */
        if (array[i] == target) count++;
    }
    return count;
}

int tail_recursive_count_occurrences(int array[], int size, int target, int index = 0, int acc = 0)
{
    if (index == size) return acc;
    return tail_recursive_count_occurrences(array, size, target, index + 1, acc + (array[index] == target ? 1 : 0));
}

int main() {
    
    int array[] = {11, 27, 5, 5, 18, 23, 1, 14, 7, 11, 11, 25, 3, 20, 20, 9, 15, 22, 4, 6, 6, 11, 10, 17, 12, 12, 24, 8, 19, 21};    
    int size = sizeof(array) / sizeof(int);
    int target;
    cout << "Enter a target number: ";
    cin >> target;
    
    cout << "The number: " << target << " appears: " << tail_recursive_count_occurrences(array, size, target) << " times" << endl;
    // cout << "The number: " << target << " appears: " << iterative_count_occurrences(array, size, target) << " times" << endl;

    return 0;
}

