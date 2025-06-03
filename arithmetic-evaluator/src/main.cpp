#include "project/posftix_evaluation.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    string expression;
    cout << "Enter an arithmetic expression: " << endl;
    getline(cin, expression);

    vector<token> infix_tokens = tokenize_expression(expression);
    vector<token> posftix_tokens = infix_to_postfix(infix_tokens);
    cout << eval_postfix(posftix_tokens) << endl;

    return 0;
}
