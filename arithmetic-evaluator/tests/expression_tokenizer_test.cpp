#include "gtest/gtest.h"
#include "project/expression_tokenizer.hpp"

TEST(ExpressionTokenizerTest, EmptyStringInput) {
    std::string input = "";
    std::vector<token> expected_output = {};
    std::vector<token> actual_output = tokenize_expression(input);
    EXPECT_EQ(token_vector_to_string(expected_output), token_vector_to_string(actual_output));
}

TEST(ExpressionTokenizerTest, SingleNumberInput) {
    std::string input = "123";
    std::vector<token> expected_output = {{true, 123.0f, '\0'}};
    std::vector<token> actual_output = tokenize_expression(input);
    EXPECT_EQ(token_vector_to_string(expected_output), token_vector_to_string(actual_output));
}

TEST(ExpressionTokenizerTest, SingleOperatorInput) {
    std::string input = "+";
    std::vector<token> expected_output = {{false, 0.0f, '+'}};
    std::vector<token> actual_output = tokenize_expression(input);
    EXPECT_EQ(token_vector_to_string(expected_output), token_vector_to_string(actual_output));
}

TEST(ExpressionTokenizerTest, MultipleNumbersAndOperatorsInput) {
    std::string input = "123+456*789";
    std::vector<token> expected_output = {{true, 123.0f, '\0'}, {false, 0.0f, '+'}, {true, 456.0f, '\0'}, {false, 0.0f, '*'}, {true, 789.0f, '\0'}};
    std::vector<token> actual_output = tokenize_expression(input);
    EXPECT_EQ(token_vector_to_string(expected_output), token_vector_to_string(actual_output));
}
