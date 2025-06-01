#include "project/notation_conversion.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    string expression;
    cout << "Enter an arithmetic expression: " << endl;
    getline(cin, expression);

    cout << "------ infix notation ------ " << endl;

    vector<token> infix_tokens = tokenize_expression(expression);
    for (auto it = infix_tokens.begin(); it != infix_tokens.end(); ++it)
    {

        if (it->number)
            cout << it->f;
        else
            cout << it->c;
    }
    cout << endl;
    vector<token> posftix_tokens = infix_to_postfix(infix_tokens);

    cout << "------ postfix notation ------ " << endl;

    for (auto it = posftix_tokens.rbegin(); it != posftix_tokens.rend(); ++it)
    {

        if (it->number)
            cout << it->f;
        else
            cout << it->c;
    }
    cout << endl;

    return 0;
}
