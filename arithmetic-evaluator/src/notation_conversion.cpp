#include "project/expression_tokenizer.hpp"
#include <stack>
#include <vector>

#include <iostream>
using namespace std;

int get_precedence(char ch)
{
    if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/')
        return 2;
    else
        return 0;
}

int find_starting_point(const vector<token>& tokens)
{
    for (int i = tokens.size() - 1; i >= 0; --i)
    {
        if (tokens[i].c == '(')
        {
            return i + 1;
        }
    }
    return 0;
}

void infix_to_postfix_helper(vector<token>& tokens, stack<token>& s,
                             vector<token>::iterator& it)
{
    vector<token> postfix_tokens;
    vector<token> operators_buffer;

    while (it != end(tokens))
    {
        token t = *it;

        if (t.number)
        {
            s.push(t);
        }
        else if (is_operator(t.c))
        {
            int precedence = get_precedence(t.c);
            if (operators_buffer.empty())
            {
                operators_buffer.push_back(t);
            }
            else
            {
                int index = 0;
                index = find_starting_point(operators_buffer);
                cout << "starting point: " << index << endl;
                if (get_precedence(operators_buffer[index].c) == precedence)
                {
                    s.push(operators_buffer[index]);
                    operators_buffer[index] = t;
                }
                else if (precedence <=
                         get_precedence(operators_buffer.back().c))
                {
                    for (size_t i = index; i < operators_buffer.size(); i++)
                    {
                        s.push(operators_buffer[i]);
                    }
                    operators_buffer.clear();
                    operators_buffer.push_back(t);
                }
                else
                {
                    auto pos = std::find_if(operators_buffer.begin() + index,
                                            operators_buffer.end(),
                                            [t](auto s) { return s < t; });
                    operators_buffer.insert(pos, t);
                }
            }
        }
        else if (t.c == '(')
        {
            // Treat as marker for future closing parenthesis
            operators_buffer.push_back(t);
        }
        else if (t.c == ')')
        {
            // Pop until matching '(' is found
            while (operators_buffer.back().c != '(')
            {
                s.push(operators_buffer.back());
                operators_buffer.pop_back();
            }

            // If operators_buffer is empty, mismatched parenthesis
            if (operators_buffer.empty())
            {
                throw std::invalid_argument("Mismatched closing parenthesis");
            }

            // Discard the opening parenthesis '('
            operators_buffer.pop_back();
        }

        cout << "Operators: [";
        for (size_t i = 0; i < operators_buffer.size(); i++)
        {
            /* code */
            cout << operators_buffer[i].c << ", ";
        }
        cout << "]" << endl;
        ++it;
    }

    for (auto it = operators_buffer.begin(); it != operators_buffer.end(); ++it)
    {
        s.push(*it);
    }
}

vector<token> infix_to_postfix(vector<token>& tokens)
{
    stack<token> s;
    vector<token>::iterator it = begin(tokens);
    vector<token> posftix_tokens;
    infix_to_postfix_helper(tokens, s, it);
    while (!s.empty())
    {
        posftix_tokens.push_back(s.top());
        s.pop();
    }
    return posftix_tokens;
}