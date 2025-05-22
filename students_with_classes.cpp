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



// This declaration creates a type named firstStudentPolicy as a pointer to a
// function that returns a bool and takes two parameters of type studentRecord.
// The parentheses around * firstStudentPolicy are necessary to prevent the
// declaration from being interpreted as a function that returns a pointer to a
// bool.
typedef bool (*firstStudentPolicy)(studentRecord r1, studentRecord r2);

// With this declaration in place, we can create our three policy functions:
bool higherGrade(studentRecord r1, studentRecord r2)
{
    return r1.grade() > r2.grade();
}
bool lowerStudentNumber(studentRecord r1, studentRecord r2)
{
    return r1.studentID() < r2.studentID();
}
bool nameComesFirst(studentRecord r1, studentRecord r2)
{
    return strcmp(r1.name().c_str(), r2.name().c_str()) < 0;
}

class scIterator;

enum FirstStudentPolicy {
  LOWER_STUDENT_NUMBER,
  NAMES_COMES_FIRST,
  HIGHER_GRADE
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
    float averageRecord();
    studentCollection *RecordsWithinRange(int low_grade, int high_grade);
    void output();
    void setFirstStudentPolicy(FirstStudentPolicy val);
    studentRecord firstStudent();
    friend class scIterator;
    scIterator firstItemIterator();

private:
    firstStudentPolicy _currentPolicy;
    typedef studentNode *studentList;
    studentList _listHead;
    studentList copiedList(const studentList original);
    void deleteList(studentList &listPtr);
};


class scIterator
{
public:
    scIterator();
    scIterator(studentCollection::studentNode *initial);
    void advance();
    bool pastEnd();
    studentRecord student();

private:
    studentCollection::studentNode *current;
};


int main()
{

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
    cout << s.averageRecord() << endl;
    s.removeRecord(4875);

    studentCollection classRoster;

    // Adding 30 student records manually
    classRoster.addRecord(studentRecord(95, 1001, "Alice"));
    classRoster.addRecord(studentRecord(88, 1002, "Bob"));
    classRoster.addRecord(studentRecord(76, 1003, "Charlie"));
    classRoster.addRecord(studentRecord(92, 1004, "Diana"));
    classRoster.addRecord(studentRecord(81, 1005, "Eve"));
    classRoster.addRecord(studentRecord(67, 1006, "Frank"));
    classRoster.addRecord(studentRecord(73, 1007, "Grace"));
    classRoster.addRecord(studentRecord(89, 1008, "Hank"));
    classRoster.addRecord(studentRecord(94, 1009, "Ivy"));
    classRoster.addRecord(studentRecord(78, 1010, "Jack"));
    classRoster.addRecord(studentRecord(85, 1011, "Karen"));
    classRoster.addRecord(studentRecord(91, 1012, "Leo"));
    classRoster.addRecord(studentRecord(82, 1013, "Mona"));
    classRoster.addRecord(studentRecord(74, 1014, "Nina"));
    classRoster.addRecord(studentRecord(87, 1015, "Oscar"));
    classRoster.addRecord(studentRecord(96, 1016, "Paul"));
    classRoster.addRecord(studentRecord(79, 1017, "Quinn"));
    classRoster.addRecord(studentRecord(84, 1018, "Rachel"));
    classRoster.addRecord(studentRecord(90, 1019, "Steve"));
    classRoster.addRecord(studentRecord(77, 1020, "Tina"));
    classRoster.addRecord(studentRecord(83, 1021, "Uma"));
    classRoster.addRecord(studentRecord(86, 1022, "Victor"));
    classRoster.addRecord(studentRecord(93, 1023, "Wendy"));
    classRoster.addRecord(studentRecord(80, 1024, "Xander"));
    classRoster.addRecord(studentRecord(72, 1025, "Yara"));
    classRoster.addRecord(studentRecord(68, 1026, "Zane"));
    classRoster.addRecord(studentRecord(75, 1027, "Liam"));
    classRoster.addRecord(studentRecord(88, 1028, "Sophia"));
    classRoster.addRecord(studentRecord(92, 1029, "Ethan"));
    classRoster.addRecord(studentRecord(89, 1030, "Olivia"));

    studentCollection newClassRoosterPtr = *classRoster.RecordsWithinRange(75, 80);

    newClassRoosterPtr.output();

    classRoster.setFirstStudentPolicy(HIGHER_GRADE);
    cout << classRoster.firstStudent().name() << endl;

    classRoster.setFirstStudentPolicy(NAMES_COMES_FIRST);
    cout << classRoster.firstStudent().name() << endl;


    classRoster.setFirstStudentPolicy(LOWER_STUDENT_NUMBER);
    cout << classRoster.firstStudent().name() << endl;

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
    _currentPolicy = NULL;
}

void studentCollection::addRecord(studentRecord newStudent)
{
    studentNode *newNode = new studentNode;
    newNode->studentData = newStudent;
    newNode->next = _listHead;
    _listHead = newNode;
}

float studentCollection::averageRecord()
{
    int sum = 0;
    int length = 0;
    studentList listPtr = this->_listHead;
    while (listPtr != NULL)
    {
        sum += listPtr->studentData.grade();
        listPtr = listPtr->next;
        length++;
    }
    return (length > 0) ? ((float)sum / (float)length) : sum;
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

studentCollection *studentCollection::RecordsWithinRange(int low_range, int high_range)
{
    studentCollection *newStudentCollectionPtr = new studentCollection;
    studentList loopPtr = this->_listHead;
    while (loopPtr != NULL)
    {
        /* code */
        if (
            (loopPtr->studentData.grade() > low_range) &&
            (loopPtr->studentData.grade() < high_range))
        {
            /* code */
            studentList studPtr = new studentNode;
            studPtr->studentData.setGrade(loopPtr->studentData.grade());
            studPtr->studentData.setName(loopPtr->studentData.name());
            studPtr->next = NULL;
            newStudentCollectionPtr->addRecord(studPtr->studentData);
        }
        loopPtr = loopPtr->next;
    }

    return newStudentCollectionPtr;
}

void studentCollection::output()
{
    studentList loopPtr = this->_listHead;
    while (loopPtr != NULL)
    {
        /* code */
        cout << "Name: " << loopPtr->studentData.name() << ", grade: " << loopPtr->studentData.grade() << endl;
        ;
        loopPtr = loopPtr->next;
    }
    cout << endl;
}

void studentCollection::setFirstStudentPolicy(FirstStudentPolicy value)
{
    switch (value)
    {
    case HIGHER_GRADE:
        /* code */
        _currentPolicy = higherGrade;
        break;
    
    case NAMES_COMES_FIRST:
        /* code */
        _currentPolicy = nameComesFirst;
        break;
    
    case LOWER_STUDENT_NUMBER:
        _currentPolicy = lowerStudentNumber;
        break;
    
    default:
        break;
    }
}

studentRecord studentCollection::firstStudent()
{
    // If there is no list to review or no policy in place, we return a dummy record.
    if (_listHead == NULL || _currentPolicy == NULL)
    {
        studentRecord dummyRecord(-1, -1, "");
        return dummyRecord;
    }
    // Otherwise, we traverse the list to find the student who best meets the current policy,
    studentNode *loopPtr = _listHead;
    studentRecord first = loopPtr->studentData;
    loopPtr = loopPtr->next;
    while (loopPtr != NULL)
    {
        if (_currentPolicy(loopPtr->studentData, first))
        {
            first = loopPtr->studentData;
        }
        loopPtr = loopPtr->next;
    }
    return first;
}

scIterator::scIterator()
{
    current = NULL;
}
scIterator::scIterator(studentCollection::studentNode *initial)
{
    current = initial;
}

scIterator studentCollection::firstItemIterator()
{
    return scIterator(_listHead);
}

void scIterator::advance()
{
    if (current != NULL)
        current = current->next;
}
bool scIterator::pastEnd()
{
    return current == NULL;
}

studentRecord scIterator::student()
{
    if (current == NULL)
    {
        studentRecord dummyRecord(-1, -1, "");
        return dummyRecord;
    }
    else
    {
        return current->studentData;
    }
}