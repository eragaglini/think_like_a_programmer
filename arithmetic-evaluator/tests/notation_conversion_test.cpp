#include "project/notation_conversion.hpp" // Include your application's header
#include "gtest/gtest.h"

TEST(InfixToPostfixTest, SimpleExpression)
{
    std::vector<token> infix = tokenize_expression("6+3*2/4-156+3*2/4-15");
    std::string expected_postfix = "632*4/+156-32*4/+15-";
    std::string actual_postfix =
        token_vector_to_string(infix_to_postfix(infix));
    EXPECT_EQ(expected_postfix, actual_postfix);
}

TEST(InfixToPostfixTest, NoOperators)
{
    std::vector<token> infix = tokenize_expression("123");
    std::string expected_postfix = "123";
    std::string actual_postfix =
        token_vector_to_string(infix_to_postfix(infix));
    EXPECT_EQ(expected_postfix, actual_postfix);
}

TEST(InfixToPostfixTest, SingleOperator)
{
    std::vector<token> infix = tokenize_expression("2+3");
    std::string expected_postfix = "23+";
    std::string actual_postfix =
        token_vector_to_string(infix_to_postfix(infix));
    EXPECT_EQ(expected_postfix, actual_postfix);
}

TEST(InfixToPostfixTest, MultipleOperators)
{
    std::vector<token> infix = tokenize_expression("2+3*4-5");
    std::string expected_postfix = "234*+5-";
    std::string actual_postfix =
        token_vector_to_string(infix_to_postfix(infix));
    EXPECT_EQ(expected_postfix, actual_postfix);
}

TEST(InfixToPostfixTest, Parentheses)
{
    std::vector<token> infix = tokenize_expression("(2+3)*4-5");
    std::string expected_postfix = "23+4*5-";
    std::string actual_postfix =
        token_vector_to_string(infix_to_postfix(infix));
    EXPECT_EQ(expected_postfix, actual_postfix);
}

TEST(InfixToPostfixTest, NestedParentheses)
{
    std::vector<token> infix = tokenize_expression("(2+(3*4))*5");
    std::string expected_postfix = "234*+5*";
    std::string actual_postfix =
        token_vector_to_string(infix_to_postfix(infix));
    EXPECT_EQ(expected_postfix, actual_postfix);
}

TEST(InfixToPostfixTest, ParenthesesWithMultipleOperators)
{
    std::vector<token> infix = tokenize_expression("(2+3)*(4-5)+6");
    std::string expected_postfix = "23+45-*6+";
    std::string actual_postfix =
        token_vector_to_string(infix_to_postfix(infix));
    EXPECT_EQ(expected_postfix, actual_postfix);
}

TEST(InfixToPostfixTest, ParenthesesAtStartAndEnd)
{
    std::vector<token> infix = tokenize_expression("((2+3)*4)");
    std::string expected_postfix = "23+4*";
    std::string actual_postfix =
        token_vector_to_string(infix_to_postfix(infix));
    EXPECT_EQ(expected_postfix, actual_postfix);
}

TEST(InfixToPostfixTest, MultipleParentheses)
{
    std::vector<token> infix = tokenize_expression("(2+3)*(4+5)-((6-7)*8)");
    std::string expected_postfix = "23+45+*67-8*-";
    std::string actual_postfix =
        token_vector_to_string(infix_to_postfix(infix));
    EXPECT_EQ(expected_postfix, actual_postfix);
}

TEST(InfixToPostfixTest, SingleNumber)
{
    std::vector<token> infix = tokenize_expression("5");
    std::string expected_postfix = "5";
    std::vector<token> actual_postfix = infix_to_postfix(infix);
    EXPECT_EQ(token_vector_to_string(actual_postfix), expected_postfix);
}