#include "project/posftix_evaluation.hpp" // Include your application's header
#include "gtest/gtest.h"

TEST(PostfixEvaluationTest, SimpleExpression)
{
    vector<token> tokens = tokenize_expression("6+3*2/4-156+3*2/4-15");
    double actual = eval_postfix(infix_to_postfix(tokens));
    EXPECT_EQ(actual, -162);
}

TEST(PostfixEvaluationTest, MultipleParentheses)
{
    vector<token> tokens = tokenize_expression("(2+3)*(4+5)-((6-7)*8)");
    double actual = eval_postfix(infix_to_postfix(tokens));
    EXPECT_EQ(actual, 53);
}

