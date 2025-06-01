#include "project/expression_tokenizer.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    string expression;
    cout << "Enter an arithmetic expression: " << endl;
    getline(cin, expression);


    vector<token> tokens = tokenize_expression(expression);
    for (unsigned int i = 0; i < tokens.size(); i++)
    {
        if (tokens[i].number)
            cout << "number: " << tokens[i].f << endl;
        else
            cout << "sign: " << tokens[i].c << endl;
    }

    return 0;
}
