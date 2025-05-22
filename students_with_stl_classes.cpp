#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

struct studentRecord
{
    int studentNum;
    int grade;
};
typedef std::vector<studentRecord> studentCollection;

void addRecord(studentCollection &sc, int stuNum, int gr)
{
    studentRecord record = {
        stuNum, // studentNum
        gr      // grade
    };
    sc.push_back(record);
}

double averageRecord(studentCollection sc)
{
    auto const count = static_cast<float>(sc.size());
    int sum = accumulate(sc.begin(), sc.end(), 0,
                         [](int sum, const studentRecord &p)
                         { return sum + p.grade; });
    return (double)sum / (double)count;
}

void printStudentCollection(const studentCollection &sc)
{
    for (int i = 0; i < sc.size(); ++i)
        cout << sc[i].studentNum << ' ';
    cout << endl;
}

void removeRecord(studentCollection &sc, int stuNum)
{
    sc.erase(
        std::remove_if(sc.begin(), sc.end(), [&](studentRecord const &st)
                       { return st.studentNum == stuNum; }),
        sc.end());
}

int main()
{
    studentCollection sc;
    addRecord(sc, 1274, 91);
    addRecord(sc, 1265, 118);
    addRecord(sc, 1119, 60);
    cout << "Students: " << endl;
    printStudentCollection(sc);
    cout << " ------------ " << endl;
    double avg = averageRecord(sc);
    cout << "Average grade: " << endl;
    cout << avg << endl;
    cout << " ------------ " << endl;

    removeRecord(sc, 1274);
    cout << "Students after trying to remove student with id == 1001: " << endl;
    printStudentCollection(sc);
    cout << " ------------ " << endl;
    return 0;
}
