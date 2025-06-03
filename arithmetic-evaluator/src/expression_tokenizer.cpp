#include "project/expression_tokenizer.hpp" // Include your application's header
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/**
 * Tokenize an arithmetic expression into a vector of tokens.
 *
 * @param input Arithmetic expression string to tokenize.
 * @return Vector of tokens representing the expression.
 */
std::vector<token> tokenize_expression(const std::string& input)
{
    std::vector<token> tokens;
    std::string current_number_str;

    for (size_t i = 0; i < input.length(); ++i)
    {
        char ch = input[i];

        // Ignore whitespace
        if (std::isspace(ch))
        {
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

/**
 * Converts a single token to a string. The string is created by appending
 * the string representation of the token to a stringstream.
 * The string representation of a token is either the number value as a string
 * if the token is a number, or the character value as a single character string
 * if the token is a character token.
 * 
 * @param t The token to convert to a string.
 * @return The string representation of the token.
 */
std::string token_to_string(const token& t) {
    return t.number ? std::to_string(t.f) : std::string(1, t.c);
}

/**
 * Converts a vector of tokens to a string. The string is created by appending
 * the string representation of each token in the vector to a stringstream.
 * The string representation of a token is either the number value as a string
 * if the token is a number, or the character value as a single character string
 * if the token is a character token.
 * 
 * @param tokens The vector of tokens to convert to a string.
 * @return The string representation of the vector of tokens.
 */
string token_vector_to_string(const vector<token>& tokens)
{
    stringstream ss;
    // Iterate over each token in the vector
    for (const auto& token : tokens)
    {
        // If the token is a number, append its number value as a string to the stringstream
        if (token.number)
        {
            ss << token.f;
        }
        // If the token is a character token, append its character value as a single character string to the stringstream
        else
        {
            ss << token.c;
        }
    }

    // Return the string representation of the vector of tokens
    return ss.str();
}
