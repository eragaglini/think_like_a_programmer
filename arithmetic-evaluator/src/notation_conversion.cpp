#include "project/expression_tokenizer.hpp"
#include <stack>
#include <stdexcept>
#include <vector>

using namespace std;

int get_operator_precedence(token t)
{
    if ((t.c == '+') || (t.c == '-'))
    {
        return 1;
    }
    else if ((t.c == '*') || (t.c == '/'))
    {
        return 2;
    }
    else
    {
        throw invalid_argument("Received invalid token!");
    }
}

vector<token> infix_to_postfix(vector<token>& tokens)
{
    stack<token> operator_stack;
    vector<token> postfix_tokens;

    for (size_t i = 0; i < tokens.size(); i++)
    {
        token t = tokens[i];
        if ((t.number))
        {
            postfix_tokens.push_back(tokens[i]);
        }
        else if (t.c == '(')
        {
            operator_stack.push(t);
        }
        else if (t.c == ')')
        {
            while (operator_stack.top().c != '(')
            {
                postfix_tokens.push_back(operator_stack.top());
                operator_stack.pop();
            }
            // removes the '('
            operator_stack.pop();
        }
        else
        {
            if (!operator_stack.empty())
            {
                while (!operator_stack.empty() &&
                       ((operator_stack.top().c != '(') &&
                        ((get_operator_precedence(t) <=
                          get_operator_precedence(operator_stack.top())))))
                {
                    postfix_tokens.push_back(operator_stack.top());
                    operator_stack.pop();
                }
            }
            operator_stack.push(t);
        }
    }
    while (!operator_stack.empty())
    {
        postfix_tokens.push_back(operator_stack.top());
        operator_stack.pop();
    }

    return postfix_tokens;
}

