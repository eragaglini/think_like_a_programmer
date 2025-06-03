#include "project/expression_tokenizer.hpp"
#include <stack>
#include <stdexcept>
#include <vector>

using namespace std;

/**
 * Returns the precedence of a given operator token. 
 * Precedence determines the order of evaluation of operators in expressions.
 * 
 * @param t A token representing the operator.
 * @return An integer indicating the precedence level of the operator.
 * @throws invalid_argument if the token is not a recognized operator.
 */
int get_operator_precedence(token t)
{
    // Check if the token is a '+' or '-' operator
    if ((t.c == '+') || (t.c == '-'))
    {
        return 1; // Return precedence level 1
    }
    // Check if the token is a '*' or '/' operator
    else if ((t.c == '*') || (t.c == '/'))
    {
        return 2; // Return precedence level 2
    }
    else
    {
        // Throw an exception if the token is not a valid operator
        throw invalid_argument("Received invalid token!");
    }
}

/**
 * Converts a vector of tokens representing an infix expression to a vector of tokens 
 * representing a postfix expression using the Shunting Yard algorithm.
 * 
 * @param tokens A vector of tokens representing the infix expression.
 * @return A vector of tokens representing the postfix expression.
 */
vector<token> infix_to_postfix(vector<token>& tokens)
{
    stack<token> operator_stack; // Stack to hold operators
    vector<token> postfix_tokens; // Vector to hold the resulting postfix expression

    // Iterate over each token in the infix expression
    for (size_t i = 0; i < tokens.size(); i++)
    {
        token t = tokens[i];
        if (t.number)
        {
            // If the token is a number, add it directly to the postfix expression
            postfix_tokens.push_back(t);
        }
        else if (t.c == '(')
        {
            // Push '(' to the stack
            operator_stack.push(t);
        }
        else if (t.c == ')')
        {
            // Pop from the stack to the postfix expression until '(' is encountered
            while (operator_stack.top().c != '(')
            {
                postfix_tokens.push_back(operator_stack.top());
                operator_stack.pop();
            }
            // Remove the '(' from the stack
            operator_stack.pop();
        }
        else
        {
            // Handle operators
            // Pop operators from the stack to the postfix expression based on their precedence
            while (!operator_stack.empty() && operator_stack.top().c != '(' &&
                   get_operator_precedence(t) <= get_operator_precedence(operator_stack.top()))
            {
                postfix_tokens.push_back(operator_stack.top());
                operator_stack.pop();
            }
            // Push the current operator onto the stack
            operator_stack.push(t);
        }
    }

    // Pop all remaining operators from the stack to the postfix expression
    while (!operator_stack.empty())
    {
        postfix_tokens.push_back(operator_stack.top());
        operator_stack.pop();
    }

    return postfix_tokens;
}

