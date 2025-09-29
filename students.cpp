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

    return 0;
}
