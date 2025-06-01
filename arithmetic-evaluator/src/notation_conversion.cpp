#include "project/expression_tokenizer.hpp"
#include <stack>
#include <vector>

#include <iostream>
using namespace std;

int get_precedence(token t)
{
    if (t.c == '+' || t.c == '-')
        return 1;
    else if (t.c == '*' || t.c == '/')
        return 2;
    else
        return 0;
}

bool has_higher_priority(token ta, token tb)
{
    return get_precedence(ta) >= get_precedence(tb);
}

vector<token> infix_to_postfix(const vector<token>& tokens)
{
    stack<token> s;
    vector<token> postfix_tokens;
    for (auto it = begin(tokens); it != end(tokens); ++it)
    {
        token t = *it;

        if (t.number)
        {
            s.push(t);
        }
        else if (is_operator(t.c))
        {
            token nt = *(++it);
            s.push(nt);
            if ((it + 1) == end(tokens))
            {
                s.push(t);
                break;
            }
            else if (!has_higher_priority(t, *(it + 1)))
            {
                vector<token> rest = std::vector<token>(it + 1, tokens.end());
                rest = infix_to_postfix(rest);
                for (auto it = rest.rbegin(); it != rest.rend(); ++it)
                {
                    s.push(*it);
                }
                s.push(t);
                break;
            }
            s.push(t);
        }
    }
    while (!s.empty())
    {
        postfix_tokens.push_back(s.top());
        s.pop();
    }
    return postfix_tokens;
}