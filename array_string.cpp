#include <iostream>
#include <string.h>
using namespace std;

typedef char *arrayString;

char characterAt(arrayString s, int position)
{
    return s[position];
}

int length(arrayString s)
{
    int count = 0;
    while (s[count] != 0)
    {
        count++;
    }
    return count;
}

arrayString substring(const arrayString &s, int from, int length)
{
    arrayString newS = new char[length];
    for (size_t i = 0; i < length; i++)
    {
        /* code */
        newS[i] = s[i + from - 1];
    }
    newS[length] = 0;
    return newS;
}

void substringTester()
{
    arrayString a = new char[5];
    a[0] = 'a';
    a[1] = 'b';
    a[2] = 'c';
    a[3] = 'd';
    a[4] = 'e';
    a[5] = 'f';
    a[6] = 'g';
    a[7] = 0;
    arrayString b = substring(a, 3, 4);
    cout << b << endl;
}

void append(arrayString &s, char c)
{
    int oldLength = length(s);
    arrayString newS = new char[oldLength + 2];
    for (int i = 0; i < oldLength; i++)
    {
        newS[i] = s[i];
    }
    newS[oldLength] = c;
    newS[oldLength + 1] = 0;
    delete[] s;
    s = newS;
}

void appendTester()
{
    arrayString a = new char[5];
    a[0] = 't';
    a[1] = 'e';
    a[2] = 's';
    a[3] = 't';
    a[4] = 0;
    append(a, '!');
    cout << a << "\n";
    arrayString b = new char[1];
    b[0] = 0;
    append(b, '!');
    cout << b << "\n";
}

void concatenate(arrayString &s1, arrayString s2)
{
    int s1_OldLength = length(s1);
    int s2_Length = length(s2);
    int s1_NewLength = s1_OldLength + s2_Length;
    arrayString newS = new char[s1_NewLength + 1];
    for (int i = 0; i < s1_OldLength; i++)
    {
        newS[i] = s1[i];
    }
    for (int i = 0; i < s2_Length; i++)
    {
        newS[s1_OldLength + i] = s2[i];
    }
    newS[s1_NewLength] = 0;
    delete[] s1;
    s1 = newS;
}

void concatenateTester()
{
    arrayString a = new char[5];
    a[0] = 't';
    a[1] = 'e';
    a[2] = 's';
    a[3] = 't';
    a[4] = 0;
    arrayString b = new char[4];
    b[0] = 'b';
    b[1] = 'e';
    b[2] = 'd';
    b[3] = 0;
    concatenate(a, b);
    cout << a << "\n";
    a[0] = 't';
    a[1] = 'e';
    a[2] = 's';
    a[3] = 't';
    a[4] = 0;
    arrayString c = new char[1];
    c[0] = 0;
    concatenate(c, a);
    cout << a << "\n"
         << c << "\n";
    cout << (void *)a << "\n"
         << (void *)c << "\n";
}

bool stringsEqual(const arrayString s1, const arrayString s2)
{
    int s1_length = length(s1);
    int s2_length = length(s2);
    if (s1_length != s2_length)
        return false;
    for (size_t i = 0; i < s1_length; i++)
    {
        /* code */
        if (s1[i] != s2[i])
            return false;
    }
    return true;
}

void stringsEqualTester()
{
    arrayString a = new char[3];
    a[0] = 'a';
    a[1] = 'b';
    a[2] = 0;
    arrayString b = new char[2];
    b[0] = 'b';
    b[1] = 0;
    if (!stringsEqual(a, b))
    {
        /* code */
        cout << "Test Passed!" << endl;
    }
    else
    {
        cout << "Error!" << endl;
    }
    arrayString c = new char[3];
    c[0] = 'a';
    c[1] = 'b';
    c[2] = 0;
    if (stringsEqual(a, c))
    {
        /* code */
        cout << "Test Passed!" << endl;
    }
    else
    {
        cout << "Error!" << endl;
    }
}

arrayString copyArrayStr(const arrayString s)
{
    int s_length = length(s);
    arrayString newS = new char[s_length];
    for (size_t i = 0; i < s_length; i++)
    {
        /* code */
        newS[i] = s[i];
    }
    return newS;
}

arrayString replaceStringHelper(arrayString &s, arrayString target, arrayString replaceText)
{
    int s_length = length(s);
    int target_length = length(target);
    bool checkStringsEqual = stringsEqual(s, target);
    if (
        (s_length < target_length) ||
        ((s_length == target_length) && !checkStringsEqual))
        return copyArrayStr(s);
    else if (checkStringsEqual)
    {
        /* code */
        return replaceText;
    }
    arrayString newS;
    arrayString restOfStr;
    if (s[0] != target[0])
    {
        /* code */
        newS = substring(s, 1, 1);
        restOfStr = &s[1];
    }
    else
    {
        arrayString checkStr = substring(s, 1, target_length);
        if (stringsEqual(checkStr, target))
        {
            /* code */
            newS = copyArrayStr(replaceText);
            restOfStr = &s[target_length];
        }
        else
        {
            newS = substring(s, 1, 1);
            restOfStr = &s[1];
        }
    }
    arrayString rest = replaceStringHelper(restOfStr, target, replaceText);
    concatenate(newS, rest);
    return newS;
}

void replaceString(arrayString &s, arrayString target, arrayString replaceText)
{
    if ((target == NULL) || (replaceText == NULL))
    {
        /* code */
        return;
    }

    arrayString newS = replaceStringHelper(s, target, replaceText);
    delete[] s;
    s = newS;
}

void replaceStringTester()
{

    arrayString s = new char[9];
    s[0] = 'a';
    s[1] = 'b';
    s[2] = 'c';
    s[3] = 'd';
    s[4] = 'a';
    s[5] = 'b';
    s[6] = 'e';
    s[7] = 'e';
    s[8] = 0;

    arrayString s = new char[2];
    s[0] = 'a';
    s[1] = 0;

    arrayString target = new char[3];
    target[0] = 'a';
    target[1] = 'b';
    target[3] = 0;
    arrayString replaceText = new char[4];
    replaceText[0] = 'x';
    replaceText[1] = 'y';
    replaceText[2] = 'z';
    replaceText[3] = 0;
    replaceString(s, target, replaceText);
    cout << s << endl;
}

int main()
{
    appendTester();
    concatenateTester();
    substringTester();
    replaceStringTester();
    stringsEqualTester();
    return 0;
}
