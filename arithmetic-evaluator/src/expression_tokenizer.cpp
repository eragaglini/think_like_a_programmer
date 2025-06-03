#include "project/expression_tokenizer.hpp" // Include your application's header
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

std::vector<token> tokenize_expression(const std::string& input)
{
    std::vector<token> tokens;
    std::string current_number_str;

    for (size_t i = 0; i < input.length(); ++i)
    {
        char ch = input[i];

        if (std::isspace(ch))
        {
            // Ignore whitespace
            continue;
        }

        if (std::isdigit(ch) || ch == '.')
        {
            // It's part of a number
            current_number_str += ch;
            // Check if it's the last character or the next character is not a
            // digit/dot
            if (i == input.length() - 1 ||
                (!std::isdigit(input[i + 1]) && input[i + 1] != '.'))
            {
                token num_token;
                num_token.number = true;
                try
                {
                    num_token.f = std::stof(current_number_str);
                }
                catch (const std::out_of_range& e)
                {
                    // Handle potential overflow/underflow if numbers are
                    // extremely large/small For simplicity, we'll just set it
                    // to 0 and log an error or throw
                    num_token.f = 0.0f;
                    // In a real application, you might log this error or throw
                    // a more specific exception.
                    std::cerr
                        << "Warning: Number out of range during tokenization: "
                        << current_number_str << std::endl;
                }
                catch (const std::invalid_argument& e)
                {
                    // Handle invalid number formats (e.g., "1.2.3")
                    num_token.f = 0.0f;
                    std::cerr
                        << "Error: Invalid number format during tokenization: "
                        << current_number_str << std::endl;
                    // You might want to throw an exception here to indicate a
                    // malformed expression.
                }
                tokens.push_back(num_token);
                current_number_str.clear(); // Reset for the next number
            }
        }
        else
        {
            // It's an operator or parenthesis
            if (!current_number_str.empty())
            {
                // If there was a number being built, add it first
                token num_token;
                num_token.number = true;
                try
                {
                    num_token.f = std::stof(current_number_str);
                }
                catch (const std::out_of_range& e)
                {
                    num_token.f = 0.0f;
                    std::cerr
                        << "Warning: Number out of range during tokenization: "
                        << current_number_str << std::endl;
                }
                catch (const std::invalid_argument& e)
                {
                    num_token.f = 0.0f;
                    std::cerr
                        << "Error: Invalid number format during tokenization: "
                        << current_number_str << std::endl;
                }
                tokens.push_back(num_token);
                current_number_str.clear();
            }

            token op_token;
            op_token.c = ch;
            op_token.number = false; // It's a character token
            tokens.push_back(op_token);
        }
    }

    // After the loop, if there's any remaining number string, add it
    if (!current_number_str.empty())
    {
        token num_token;
        num_token.number = true;
        try
        {
            num_token.f = std::stof(current_number_str);
        }
        catch (const std::out_of_range& e)
        {
            num_token.f = 0.0f;
            std::cerr << "Warning: Number out of range during tokenization: "
                      << current_number_str << std::endl;
        }
        catch (const std::invalid_argument& e)
        {
            num_token.f = 0.0f;
            std::cerr << "Error: Invalid number format during tokenization: "
                      << current_number_str << std::endl;
        }
        tokens.push_back(num_token);
    }

    return tokens;
}

std::string token_to_string(const token& t) {
    return t.number ? std::to_string(t.f) : std::string(1, t.c);
}

string token_vector_to_string(const vector<token>& tokens)
{
    stringstream ss;
    for (const auto& token : tokens)
    {
        if (token.number)
        {
            ss << token.f;
        }
        else
        {
            ss << token.c;
        }
    }

    return ss.str();
}
