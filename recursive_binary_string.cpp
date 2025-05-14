#include <iostream>
#include <string>
using namespace std;

struct listNodeChar
{
    char c;
    listNodeChar *next;
};
typedef listNodeChar *linkdListString;


bool tail_recursive_check_odd_parity(linkdListString lst, int count = 0)
{
    if (lst == NULL) return (count % 2 != 0);
    return tail_recursive_check_odd_parity(lst->next, count + (lst->c == '1' ? 1 : 0));
}

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

linkdListString init_linkd_list(const string data, int index = 0)
{
    if (index == data.length()) return NULL;
    
    listNodeChar *newNode = new listNodeChar;
    newNode->c = data[index];
    newNode->next = init_linkd_list(data, index + 1);
    return newNode;
}

void delete_linkd_list(linkdListString& list) {
    while (list != NULL) {
        listNodeChar* next = list->next;
        delete list;
        list = next;
    }
}

int main()
{
    string input;
    cout << "Enter a binary string: ";
    cin >> input;

    linkdListString input_linkd_list = init_linkd_list(input);

    cout << "Linked list:" << endl;
    output(input_linkd_list);
    
    // if (iterative_check_odd_parity(input))
    if (tail_recursive_check_odd_parity(input_linkd_list))
    {
        /* code */

        cout << "Your binary string has odd parity" << endl;
    }
    else
    {
        cout << "No odd parity" << endl;
    }
    delete_linkd_list(input_linkd_list);
    return 0;
}
