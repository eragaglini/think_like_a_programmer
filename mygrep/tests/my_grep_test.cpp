#include "project/my_grep.hpp"
#include <gtest/gtest.h>
#include <regex>

TEST(GetRegexPatternTest, CaseSensitivePattern)
{
    std::string pattern = "Hello";
    bool i_flag = false;
    std::regex expected_regex(pattern);
    std::regex actual_regex = get_regex_pattern(pattern, i_flag);
    EXPECT_EQ(expected_regex.mark_count(), actual_regex.mark_count());
    EXPECT_EQ(expected_regex.flags(), actual_regex.flags());
}

TEST(GetRegexPatternTest, CaseInsensitivePattern)
{
    std::string pattern = "Hello";
    bool i_flag = true;
    std::regex expected_regex(pattern, std::regex_constants::icase);
    std::regex actual_regex = get_regex_pattern(pattern, i_flag);
    EXPECT_EQ(expected_regex.mark_count(), actual_regex.mark_count());
    EXPECT_EQ(expected_regex.flags(), actual_regex.flags());
}

TEST(GetRegexPatternTest, InvalidPattern)
{
    std::string pattern = "("; // invalid pattern
    bool i_flag = false;
    EXPECT_THROW(get_regex_pattern(pattern, i_flag), std::regex_error);
}

TEST(GetRegexPatternTest, EmptyPattern)
{
    std::string pattern = "";
    bool i_flag = false;
    std::regex expected_regex(pattern);
    std::regex actual_regex = get_regex_pattern(pattern, i_flag);
    EXPECT_EQ(expected_regex.mark_count(), actual_regex.mark_count());
    EXPECT_EQ(expected_regex.flags(), actual_regex.flags());
}
#include "project/my_grep.hpp"
#include <gtest/gtest.h>
#include <regex>

TEST(MatchesPatternTest, MatchingPatternVFlagFalse)
{
    std::string line = "Hello World";
    std::regex pattern_regex("World");
    bool v_flag = false;
    EXPECT_TRUE(matches_pattern(line, pattern_regex, v_flag));
}

TEST(MatchesPatternTest, NonMatchingPatternVFlagFalse)
{
    std::string line = "Hello World";
    std::regex pattern_regex("Foo");
    bool v_flag = false;
    EXPECT_FALSE(matches_pattern(line, pattern_regex, v_flag));
}

TEST(MatchesPatternTest, MatchingPatternVFlagTrue)
{
    std::string line = "Hello World";
    std::regex pattern_regex("World");
    bool v_flag = true;
    EXPECT_FALSE(matches_pattern(line, pattern_regex, v_flag));
}

TEST(MatchesPatternTest, NonMatchingPatternVFlagTrue)
{
    std::string line = "Hello World";
    std::regex pattern_regex("Foo");
    bool v_flag = true;
    EXPECT_TRUE(matches_pattern(line, pattern_regex, v_flag));
}

TEST(MatchesPatternTest, EmptyPatternVFlagFalse)
{
    std::string line = "Hello World";
    std::regex pattern_regex("");
    bool v_flag = false;
    EXPECT_TRUE(matches_pattern(line, pattern_regex, v_flag));
}

TEST(MatchesPatternTest, EmptyPatternVFlagTrue)
{
    std::string line = "Hello World";
    std::regex pattern_regex("");
    bool v_flag = true;
    EXPECT_FALSE(matches_pattern(line, pattern_regex, v_flag));
}
TEST(MatchesPatternTest, EmptyLineVFlagFalse)
{
    std::string line = "";
    std::regex pattern_regex("World");
    bool v_flag = false;
    EXPECT_FALSE(matches_pattern(line, pattern_regex, v_flag));
}

TEST(MatchesPatternTest, EmptyLineVFlagTrue)
{
    std::string line = "";
    std::regex pattern_regex("World");
    bool v_flag = true;
    EXPECT_TRUE(matches_pattern(line, pattern_regex, v_flag));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}