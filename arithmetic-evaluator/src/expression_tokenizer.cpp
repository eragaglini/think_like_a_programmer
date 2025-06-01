#include "project/expression_tokenizer.hpp" // Include your application's header
#include <algorithm>                        // for std::find, std::remove_if
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

void flush_buffer(vector<char>& buffer, vector<token>& tokens)
{
    string s(buffer.begin(), buffer.end());
    if (!s.empty())
    {
        token t;
        t.f = stof(s);
        t.number = true;
        tokens.push_back(t);
    }
    buffer.clear();
}

bool is_operator(char ch)
{
    return (ch == '%' || ch == '/' || ch == '*' || ch == '+' || ch == '-');
}

bool is_parenthesis(char ch) { return (ch == '(' || ch == ')'); }

/**
 * @brief Tokenize an expression string into a vector of tokens
 *
 * This function takes a string expression and breaks it down into a vector of
 * tokens. Tokens are either numbers or operators. The function handles decimal
 * points and parentheses.
 *
 * @param input The input expression as a string
 * @return A vector of tokens representing the input expression
 * @throws std::invalid_argument if the input expression is invalid
 */
vector<token> tokenize_expression(const string& input)
{
    // Work on a copy to avoid modifying the original input
    string sanitized_input = input;

    // Remove all whitespaces
    sanitized_input.erase(
        remove_if(sanitized_input.begin(), sanitized_input.end(), ::isspace),
        sanitized_input.end());

    vector<token> result;
    vector<char> digit_buffer;
    int parenthesis_count = 0;
    bool last_was_operator = false;

    for (auto it = sanitized_input.begin(); it != sanitized_input.end(); ++it)
    {
        char ch = *it;

        if (isdigit(ch) || ch == '.') // Handle numbers, including decimals
        {
            digit_buffer.push_back(ch);

            // Look ahead to collect subsequent digits or a single decimal point
            while (
                // Check if we're not at the end of the string
                it + 1 != sanitized_input.end() &&

                // Check if the next character is a digit or a decimal point
                (isdigit(*(it + 1)) || // Next character is a digit
                 (*(it + 1) == '.' &&  // Next character is a decimal point
                  std::find(digit_buffer.begin(), digit_buffer.end(), '.') ==
                      digit_buffer
                          .end() // And no decimal point has been seen before
                  )))
            {
                ++it;
                ch = *it;
                digit_buffer.push_back(ch);
            }

            flush_buffer(digit_buffer, result);
            last_was_operator = false;
        }
        else if (is_parenthesis(ch))
        {
            token t;
            t.c = ch;
            t.number = false;
            result.push_back(t);

            if (ch == '(')
            {
                parenthesis_count++;
            }
            else if (ch == ')')
            {
                if (parenthesis_count == 0)
                {
                    throw std::invalid_argument(
                        "Unmatched closing parenthesis in input");
                }
                parenthesis_count--;
            }

            last_was_operator = false; // Parentheses don’t count as operators
        }
        else if (is_operator(ch))
        {
            if (last_was_operator)
            {
                throw std::invalid_argument(
                    "Two consecutive operators in input");
            }

            token t;
            t.c = ch;
            t.number = false;
            result.push_back(t);

            last_was_operator = true;
        }
        else
        {
            throw std::invalid_argument("Invalid character '" + string(1, ch) +
                                        "' in input");
        }
    }

    if (parenthesis_count != 0)
    {
        throw std::invalid_argument(
            "Unbalanced parentheses in input expression");
    }

    return result;
}
