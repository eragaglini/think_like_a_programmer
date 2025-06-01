#include "project/notation_conversion.hpp" // Include your application's header
#include "gtest/gtest.h"


// TEST(InfixToPostfixTest, SimpleExpression)
// {
//     std::vector<token> infix;
//     infix.push_back(token('2', true, 2));
//     infix.push_back(token('*', false, 0));
//     infix.push_back(token('3', true, 3));

//     std::vector<token> expected_postfix;
//     expected_postfix.push_back(token('*', false, 0));
//     expected_postfix.push_back(token('3', true, 3));
//     expected_postfix.push_back(token('2', true, 2));

//     std::vector<token> postfix = infix_to_postfix(infix);
//     EXPECT_EQ(postfix, expected_postfix);
// }

// TEST(InfixToPostfixTest, SingleNumber)
// {
//     std::vector<token> infix;
//     infix.push_back(token('5', true, 5));

//     std::vector<token> expected_postfix;
//     expected_postfix.push_back(token('5', true, 5));

//     std::vector<token> postfix = infix_to_postfix(infix);
//     EXPECT_EQ(postfix, expected_postfix);
// }

// // TEST(InfixToPostfixTest, SingleOperator)
// // {
// //     std::vector<token> infix;
// //     infix.push_back(token('+', false, 0));

// //     std::vector<token> expected_postfix;
// //     expected_postfix.push_back(token('+', false, 0));

// //     std::vector<token> postfix = infix_to_postfix(infix);
// //     EXPECT_EQ(postfix, expected_postfix);
// // }

// TEST(InfixToPostfixTest, MultipleOperators)
// {
//     std::vector<token> infix;
//     infix.push_back(token('2', true, 2));
//     infix.push_back(token('+', false, 0));
//     infix.push_back(token('3', true, 3));
//     infix.push_back(token('*', false, 0));
//     infix.push_back(token('4', true, 4));

//     std::vector<token> expected_postfix;
//     expected_postfix.push_back(token('2', true, 2));
//     expected_postfix.push_back(token('3', true, 3));
//     expected_postfix.push_back(token('4', true, 4));
//     expected_postfix.push_back(token('*', false, 0));
//     expected_postfix.push_back(token('+', false, 0));

//     std::vector<token> postfix = infix_to_postfix(infix);

//     // Check that the numbers are in the correct order
//     EXPECT_EQ(postfix[0].f, 2);
//     EXPECT_EQ(postfix[1].f, 3);
//     EXPECT_EQ(postfix[2].f, 4);

//     // Check that the operators are in the correct order
//     EXPECT_EQ(postfix[3].c, '*');
//     EXPECT_EQ(postfix[4].c, '+');
// }

// TEST(InfixToPostfixTest, Division)
// {
//     std::vector<token> infix;
//     infix.push_back(token('6', true, 6));
//     infix.push_back(token('/', false, 0));
//     infix.push_back(token('2', true, 2));

//     std::vector<token> expected_postfix;
//     expected_postfix.push_back(token('6', true, 6));
//     expected_postfix.push_back(token('2', true, 2));
//     expected_postfix.push_back(token('/', false, 0));

//     std::vector<token> postfix = infix_to_postfix(infix);
//     EXPECT_EQ(postfix, expected_postfix);
// }

// TEST(InfixToPostfixTest, Multiplication)
// {
//     std::vector<token> infix;
//     infix.push_back(token('7', true, 7));
//     infix.push_back(token('*', false, 0));
//     infix.push_back(token('3', true, 3));

//     std::vector<token> expected_postfix;
//     expected_postfix.push_back(token('7', true, 7));
//     expected_postfix.push_back(token('3', true, 3));
//     expected_postfix.push_back(token('*', false, 0));

//     std::vector<token> postfix = infix_to_postfix(infix);
//     EXPECT_EQ(postfix, expected_postfix);
// }