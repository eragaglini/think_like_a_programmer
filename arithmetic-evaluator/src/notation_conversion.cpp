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

vector<token> infix_to_postfix_helper(vector<token>& tokens, stack<token>& s,
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
            // int last_operator_precedence =
            //     get_precedence(operators_buffer.back().c);
            // int first_operator_precedence =
            //     get_precedence(operators_buffer[0].c);

            if (operators_buffer.empty())
            {
                operators_buffer.push_back(t);
            }
            else if (get_precedence(operators_buffer[0].c) == precedence)
            {
                s.push(operators_buffer[0]);
                operators_buffer[0] = t;
            }
            else if (precedence <= get_precedence(operators_buffer.back().c))
            {
                // cout << "riga 51 operator: " << t.c << endl;
                for (size_t i = 0; i < operators_buffer.size(); i++)
                {
                    /* code */
                    s.push(operators_buffer[i]);
                }
                operators_buffer.clear();
                operators_buffer.push_back(t);
                
            }
            else
            {
                // cout << "operator: " << t.c << endl;

                auto pos = std::find_if(operators_buffer.begin(),
                                        operators_buffer.end(),
                                        [t](auto s) { return s < t; });
                operators_buffer.insert(pos, t);
            }

            // cout << "Operators: [";
            // for (size_t i = 0; i < operators_buffer.size(); i++)
            // {
            //     /* code */
            //     cout << operators_buffer[i].c << ", ";
            // }
            // cout << "]" << endl;
        }
        ++it;
    }
    for (auto it = operators_buffer.begin(); it != operators_buffer.end(); ++it)
    {
        // cout << "operatore: " << it->c << " pushato sullo stack" << endl;
        s.push(*it);
    }

    while (!s.empty())
    {
        postfix_tokens.push_back(s.top());
        s.pop();
    }
    return postfix_tokens;
}

vector<token> infix_to_postfix(vector<token>& tokens)
{
    stack<token> s;
    vector<token>::iterator it = begin(tokens);
    return infix_to_postfix_helper(tokens, s, it);
}