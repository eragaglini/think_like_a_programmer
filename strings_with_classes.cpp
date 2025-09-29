#include <iostream>
#include <string>
using namespace std;

class MyString
{
private:
    struct stringChar
    {
        char charData;
        stringChar *next;
    };
    typedef stringChar *stringList;
    stringList _listHead;
    void addStringChar(stringList character);
    stringList getCharacterAt(int index);
    stringList getNewChar(const char character);

public:
    // Constructor
    MyString();
    MyString(const string &s);

    void append(const char character);
    void output();
    // Overloading [] operator to access elements in array
    // style
    char operator[](int);
    int getLength();
    void remove(int from, int num);

    ~MyString();
};

int main()
{

    MyString myStr("Test!");
    myStr.output();
    myStr.append('!');
    myStr.output();
    for (size_t i = 0; i < myStr.getLength(); i++)
    {
        /* code */
        cout << myStr[i] << endl;
    }

    cout << "String length: " << myStr.getLength() << endl;

    MyString myStr2("abcdefg");
    myStr2.remove(3, 4);
    myStr2.output();

    MyString myStr3("abcdefghijklmno");
    myStr3.remove(1, 7);
    myStr3.output();

    MyString myStr4("abcdefg");
    myStr4.remove(1, 4);
    myStr4.output();
    return 0;
}

MyString::MyString()
{
    _listHead = NULL;
}

MyString::MyString(const string &s)
{
    for (size_t i = 0; i < s.length(); i++)
    {
        /* code */
        stringChar *newNode = getNewChar(s[i]);
        if (i == 0)
        {
            /* code */
            this->_listHead = newNode;
        }
        else
        {
            this->addStringChar(newNode);
        }
    }
}

void MyString::addStringChar(stringList character)
{
    stringList loopPtr = this->_listHead;
    while (loopPtr->next != NULL)
    {
        /* code */
        loopPtr = loopPtr->next;
    }
    loopPtr->next = character;
}

void MyString::output()
{
    stringList loopPtr = this->_listHead;
    while (loopPtr != NULL)
    {
        /* code */
        cout << loopPtr->charData;
        loopPtr = loopPtr->next;
    }
    cout << endl;
}

void MyString::append(const char character)
{
    stringChar *newChar = this->getNewChar(character);
    addStringChar(newChar);
}

MyString::~MyString()
{
    stringList listPtr = this->_listHead;
    while (listPtr != NULL)
    {
        stringChar *temp = listPtr;
        listPtr = listPtr->next;
        delete temp;
    }
}

MyString::stringList MyString::getNewChar(const char character)
{
    MyString::stringChar *newChar = new stringChar;
    newChar->charData = character;
    newChar->next = NULL;
    return newChar;
};

MyString::stringList MyString::getCharacterAt(int index)
{
    if (index > (this->getLength() - 1))
    {
        /* code */
        cout << "Index out of range" << endl;
        exit(0);
    }

    stringList listPtr = this->_listHead;
    if (index == 0)
        return listPtr;
    int current_index = 1;

    while (listPtr != NULL)
    {
        listPtr = listPtr->next;
        if (index == current_index)
            break;
        current_index++;
    }
    return listPtr;
}

char MyString::operator[](int index)
{
    stringList listPtr = getCharacterAt(index);
    return listPtr->charData;
}

int MyString::getLength()
{
    stringList listPtr = this->_listHead;
    int current_index = 0;

    while (listPtr != NULL)
    {
        listPtr = listPtr->next;
        current_index++;
    }
    return current_index;
}

void MyString::remove(int from, int num)
{
    if (
        (from > (this->getLength() - 1)) ||
        ((from + num) > (this->getLength())))
    {
        /* code */
        cout << "Index out of range" << endl;
        exit(0);
    }

    stringList nextPtr;
    stringList endPtr = this->getCharacterAt(from + num - 2);

    if (from > 1)
    {
        for (size_t i = 0; i < (from - 1); i++)
        {
            /* code */
            nextPtr = this->_listHead->next;
            delete this->_listHead;
            this->_listHead = nextPtr;
        }
    }
    else
    {
        nextPtr = this->_listHead;
    }
    this->_listHead = nextPtr;
    stringList listPtr = endPtr->next;
    endPtr->next = NULL;

    while (listPtr != NULL)
    {
        stringChar *temp = listPtr;
        listPtr = listPtr->next;
        delete temp;
    }
}
