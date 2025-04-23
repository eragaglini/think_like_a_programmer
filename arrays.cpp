#include <iostream>
using namespace std;

bool checkIfSorted(int intArray[], int ARRAY_SIZE)
{
    int el = intArray[0];
    for (size_t i = 1; i < ARRAY_SIZE; i++)
    {
        /* code */
        if (intArray[i] < el)
            return false;
        el = intArray[i];
    }
    return true;
}

int main()
{

    // Sorted arrays
    int sortedArray1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    cout << checkIfSorted(sortedArray1, 15) << endl;

    int sortedArray2[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75};

    cout << checkIfSorted(sortedArray2, 15) << endl;
    int sortedArray3[] = {-10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4};

    cout << checkIfSorted(sortedArray3, 15) << endl;

    // Unsorted arrays
    int unsortedArray1[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 1};

    cout << checkIfSorted(unsortedArray1, 15) << endl;
    int unsortedArray2[] = {10, 40, 30, 60, 50, 20, 70, 80, 90, 10, 50, 30, 20, 40, 60};

    cout << checkIfSorted(unsortedArray2, 15) << endl;
    int unsortedArray3[] = {-5, 10, -1, 7, -3, 2, -9, 5, -7, 1, 6, -4, 8, -2, 3};

    cout << checkIfSorted(unsortedArray3, 15) << endl;
    return 0;
}
