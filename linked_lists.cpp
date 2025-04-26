#include <iostream>
using namespace std;

struct listNode
{
    int studentNum;
    int grade;
    listNode *next;
};
typedef listNode *studentCollection;

void addRecord(studentCollection &sc, int stuNum, int gr)
{
    listNode *newNode = new listNode;
    newNode->studentNum = stuNum;
    newNode->grade = gr;
    newNode->next = sc;
    sc = newNode;
}

double averageRecord(studentCollection sc)
{
    if (sc == NULL)
        return 0;
    listNode *loopPtr = sc;
    double sum = 0;
    int count = 0;
    while (loopPtr != NULL)
    {
        /* code */
        sum += loopPtr->grade;
        count++;
        loopPtr = loopPtr->next;
    }
    return sum / count;
}

void printLinkedList(const studentCollection &sc)
{
    listNode *loopPtr = sc;
    while (loopPtr != NULL)
    {
        /* code */
        cout << "Student Num: " << loopPtr->studentNum << ", grade: " << loopPtr->grade << endl;
        loopPtr = loopPtr->next;
    }
}

void removeRecord(studentCollection &sc, int studentNum)
{
    if (sc == NULL)
    {
        /* code */
        return;
    }
    else if (sc->studentNum == studentNum)
    {
        /* code */
        listNode *temp = sc->next;
        delete sc;
        sc = temp;
        return;
    }
    else
    {
        listNode *loopPtr = sc;
        while (loopPtr->next->studentNum != studentNum)
        {
            /* code */
            loopPtr = loopPtr->next;
            if (loopPtr->next == NULL)
            {
                /* code */
                return;
            }
        }

        listNode *temp = loopPtr->next;
        loopPtr->next = loopPtr->next->next;
        delete temp;
        return;
    }
}

int main()
{
    studentCollection sc;
    listNode *node1 = new listNode;
    node1->studentNum = 1001;
    node1->grade = 78;
    listNode *node2 = new listNode;
    node2->studentNum = 1012;
    node2->grade = 93;
    listNode *node3 = new listNode;
    node3->studentNum = 1076;
    node3->grade = 85;
    sc = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = NULL;
    addRecord(sc, 1274, 91);
    cout << "Students: " << endl;
    printLinkedList(sc);
    cout << " ------------ " << endl;
    int avg = averageRecord(sc);
    cout << "Average grade: " << endl;
    cout << avg << endl;
    cout << " ------------ " << endl;
    node1 = node2 = node3 = NULL;


    removeRecord(sc, 9);
    cout << "Students after trying to remove student with id == 9: " << endl;
    printLinkedList(sc);
    cout << " ------------ " << endl;

    removeRecord(sc, 1001);
    cout << "Students after trying to remove student with id == 1001: " << endl;
    printLinkedList(sc);
    cout << " ------------ " << endl;
    return 0;
}
