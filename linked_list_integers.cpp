#include <iostream>
#include <cmath>
#include <sstream>
#include <string.h>

using namespace std;

struct listNodeInt
{
    int data;
    listNodeInt *next;
};

typedef listNodeInt *linkdListInt;

void output(const linkdListInt &s)
{
    if (s == NULL)
        return;
    cout << s->data << " ";
    output(s->next);
}

int getTotalValue(const linkdListInt &s, int acc = 0)
{
    if (s == NULL)
        return acc;
    acc = (acc * 10) + s->data;
    return getTotalValue(s->next, acc);
}

int string_size_1(const char *pchar)
{
    int Size = 0;
    while (pchar[Size] != '\0')
        Size++;
    return Size;
}

linkdListInt setTotalValueHelper(const char *pchar)
{
    size_t string_size = string_size_1(pchar);
    listNodeInt *newNode = new listNodeInt;
    int data = pchar[0] - '0';
    newNode->data = data;
    newNode->next = NULL;

    if (string_size == 1)
    {
        return newNode;
    }

    newNode->next = setTotalValueHelper(&pchar[1]);
    return newNode;
}

linkdListInt setTotalValue(int data)
{
    if (data < 0)
    {
        listNodeInt *newNode = new listNodeInt;
        newNode->data = -1;
        newNode->next = NULL;
        return newNode;
    }
    stringstream strs;
    strs << data;
    string temp_str = strs.str();
    const char *pchar = temp_str.c_str(); // dont use cast

    return setTotalValueHelper(pchar);
}

linkdListInt appendHelper(linkdListInt &s, int data)
{
    listNodeInt *newNode = new listNodeInt;
    newNode->data = data;
    newNode->next = NULL;

    if (s == NULL)
        return newNode;

    listNodeInt *loopPtr = s;
    while (loopPtr->next != NULL)
    {
        loopPtr = loopPtr->next;
    }
    loopPtr->next = newNode;
    return s;
}

linkdListInt append(linkdListInt &s, int data)
{
    if (!((data > 0) && (data < 10)))
    {
        /* code */
        return s;
    }
    return appendHelper(s, data);
}

linkdListInt sumLinkedLists(const linkdListInt &s1, const linkdListInt &s2)
{
    return setTotalValue(getTotalValue(s1) + getTotalValue(s2));
}

void deleteLinkedList(linkdListInt& list) {
    while (list != NULL) {
        listNodeInt* next = list->next;
        delete list;
        list = next;
    }
}

int main()
{
    linkdListInt list1 = setTotalValue(156);
    cout << "list1 value: " << getTotalValue(list1) << endl;
    linkdListInt list2 = setTotalValue(119);
    cout << "list2 value: " << getTotalValue(list2) << endl;

    linkdListInt list3 = sumLinkedLists(list1, list2);
    cout << "list3 value: " << getTotalValue(list3) << endl;
    linkdListInt list4 = setTotalValue(20000);
    cout << "list4 value: " << getTotalValue(list4) << endl;
    linkdListInt list5 = setTotalValue(0);
    cout << "list5 value: " << getTotalValue(list5) << endl;
    linkdListInt list6 = setTotalValue(-30);
    cout << "list6 value: " << getTotalValue(list6) << endl;

    if (list6->data == -1)
    {
        /* code */
        cout << "Value must be positive!!" << endl;
    }

    deleteLinkedList(list1);
    deleteLinkedList(list2);
    deleteLinkedList(list3);
    deleteLinkedList(list4);
    deleteLinkedList(list5);
    deleteLinkedList(list6);

    return 0;
}
