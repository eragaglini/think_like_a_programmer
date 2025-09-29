#include <iostream>
using namespace std;

typedef char *arrayString;

char characterAt(arrayString s, int position)
{
    return s[position + 1];
}

void output(const arrayString s)
{
    for (size_t i = 1; i <= s[0]; i++)
    {
        /* code */
        cout << s[i];
    }
    cout << endl;
}

void append(arrayString &s, char c)
{
    arrayString newS = new char[s[0] + 2];
    newS[0] = s[0] + 1;
    for (int i = 1; i <= s[0]; i++)
    {
        newS[i] = s[i];
    }
    newS[s[0] + 1] = c;
    delete[] s;
    s = newS;
}


void concatenate(arrayString &s1, arrayString s2)
{

    int s1_NewLength = s1[0] + s2[0];
    arrayString newS = new char[s1_NewLength + 1];
    newS[0] = s1_NewLength;
    for (int i = 1; i <= s1[0]; i++)
    {
        newS[i] = s1[i];
    }
    for (int i = 1; i <= s2[0]; i++)
    {
        newS[s1[0] + i] = s2[i];
    }
    delete[] s1;
    s1 = newS;
}

int main()
{
    arrayString str = new char[5];
    str[0] = 4;
    str[1] = 'T';
    str[2] = 'e';
    str[3] = 's';
    str[4] = 't';
    output(str);
    append(str, '!');
    output(str);
    arrayString b = new char[4];
    b[0] = 3;
    b[1] = 'b';
    b[2] = 'e';
    b[3] = 'd';
    concatenate(str, b);
    output(str);
    
    cout << characterAt(str, 0) << endl;
    cout << characterAt(str, 7) << endl;
    cout << characterAt(str, 4) << endl;
    return 0;
}
