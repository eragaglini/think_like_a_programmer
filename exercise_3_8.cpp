#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

struct Student
{
    int grade;
    int studentID;
    string name;
};


const int STUDENTS_SIZE = 30;

Student students[STUDENTS_SIZE] = {
    {85, 8142, "Ethan Thompson"},
    {92, 3519, "Ava Lee"},
    {67, 2701, "Liam Patel"},
    {78, 4678, "Sophia Rodriguez"},
    {95, 9821, "Mason Kim"},
    {72, 1357, "Isabella Martin"},
    {89, 6283, "Noah Brooks"},
    {98, 7429, "Emily Chen"},
    {61, 4198, "Logan White"},
    {82, 9532, "Abigail Hall"},
    {99, 1189, "Alexander Brown"},
    {75, 2756, "Mia Garcia"},
    {88, 4321, "William Davis"},
    {91, 6587, "Olivia Taylor"},
    {58, 9823, "Benjamin Russell"},
    {81, 1456, "Charlotte Lewis"},
    {96, 3698, "Elijah Walker"},
    {70, 7532, "Harper Jenkins"},
    {87, 2198, "Jackson Lee"},
    {93, 4673, "Amelia Hernandez"},
    {65, 9821, "Caleb Martin"},
    {80, 1359, "Lillian Brooks"},
    {97, 6281, "Gabriel Hall"},
    {74, 7429, "Aiden Kim"},
    {86, 9534, "Julia White"},
    {94, 1187, "Michael Brown"},
    {62, 2758, "Sydney Patel"},
    {83, 4323, "Samantha Taylor"},
    {90, 6589, "Daniel Russell"},
    {76, 1458, "Madison Lewis"}
};
 
bool compareByGrade(Student const &lhs, Student const &rhs)
{
    return lhs.grade < rhs.grade;
}
 
int main()
{
    
    // srand(time(0)); // Seed the random number generator

    // Student students[STUDENTS_SIZE];
    // for (int i = 0; i < STUDENTS_SIZE; i++) {
    //     students[i].grade = rand() % 12 + 1; // Random grade between 1 and 12
    //     students[i].studentID = rand() % 9000 + 1000; // Random student ID between 1000 and 9999
    //     students[i].name = "Student " + std::to_string(i+1); // Simple name for demonstration purposes
    // }

    cout << "Students: " << endl;

    for (size_t i = 0; i < STUDENTS_SIZE; i++)
    {
        /* code */
        cout << "Student ID: " << students[i].studentID << ", Name: " << students[i].name << ", Grade: " << students[i].grade << endl;
    }

    cout << "--------------" << endl;

    cout << "Students sorted by grade: " << endl;
 
    sort(students, students + STUDENTS_SIZE, compareByGrade);

    for (size_t i = 0; i < STUDENTS_SIZE; i++)
    {
        /* code */
        cout << "Student ID: " << students[i].studentID << ", Name: " << students[i].name << ", Grade: " << students[i].grade << endl;
    }

    cout << "--------------" << endl;

    int better_than_25 = ceil((double)STUDENTS_SIZE * 0.25);

    cout << "To do better than 25 per cent of students you have to get at least: " << students[better_than_25].grade + 1 << endl;

    int better_than_50 = ceil((double)STUDENTS_SIZE * 0.50);

    cout << "To do better than 50 per cent of students you have to get at least: " << students[better_than_50].grade + 1 << endl;
    
    int better_than_75 = ceil((double)STUDENTS_SIZE * 0.75);

    cout << "To do better than 75 per cent of students you have to get at least: " << students[better_than_75].grade + 1 << endl;

    return 0;
}
