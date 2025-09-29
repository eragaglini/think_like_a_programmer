#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

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
    int year();
    void setYear(int year);
    string audit();
    void setAudit(string audit);
    string title();
    void setTitle(string title);


private:
    int _grade;
    int _studentID;
    string _name;
    string _audit;
    string _title;
    int _year;
    bool isValidName(string name);
    bool isValidGrade(int grade);
};

/**
 * The Builder interface specifies methods for creating the different parts of
 * the Product objects.
 */
class Builder {
public:
    virtual ~Builder() {}
    virtual void addStudentRecordTitle(string title) const = 0;
    virtual void addStudentRecordYear(int year) const = 0;
    virtual void addStudentRecordAudit(string audit) const = 0;
};

class ConcreteBuilder1 : public Builder {
private:

    studentRecord* student;

    /**
     * A fresh builder instance should contain a blank product object, which is
     * used in further assembly.
     */
public:

    ConcreteBuilder1() {
        this->Reset();
    }

    ~ConcreteBuilder1() {
        delete student;
    }

    void Reset() {
        this->student = new studentRecord();
    }
    /**
     * All production steps work with the same product instance.
     */

    void addStudentRecordTitle(string title)const override {
        this->student->setTitle(title);
    }

    void addStudentRecordYear(int year)const override {
        this->student->setYear(year);
    }

    void addStudentRecordAudit(string audit)const override {
        this->student->setAudit(audit);
    }

    /**
     * Concrete Builders are supposed to provide their own methods for
     * retrieving results. That's because various types of builders may create
     * entirely different products that don't follow the same interface.
     * Therefore, such methods cannot be declared in the base Builder interface
     * (at least in a statically typed programming language). Note that PHP is a
     * dynamically typed language and this method CAN be in the base interface.
     * However, we won't declare it there for the sake of clarity.
     *
     * Usually, after returning the end result to the client, a builder instance
     * is expected to be ready to start producing another product. That's why
     * it's a usual practice to call the reset method at the end of the
     * `getProduct` method body. However, this behavior is not mandatory, and
     * you can make your builders wait for an explicit reset call from the
     * client code before disposing of the previous result.
     */

     /**
      * Please be careful here with the memory ownership. Once you call
      * GetProduct the user of this function is responsable to release this
      * memory. Here could be a better option to use smart pointers to avoid
      * memory leaks
      */

    studentRecord* getStudentRecord() {
        studentRecord* result = this->student;
        this->Reset();
        return result;
    }
};


class Client
{
public:
    static void main(std::vector<std::string>& args)
    {
        studentRecord tony = studentRecord(76, 1456, "Tony");

        ConcreteBuilder1 * builder = new ConcreteBuilder1();
        builder->addStudentRecordAudit("Test Audit");
        builder->addStudentRecordTitle("Problems of Unconditional Branching");
        builder->addStudentRecordYear(2025);
        studentRecord *rob = builder->getStudentRecord();
        rob->setName("Bob");
        rob->setStudentID(1140);
        rob->setGrade(65);
        cout << rob->name() << endl;
        cout << rob->audit() << endl;
        cout << tony.audit() << endl;
    }
};

int main(int argc, char** argv) {
    std::vector<std::string> parameter(argv + 1, argv + argc);
    Client::main(parameter);
    return 0;
};

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

string studentRecord::audit()
{
    return _audit;
}

void studentRecord::setAudit(string audit)
{
    if (isValidName(audit))
    {
        /* code */
        _audit = audit;
        return;
    }
}

string studentRecord::title()
{
    return _title;
}

void studentRecord::setTitle(string title)
{
    if (isValidName(title))
    {
        /* code */
        _title = title;
        return;
    }
}

int studentRecord::studentID()
{
    return _studentID;
}



void studentRecord::setYear(int year)
{
    _year = year;
}

int studentRecord::year()
{
    return _year;
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
    const string GRADE_LETTER[] = { "F", "D", "D+", "C-", "C", "C+", "B-", "B", "B+", "A-", "A" };
    const int LOWEST_GRADE_SCORE[] = { 0, 60, 67, 70, 73, 77, 80, 83, 87, 90, 93 };
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

