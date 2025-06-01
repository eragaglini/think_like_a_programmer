#include "project/expression_tokenizer.hpp" // Include your application's header
#include "gtest/gtest.h"


// Verifies that the default constructor initializes a token as a non-number
// with a character value of 0.
TEST(TokenTests, DefaultConstructorInitializesCorrectly)
{
    token t;
    EXPECT_FALSE(t.number);
    EXPECT_EQ(t.c, 0);
}

// Verifies that a token can be assigned a float value, and that the
// value can be correctly accessed after assignment.
TEST(TokenTests, CanAssignFloatValue)
{
    token t;
    t.f = 3.14159f;
    t.number = true;
    EXPECT_FLOAT_EQ(t.f, 3.14159f);
    EXPECT_TRUE(t.number);
}

// Verifies that a token can switch between holding a character and a float
// value, and that the type and value are correctly updated and accessed after
// each assignment.
TEST(TokenTests, CanSwitchBetweenTypes)
{
    token t;
    t.c = '*';
    t.number = false;
    EXPECT_EQ(t.c, '*');
    EXPECT_FALSE(t.number);
    t.f = 100.0f;
    t.number = true;
    EXPECT_FLOAT_EQ(t.f, 100.0f);
    EXPECT_TRUE(t.number);
    t.c = '/';
    t.number = false;
    EXPECT_EQ(t.c, '/');
    EXPECT_FALSE(t.number);
}

TEST(TokenizeExpressionFunctionTest, BasicTest)
{
    // Test case 1: Single number
    std::string input = "123";
    std::vector<token> expected_output;
    token t;
    t.f = 123;
    t.c = 0;
    t.number = true;
    expected_output.push_back(t);
    std::vector<token> actual_output = tokenize_expression(input);
    EXPECT_EQ(expected_output, actual_output);
    // Test case 2: Number followed by operator and another number
    input = "123+456";

    token t2;
    t2.number = false;
    t2.c = '+';
    expected_output.push_back(t2);

    token t3;
    t3.f = 456;
    t3.c = 0;
    t3.number = true;
    expected_output.push_back(t3);
    actual_output = tokenize_expression(input);
    EXPECT_EQ(expected_output, actual_output);
    expected_output = {};
}

TEST(TokenizeExpressionFunctionTest, SingleOperatorTest)
{
    // Test case: Single operator
    std::string input = "+";
    std::vector<token> expected_output;
    token t;
    t.number = false;
    t.c = '+';
    expected_output.push_back(t);
    std::vector<token> actual_output = tokenize_expression(input);
    EXPECT_EQ(expected_output, actual_output);
}

TEST(TokenizeExpressionFunctionTest, MultipleOperatorsTest)
{
    // Test case: Multiple operators
    std::string input = "+-*/";
    EXPECT_THROW(tokenize_expression(input), std::invalid_argument);
}

TEST(TokenizeExpressionFunctionTest, DecimalNumberTest)
{
    // Test case: Decimal number
    std::string input = "123.456";
    std::vector<token> expected_output;
    token t;
    t.f = 123.456;
    t.c = 0;
    t.number = true;
    expected_output.push_back(t);
    std::vector<token> actual_output = tokenize_expression(input);
    EXPECT_EQ(expected_output, actual_output);
}

TEST(TokenizeExpressionFunctionTest, NumberWithLeadingZeroTest)
{
    // Test case: Number with leading zero
    std::string input = "0123";
    std::vector<token> expected_output;
    token t;
    t.f = 123;
    t.c = 0;
    t.number = true;
    expected_output.push_back(t);
    std::vector<token> actual_output = tokenize_expression(input);
    EXPECT_EQ(expected_output, actual_output);
}

TEST(TokenizeExpressionFunctionTest, EmptyStringTest)
{
    // Test case: Empty string
    std::string input = "";
    std::vector<token> expected_output;
    std::vector<token> actual_output = tokenize_expression(input);
    EXPECT_EQ(expected_output, actual_output);
}

TEST(TokenizeExpressionFunctionTest, InvalidInputTest)
{
    // Test case: Invalid input (non-numeric character)
    std::string input = "123abc";
    EXPECT_THROW(tokenize_expression(input), std::invalid_argument);
}

TEST(TokenizeExpressionFunctionTest, ParenthesesTest)
{
    // Test case: Parentheses
    std::string input = "(123)";
    std::vector<token> expected_output;
    token t1;
    t1.number = false;
    t1.c = '(';
    expected_output.push_back(t1);
    token t2;
    t2.f = 123;
    t2.c = 0;
    t2.number = true;
    expected_output.push_back(t2);
    token t3;
    t3.number = false;
    t3.c = ')';
    expected_output.push_back(t3);
    std::vector<token> actual_output = tokenize_expression(input);
    EXPECT_EQ(expected_output, actual_output);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}