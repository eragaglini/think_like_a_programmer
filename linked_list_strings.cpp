#include <iostream>
using namespace std;

struct listNodeChar
{
    char c;
    listNodeChar *next;
};
typedef listNodeChar *linkdListString;

void output(const linkdListString &s)
{
    if (s == NULL)
        return;
    cout << s->c;
    listNodeChar *loopPtr = s->next;
    while (loopPtr != NULL)
    {
        /* code */
        cout << loopPtr->c;
        loopPtr = loopPtr->next;
    }
    cout << endl;
}

void append(linkdListString &s, char c)
{
    listNodeChar *newNode = new listNodeChar;
    newNode->c = c;
    newNode->next = NULL;

    if (s == NULL)
        return;

    listNodeChar *loopPtr = s;
    while (loopPtr->next != NULL)
    {
        /* code */
        loopPtr = loopPtr->next;
    }
    loopPtr->next = newNode;
}

linkdListString copyString(const linkdListString &s)
{
    if (s == NULL)
        return NULL;
    listNodeChar *newNode = new listNodeChar;
    newNode->c = s->c;
    newNode->next = copyString(s->next);
    return newNode;
}

void concatenate(linkdListString &s1, const linkdListString s2)
{
    linkdListString newStr = copyString(s2);
    listNodeChar *loopPtr = s1;
    while (loopPtr->next != NULL)
    {
        /* code */
        loopPtr = loopPtr->next;
    }
    loopPtr->next = newStr;
}

int length(const linkdListString &s, int acc = 0)
{
    if (s == NULL)
        return acc;
    return length(s->next, acc + 1);
}

void removeChars(linkdListString &s1, int from, int charNum)
{
    int strLen = length(s1);
    // if charNum is 0, it means that i don't have to remove any character
    // if the length of the string is less than from + charNum, it means the index is out of range
    from--;
    if ((charNum == 0) || (strLen < (from + charNum)))
        return;
    from--;
    listNodeChar *loopPtr = s1;
    for (size_t i = 0; i < from; i++)
    {
        /* code */
        loopPtr = loopPtr->next;
    }
    listNodeChar *fromChar = loopPtr;
    loopPtr = fromChar->next;
    listNodeChar *temp;
    for (size_t i = 1; i <= charNum; i++)
    {
        /* code */
        temp = loopPtr;
        fromChar->next = loopPtr->next;
        delete temp;
        loopPtr = fromChar->next;
    }
}

int main()
{
    linkdListString str;
    listNodeChar *char1 = new listNodeChar;
    char1->c = 'a';
    listNodeChar *char2 = new listNodeChar;
    char2->c = 'b';
    listNodeChar *char3 = new listNodeChar;
    char3->c = 'c';
    listNodeChar *char4 = new listNodeChar;
    char4->c = 'd';
    str = char1;
    char1->next = char2;
    char2->next = char3;
    char3->next = char4;
    output(str);
    append(str, 'e');
    output(str);

    linkdListString newStr = copyString(str);
    append(newStr, 'f');

    output(newStr);
    output(str);

    concatenate(newStr, str);
    append(newStr, 'g');
    output(newStr);
    output(str);

    cout << "newStr length: " << length(newStr) << endl;

    cout << " ------------ " << endl;
    output(newStr);

    linkdListString str1 = copyString(newStr);
    removeChars(str1, 5, 3);
    output(str1);

    linkdListString str2 = copyString(newStr);
    removeChars(str2, 5, 8);
    output(str2);

    return 0;
}
