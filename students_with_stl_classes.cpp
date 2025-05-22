#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

struct studentRecord
{
    int studentNum;
    int grade;
};
typedef std::vector<studentRecord> studentCollection;

bool compare_by_id(const studentRecord &a, const studentRecord &b)
{
    return a.studentNum < b.studentNum;
}

void addRecord(studentCollection &sc, int stuNum, int gr)
{
    studentRecord record = {
        stuNum, // studentNum
        gr      // grade
    };
    sc.push_back(record);
    sort(sc.begin(), sc.end(), compare_by_id);
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

int interpolation_search(studentCollection &sc, int lo, int hi, int stuNum)
{
    int pos;

    // Since array is sorted, an element present
    // in array must be in range defined by corner
    if (lo <= hi && (stuNum >= sc[lo].studentNum) && (stuNum <= sc[hi].studentNum))
    {

        // Probing the position with keeping
        // uniform distribution in mind.
        pos = lo + (((stuNum - sc[lo].studentNum) * (hi - lo)) / (sc[hi].studentNum - sc[lo].studentNum));
        // Condition of target found
        if (sc[pos].studentNum == stuNum)
            return pos;

        // If x is larger, x is in right sub array
        if (sc[pos].studentNum < stuNum)
            return interpolation_search(sc, pos + 1, hi, stuNum);

        // If x is smaller, x is in left sub array
        if (sc[pos].studentNum > stuNum)
            return interpolation_search(sc, lo, pos - 1, stuNum);
    }
    return -1;
}

int main()
{
    studentCollection sc;
    // Uniformly distributed student IDs, step = 10
    addRecord(sc, 1000, 75);
    addRecord(sc, 1010, 82);
    addRecord(sc, 1020, 91);
    addRecord(sc, 1030, 67);
    addRecord(sc, 1040, 88);
    addRecord(sc, 1050, 60);
    addRecord(sc, 1060, 95);
    addRecord(sc, 1070, 73);
    addRecord(sc, 1080, 99);
    addRecord(sc, 1090, 54);
    addRecord(sc, 1100, 77);
    addRecord(sc, 1110, 85);
    addRecord(sc, 1120, 92);
    addRecord(sc, 1130, 61);
    addRecord(sc, 1140, 78);

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

    // student id to be searched
    int stuNum = 1070;
    int index = interpolation_search(sc, 0, sc.size() -1, stuNum);

    // If element was found
    if (index != -1)
        cout << "Element found at index " << index << endl;
    else
        cout << "Element not found." << endl;

    return 0;
}
