#include <iostream>
#include <algorithm>
using namespace std;

void removeNumber(int numbers[], int idx, int &size)
{
    int i;
    for (i = idx; i < size - 1; i++)
        numbers[i] = numbers[i + 1];
    size--;
}

// Function to remove duplicate
// elements This function returns
// new size of modified array.
int removeDuplicates(int arr[], int n)
{
    // Return, if array is empty or
    // contains a single element
    if (n == 0 || n == 1)
        return n;

    int temp[n];

    // Start traversing elements
    int j = 0;

    // If current element is not equal
    // to next element then store that
    // current element
    for (int i = 0; i < n - 1; i++)
        if (arr[i] != arr[i + 1])
            temp[j++] = arr[i];

    // Store the last element as whether
    // it is unique or repeated, it hasn't
    // stored previously
    temp[j++] = arr[n - 1];

    // Modify original array
    for (int i = 0; i < j; i++)
        arr[i] = temp[i];

    return j;
}

void printArray(const int intArray[], int size)
{
    for (size_t i = 0; i < size; i++)
    {
        /* code */
        cout << intArray[i] << " ";
    }
    cout << endl;
}

int main()
{

    // given an array of integers and determines the mode,
    // which is the number that appears most frequently in the array.
    const int numbers[] = {14, 14, 27, 27, 5, 5, 5, 18, 18, 31, 31, 9, 9, 22, 22, 1, 1, 16, 16, 25, 25, 11, 11, 7, 7, 20, 20, 4, 4, 29};
    int numbers_length = sizeof(numbers) / sizeof(int);
    int sorted_numbers[numbers_length];
    for (size_t i = 0; i < numbers_length; i++)
    {
        /* code */
        sorted_numbers[i] = numbers[i];
    }
    sort(sorted_numbers, sorted_numbers + numbers_length);
    printArray(sorted_numbers, numbers_length);

    int unique_length = removeDuplicates(sorted_numbers, numbers_length);
    int array_count[unique_length];
    printArray(sorted_numbers, numbers_length);

    for (size_t i = 0; i < unique_length; i++)
    {
        /* code */
        int num = sorted_numbers[i];
        int count = 0;
        for (size_t j = 0; j < numbers_length; j++)
        {
            /* code */
            if (numbers[j] == num)
            {
                /* code */
                count++;
            }
        }
        array_count[i] = count;
    }

    int max = array_count[0];
    int max_index = 0;
    for (size_t i = 1; i < unique_length; i++)
    {
        /* code */
        if (array_count[i] > max)
        {
            /* code */
            max = array_count[i];
            max_index = i;
        }
    }
    cout << "the number that appears most frequently in the array is " << sorted_numbers[max_index] << " with: " << max << " occurences." << endl;

    return 0;
}
