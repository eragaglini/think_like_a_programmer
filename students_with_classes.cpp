#include <iostream>
#include <string>
#include <regex>
using namespace std;

/*
Design a class or set of classes for use in a program that maintains a class roster. For
each student, store the student’s name, ID, and final grade score in the range 0–100.
The program will allow student records to be added or removed; display the record of
a particular student, identified by ID, with the grade displayed as a number and as a
letter; and display the average score for the class.
The appropriate letter grade for a
particular score is shown in this table:

Score Range     Letter Grade

93–100          A
90–92           A–
87–89           B+
83–86           B
80–82           B–
77–79           C+
73–76           C
70–72           C–
67–69           D+
60–66           D
0–59            F

*/

class studentRecord
{
public:
    studentRecord();
    studentRecord(int newGrade, int newID, string newName);
    int grade();
    void setGrade(int newGrade);
    int studentID();
    void setStudentID(int newID);
    string name();
    void setName(string newName);
    string letterGrade();

private:
    int _grade;
    int _studentID;
    string _name;
    bool isValidName(string name);
    bool isValidGrade(int grade);
};

class studentCollection
{
private:
    struct studentNode
    {
        studentRecord studentData;
        studentNode *next;
    };

public:
    studentCollection();
    studentCollection(const studentCollection &original);
    void addRecord(studentRecord newStudent);
    studentRecord recordWithNumber(int idNum);
    void removeRecord(int idNum);
    ~studentCollection();
    studentCollection &operator=(const studentCollection &rhs);

private:
    typedef studentNode *studentList;
    studentList _listHead;
    studentList copiedList(const studentList original);
    void deleteList(studentList &listPtr);
};

int main()
{
    std::cout << "Hello, World!" << std::endl;

    studentRecord test = studentRecord(77, 1001, "Test");
    cout << test.name() << endl;
    cout << test.letterGrade() << endl;
    studentRecord invalidTest = studentRecord();
    cout << invalidTest.letterGrade() << endl;

    studentCollection s;
    studentRecord stu3(84, 1152, "Sue");
    studentRecord stu2(75, 4875, "Ed");
    studentRecord stu1(98, 2938, "Todd");
    s.addRecord(stu3);
    s.addRecord(stu2);
    s.addRecord(stu1);
    s.removeRecord(4875);

    return 0;
}

// student
string studentRecord::name()
{
    return _name;
}

void studentRecord::setName(string name)
{
    if (isValidName(name))
    {
        /* code */
        _name = name;
        return;
    }
}

int studentRecord::studentID()
{
    return _studentID;
}

void studentRecord::setStudentID(int studentID)
{
    _studentID = studentID;
}

bool studentRecord::isValidGrade(int grade)
{
    if ((grade >= 0) && (grade <= 100))
        return true;
    else
        return false;
}

int studentRecord::grade()
{
    return _grade;
}

void studentRecord::setGrade(int newGrade)
{
    if (isValidGrade(newGrade))
        _grade = newGrade;
}

studentRecord::studentRecord(int newGrade, int newID, string newName)
{
    setGrade(newGrade);
    setStudentID(newID);
    setName(newName);
}

studentRecord::studentRecord()
{
    setGrade(0);
    setStudentID(-1);
    setName("");
}

string studentRecord::letterGrade()
{
    if (!isValidGrade(_grade))
        return "ERROR";
    const int NUMBER_CATEGORIES = 11;
    const string GRADE_LETTER[] = {"F", "D", "D+", "C-", "C", "C+", "B-", "B", "B+", "A-", "A"};
    const int LOWEST_GRADE_SCORE[] = {0, 60, 67, 70, 73, 77, 80, 83, 87, 90, 93};
    int category = 0;
    while (category < NUMBER_CATEGORIES && LOWEST_GRADE_SCORE[category] <= _grade)
        category++;
    return GRADE_LETTER[category - 1];
}

// Test if the given string has anything not in A-Za-z0-9_
bool studentRecord::isValidName(string str)
{

    // Make own character set
    regex regx("[@_!#$%^&*()<>?/|}{~:]");

    // Pass the string in regex_search
    // method
    return (regex_search(str, regx) == 0);
}

// student collection
studentCollection::studentCollection()
{
    _listHead = NULL;
}

void studentCollection::addRecord(studentRecord newStudent)
{
    studentNode *newNode = new studentNode;
    newNode->studentData = newStudent;
    newNode->next = _listHead;
    _listHead = newNode;
}

studentRecord studentCollection::recordWithNumber(int idNum)
{
    studentNode *loopPtr = _listHead;
    while (loopPtr != NULL && loopPtr->studentData.studentID() != idNum)
    {
        loopPtr = loopPtr->next;
    }
    if (loopPtr == NULL)
    {
        studentRecord dummyRecord(-1, -1, "");
        return dummyRecord;
    }
    else
    {
        return loopPtr->studentData;
    }
}

void studentCollection::removeRecord(int idNum)
{
    studentNode *loopPtr = _listHead;
    studentNode *trailing = NULL;
    while (loopPtr != NULL && loopPtr->studentData.studentID() != idNum)
    {
        trailing = loopPtr;
        loopPtr = loopPtr->next;
    }
    if (loopPtr == NULL)
        return;
    if (trailing == NULL)
    {
        _listHead = _listHead->next;
    }
    else
    {
        trailing->next = loopPtr->next;
    }
    delete loopPtr;
}

void studentCollection::deleteList(studentList &listPtr)
{
    while (listPtr != NULL)
    {
        studentNode *temp = listPtr;
        listPtr = listPtr->next;
        delete temp;
    }
}

studentCollection::~studentCollection()
{
    deleteList(_listHead);
}

studentCollection::studentList studentCollection::copiedList(const studentList original)
{
    if (original == NULL)
    {
        return NULL;
    }
    studentList newList = new studentNode;
    newList->studentData = original->studentData;
    studentNode *oldLoopPtr = original->next;
    studentNode *newLoopPtr = newList;
    while (oldLoopPtr != NULL)
    {
        newLoopPtr->next = new studentNode;
        newLoopPtr = newLoopPtr->next;
        newLoopPtr->studentData = oldLoopPtr->studentData;
        oldLoopPtr = oldLoopPtr->next;
    }
    newLoopPtr->next = NULL;
    return newList;
}

studentCollection &studentCollection::operator=(const studentCollection &rhs)
{
    if (this != &rhs)
    {
        deleteList(_listHead);
        _listHead = copiedList(rhs._listHead);
    }
    return *this;
}

studentCollection::studentCollection(const studentCollection &original)
{
    _listHead = copiedList(original._listHead);
}