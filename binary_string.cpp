#include <iostream>
#include <string>
using namespace std;

bool iterative_check_odd_parity(string input)
{
    int count = 0;
    for (size_t i = 0; i < input.length(); i++)
    {
        /* code */
        if (input[i] == '1')
        {
            count++;
        }
    }
    return (count % 2 != 0);  
}

bool tail_recursive_check_odd_parity(string input, int index = 0, int count = 0)
{
    if (input.length() == index) return (count % 2 != 0);
    return tail_recursive_check_odd_parity(input, index + 1, count + (input[index] == '1' ? 1 : 0));
}

int main()
{
    string input;
    cout << "Enter a binary string: ";
    cin >> input;
    
    // if (iterative_check_odd_parity(input))
    if (tail_recursive_check_odd_parity(input))
    {
        /* code */

        cout << "Your binary string has odd parity" << endl;
    }
    else
    {
        cout << "No odd parity" << endl;
    }
    
    cout << input << endl;
    return 0;
}
