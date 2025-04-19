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

int main()
{
    // sort(students, students + STUDENTS_SIZE, compareByGrade);

    // for (size_t i = 0; i < STUDENTS_SIZE; i++)
    // {
    //     /* code */
    //     cout << "Name: " << students[i].name << ", grade: " << students[i].grade << endl;
    // }

    // string name;
    // cout << "Enter your name: ";

    // Taking string as input
    // getline(cin, name);

    // int index = searchByName(students, STUDENTS_SIZE, name);
    // if (index >= 0)
    //     cout << "Grade: " << students[index].grade << endl;
    // else
    //     cout << "No student found" << endl;

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
    cout << "Plain Text: " << endl;
    cout << decodedMessage << endl;

    return 0;
}
