#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

struct Student
{
    int grade;
    int studentID;
    string name;
};

const int STUDENTS_SIZE = 15;

Student students[STUDENTS_SIZE] = {
    {90, 12345, "John Doe"},
    {85, 67890, "Jane Smith"},
    {95, 34567, "Bob Johnson"},
    {80, 90123, "Alice Brown"},
    {92, 45678, "Mike Davis"},
    {88, 11111, "Emily Chen"},
    {76, 22222, "David Lee"},
    {98, 33333, "Sophia Patel"},
    {82, 44444, "Oliver Kim"},
    {89, 55555, "Ava Moreno"},
    {91, 66666, "Ethan Hall"},
    {84, 77777, "Lily Tran"},
    {96, 88888, "Noah Brooks"},
    {87, 99999, "Isabella Garcia"},
    {93, 10101, "Julian Sanchez"}};

const char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
// const char cipherAlphabet[] = {'J', 'A', 'Z', 'E', 'K', 'R', 'T', 'N', 'D', 'F', 'G', 'Y', 'C', 'Q', 'V', 'B', 'H', 'M', 'W', 'X', 'I', 'P', 'L', 'O', 'S', 'U'};
const int ALPHABET_LENGHT = 26;

bool compareByGrade(Student const &lhs, Student const &rhs)
{
    return lhs.grade < rhs.grade;
}

int searchByName(Student a[], int size, string name)
{
    for (size_t i = 0; i < size; i++)
    {
        Student student = a[i];
        // /* code */
        if (!student.name.compare(name))
            return i;
    }
    return -1;
}

double arrayAverage(int intArray[], int ARRAY_SIZE)
{
    double sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        sum += intArray[i];
    }
    double average = (sum + 0.5) / ARRAY_SIZE;
    return average;
}

double arrayMedian(int intArray[], int ARRAY_SIZE)
{
    sort(intArray, intArray + ARRAY_SIZE);
    if (ARRAY_SIZE % 2 != 0)
    {
        return intArray[ARRAY_SIZE / 2];
    }
    else
    {
        return (intArray[ARRAY_SIZE / 2] + intArray[(ARRAY_SIZE / 2) - 1]) / 2;
    }
}

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

int getposition(const char *array, size_t size, char c)
{
    const char *end = array + size;
    const char *match = std::find(array, end, c);
    return (end == match) ? -1 : (match - array);
}

void getCipherText(const char charArray1[], char result[], int textLength, const char from[], const char to[])
{
    for (size_t i = 0; i < textLength; i++)
    {
        /* code */
        int index = getposition(from, 26, charArray1[i]);
        if (index != -1)
        {
            result[i] = to[index];
        }
        else
        {
            result[i] = charArray1[i];
        }
    }
}

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
    sort(students, students + STUDENTS_SIZE, compareByGrade);

    for (size_t i = 0; i < STUDENTS_SIZE; i++)
    {
        cout << "Name: " << students[i].name << ", grade: " << students[i].grade << endl;
    }

    string name;
    cout << "Enter your name: ";

    // Taking string as input
    getline(cin, name);

    int index = searchByName(students, STUDENTS_SIZE, name);
    if (index >= 0)
        cout << "Your Grade: " << students[index].grade << endl;
    else
        cout << "No student found for the given name." << endl;

    const int NUM_AGENTS = 3;
    const int NUM_MONTHS = 12;
    int sales[NUM_AGENTS][NUM_MONTHS] = {
        {1856, 498, 30924, 87478, 328, 2653, 387, 3754, 387587, 2873, 276, 32},
        {5865, 5456, 3983, 6464, 9957, 4785, 3875, 3838, 4959, 1122, 7766, 2534},
        {23, 55, 67, 99, 265, 376, 232, 223, 4546, 564, 4544, 3434}};

    int highestAverage = arrayAverage(sales[0], 12);
    for (int agent = 1; agent < NUM_AGENTS; agent++)
    {
        int agentAverage = arrayAverage(sales[agent], 12);
        if (agentAverage > highestAverage)
            highestAverage = agentAverage;
    }
    cout << "Highest monthly average: " << highestAverage << "\n";

    int highestMedian = arrayMedian(sales[0], 12);
    for (size_t i = 0; i < NUM_AGENTS; i++)
    {
        /* code */

        int agentMedian = arrayMedian(sales[i], 12);
        if (agentMedian > highestMedian)
            highestMedian = agentMedian;
    }
    cout << "Highest monthly median: " << highestMedian << "\n";

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

    // creatin a cipher alphabet by copying and shuffling the alphabet
    char cipherAlphabet[ALPHABET_LENGHT];
    strncpy(cipherAlphabet, alphabet, 26);
    random_shuffle(&cipherAlphabet[0], &cipherAlphabet[25]);
    cout << cipherAlphabet << endl;

    char plainText[] = "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG, PACKING MY BOX WITH FIVE DOZEN LIQUOR JUGS.";
    int textLength = sizeof(plainText) / sizeof(char);
    char cipherText[textLength];
    getCipherText(plainText, cipherText, textLength, alphabet, cipherAlphabet);

    cout << endl;
    cout << "Plain text: " << endl;
    cout << plainText << endl;
    cout << "Ciphertext: " << endl;
    cout << cipherText << endl;

    cout << "----------" << endl;

    char decodedMessage[textLength];
    getCipherText(cipherText, decodedMessage, textLength, cipherAlphabet, alphabet);

    cout << endl;
    cout << "Ciphertext: " << endl;
    cout << cipherText << endl;
    cout << "Decoded Message: " << endl;
    cout << decodedMessage << endl;

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
            if (numbers[j] ==  num)
            {
                /* code */
                count ++;
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
