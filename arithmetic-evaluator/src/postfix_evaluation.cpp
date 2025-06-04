#include "project/posftix_evaluation.hpp"
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

/**
 * Performs an operation on two operands based on the operator token passed in.
 * The operator token is expected to be one of the following: '+', '-', '*', '/'.
 * 
 * @param op A token representing the operator.
 * @param first The first operand.
 * @param second The second operand.
 * @return The result of the operation.
 */
float do_eval(token op, float first, float second)
{
    char op_code = op.c;
    switch (op_code)
    {
        // Add the two operands
        case '+':
            return first + second;
        // Subtract the second operand from the first operand
        case '-':
            return first - second;
        // Multiply the two operands
        case '*':
            return first * second;
        // Divide the first operand by the second operand
        case '/':
            if (second == 0) {
                // Handle division by zero error
                throw std::runtime_error("Division by zero");
            }
            return first / second;
        default:
            // Handle unknown operator error
            throw std::runtime_error("Unknown operator");
    }
}

/**
 * Evaluates a postfix expression represented as a vector of tokens.
 * The expression is iterated over, and when a number is encountered, it is pushed
 * onto a stack. When an operator is encountered, the top two numbers are popped
 * off the stack, the operation is performed, and the result is pushed back onto
 * the stack. The final result is the only item left on the stack.
 * 
 * @param postfix_tokens A vector of tokens representing the postfix expression.
 * @return The result of the postfix expression as a float.
 */
float eval_postfix(vector<token> postfix_tokens)
{
    stack<float> operand_stack;
    for (size_t i = 0; i < postfix_tokens.size(); i++)
    {
        token t = postfix_tokens[i];
        if (t.number)
        {
            // Push the number onto the stack
            operand_stack.push(t.f);
        }
        else
        {
            // Pop the second operand off the stack
            float second = operand_stack.top();
            operand_stack.pop();

            // Pop the first operand off the stack
            float first = operand_stack.top();
            operand_stack.pop();

            // Perform the operation and push the result onto the stack
            operand_stack.push(do_eval(t, first, second));
        }
    }

    // The final result is the only item left on the stack
    return operand_stack.top();
}
