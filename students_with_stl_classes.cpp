#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <algorithm>
#include <type_traits>

using namespace std;

struct studentRecord
{
    int studentNum;
    int grade;
};
typedef std::vector<studentRecord> studentCollection;

struct listNode
{
    studentRecord studentData;
    listNode* next;
};
typedef listNode* linkedList;


void delete_linkd_list(linkedList& list) {
    while (list != NULL) {
        listNode* next = list->next;
        delete list;
        list = next;
    }
}

struct HashMap
{
    vector<linkedList> buckets;
};

void delete_hash_map(HashMap hash_map)
{
    for (size_t i = 0; i < hash_map.buckets.size(); i++)
    {
        /* code */
        delete_linkd_list(hash_map.buckets[i]);
    }
}

hash<int> h;

int get_index(int key, int size)
{
    return h(key) % size;
}

linkedList add_record(linkedList list, listNode* node)
{
    node->next = list;
    return node;
}

HashMap get_hash_map(studentCollection& sc, int size = 100)
{
    std::vector<linkedList> buckets;
    buckets.reserve(size);
    for (int i = 0; i < size; i++)
    {
        buckets.push_back(NULL);
    }

    for (size_t i = 0; i < sc.size(); i++)
    {
        /* code */
        listNode* newNode = new listNode;
        newNode->studentData = sc[i];
        int index = get_index(sc[i].studentNum, buckets.size());
        buckets[index] = add_record(buckets[index], newNode);
    }
    HashMap hash_map = {
        buckets };
    return hash_map;
}

void print_linked_list(const linkedList& sc)
{
    listNode* loopPtr = sc;
    while (loopPtr != NULL)
    {
        /* code */
        cout << "Student Num: " << loopPtr->studentData.studentNum << ", grade: " << loopPtr->studentData.grade << endl;
        loopPtr = loopPtr->next;
    }
}

void print_hash_map(const HashMap& hash_map)
{
    cout << "Hash Map: " << endl;
    for (size_t i = 0; i < hash_map.buckets.size(); i++)
    {
        /* code */
        cout << "buckets " << i << ": " << endl;
        print_linked_list(hash_map.buckets[i]);
        cout << " ---- " << endl;
    }
}
studentRecord find_student(const int studentNum, linkedList& buckets)
{

    studentRecord dummy_node = {
        -1,
        -1 };
    if (buckets == NULL)
        return dummy_node;
    listNode* loopPtr = buckets;
    while (loopPtr != NULL)
    {
        /* code */
        if (loopPtr->studentData.studentNum == studentNum)
        {
            /* code */
            return loopPtr->studentData;
        }
        loopPtr = loopPtr->next;
    }
    return dummy_node;
}

studentRecord get_student_record(int key, HashMap hash_map)
{
    return find_student(key, hash_map.buckets[get_index(key, hash_map.buckets.size())]);
}

bool compare_by_id(const studentRecord& a, const studentRecord& b)
{
    return a.studentNum < b.studentNum;
}

void add_record_to_student_collection(studentCollection& sc, int stuNum, int gr)
{
    studentRecord record = {
        stuNum, // studentNum
        gr      // grade
    };
    sc.push_back(record);
    sort(sc.begin(), sc.end(), compare_by_id);
}

auto sum_grades = [](int sum, const studentRecord& p)
    {
        return sum + p.grade;
    };


double averageRecord(studentCollection sc)
{
    auto const count = static_cast<float>(sc.size());
    int sum = accumulate(sc.begin(), sc.end(), 0, sum_grades);
    return (double)sum / (double)count;
}

void print_student_collection(const studentCollection& sc)
{
    for (int i = 0; i < sc.size(); ++i)
        cout << sc[i].studentNum << ' ';
    cout << endl;
}

void remove_record(studentCollection& sc, int stuNum)
{
    sc.erase(
        std::remove_if(sc.begin(), sc.end(), [&](studentRecord const& st)
            { return st.studentNum == stuNum; }),
        sc.end());
}

int interpolation_search(studentCollection& sc, int lo, int hi, int stuNum)
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
    add_record_to_student_collection(sc, 1000, 75);
    add_record_to_student_collection(sc, 1010, 82);
    add_record_to_student_collection(sc, 1020, 91);
    add_record_to_student_collection(sc, 1030, 67);
    add_record_to_student_collection(sc, 1040, 88);
    add_record_to_student_collection(sc, 1050, 60);
    add_record_to_student_collection(sc, 1060, 95);
    add_record_to_student_collection(sc, 1070, 73);
    add_record_to_student_collection(sc, 1080, 99);
    add_record_to_student_collection(sc, 1090, 54);
    add_record_to_student_collection(sc, 1100, 77);
    add_record_to_student_collection(sc, 1110, 85);
    add_record_to_student_collection(sc, 1120, 92);
    add_record_to_student_collection(sc, 1130, 61);
    add_record_to_student_collection(sc, 1140, 78);

    cout << "Students: " << endl;
    print_student_collection(sc);
    cout << " ------------ " << endl;
    double avg = averageRecord(sc);
    cout << "Average grade: " << endl;
    cout << avg << endl;
    cout << " ------------ " << endl;

    remove_record(sc, 1274);
    cout << "Students after trying to remove student with id == 1001: " << endl;
    print_student_collection(sc);
    cout << " ------------ " << endl;

    // student id to be searched
    int stuNum = 1070;
    int index = interpolation_search(sc, 0, sc.size() - 1, stuNum);

    // If element was found
    if (index != -1)
        cout << "Element found at index " << index << endl;
    else
        cout << "Element not found." << endl;

    HashMap hash_map = get_hash_map(sc);
    print_hash_map(hash_map);

    cout << get_student_record(1080, hash_map).grade << endl;

    delete_hash_map(hash_map);


    std::map<int, int> m;
    for (size_t i = 0; i < sc.size(); i++)
    {
        /* code */
        m[sc[i].studentNum] = sc[i].grade;
    }

    for (const auto& [key, value] : m)
    {
        std::cout << key << ": " << value << '\n';
    }
    return 0;
}
