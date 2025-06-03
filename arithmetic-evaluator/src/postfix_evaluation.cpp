#include "project/posftix_evaluation.hpp"
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

float do_eval(token op, float first, float second)
{
    char op_code = op.c;
    switch (op_code)
    {
        case '+':
            /* code */
            return first + second;
        case '-':
            /* code */
            return first - second;
        case '*':
            /* code */
            return first * second;
        case '/':
            /* code */
            return first / second;
    }
}

float eval_postfix(vector<token> postfix_tokens)
{
    stack<float> operand_stack;
    for (size_t i = 0; i < postfix_tokens.size(); i++)
    {
        /* code */
        token t = postfix_tokens[i];
        if (t.number)
        {
            /* code */
            operand_stack.push(t.f);
        }
        else
        {
            float second = operand_stack.top();
            operand_stack.pop();

            float first = operand_stack.top();
            operand_stack.pop();

            operand_stack.push(do_eval(t, first, second));
        }
    }

    return operand_stack.top();
}