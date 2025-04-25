#include <iostream>
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

int main()
{
    appendTester();
    concatenateTester();
    substringTester();
    return 0;
}
