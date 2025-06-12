#include "project/my_grep.hpp"
#include <gtest/gtest.h>

TEST(MatchesPatternTest, CaseInsensitiveMatching)
{
    std::string line = "Hello World";
    std::string pattern = "hello";
    bool i_flag = true;
    bool v_flag = false;
    EXPECT_TRUE(matches_pattern(line, pattern, v_flag, i_flag));
}

TEST(MatchesPatternTest, CaseSensitiveMatching)
{
    std::string line = "Hello World";
    std::string pattern = "hello";
    bool i_flag = false;
    bool v_flag = false;
    EXPECT_FALSE(matches_pattern(line, pattern, v_flag, i_flag));
}

TEST(MatchesPatternTest, InvertMatchFlag)
{
    std::string line = "Hello World";
    std::string pattern = "Hello";
    bool i_flag = false;
    bool v_flag = true;
    EXPECT_FALSE(matches_pattern(line, pattern, v_flag, i_flag));
}

TEST(MatchesPatternTest, SimplePatternMatching)
{
    std::string line = "Hello World";
    std::string pattern = "World";
    bool i_flag = false;
    bool v_flag = false;
    EXPECT_TRUE(matches_pattern(line, pattern, v_flag, i_flag));
}

TEST(MatchesPatternTest, ComplexPatternMatching)
{
    std::string line = "Hello, World!";
    std::string pattern = "[^a-zA-Z0-9]+";
    bool i_flag = false;
    bool v_flag = false;
    EXPECT_TRUE(matches_pattern(line, pattern, v_flag, i_flag));
}

TEST(MatchesPatternTest, NonMatchingSimplePattern)
{
    std::string line = "Hello World";
    std::string pattern = "Foo";
    bool i_flag = false;
    bool v_flag = false;
    EXPECT_FALSE(matches_pattern(line, pattern, v_flag, i_flag));
}

TEST(MatchesPatternTest, NonMatchingComplexPattern)
{
    std::string line = "Hello World";
    std::string pattern = "[^a-zA-Z0-9 ]+"; // add space to the character class
    bool i_flag = false;
    bool v_flag = true;
    EXPECT_TRUE(matches_pattern(line, pattern, v_flag, i_flag));
}
TEST(GrepLinesTest, FileCannotBeOpened)
{
    std::string pattern = "test";
    std::string file_path = "non_existent_file.txt";
    bool n_flag = false;
    bool r_flag = false;
    bool v_flag = false;
    bool i_flag = false;
    EXPECT_THROW(grep_lines(pattern, file_path, n_flag, r_flag, v_flag, i_flag),
                 std::runtime_error);
}
TEST(GrepLinesTest, PatternNotFound)
{
    std::string pattern = "test";
    std::string file_path = "testfile.txt";
    bool n_flag = false;
    bool r_flag = false;
    bool v_flag = false;
    bool i_flag = false;
    std::vector<std::string> expected;
    std::vector<std::string> actual =
        grep_lines(pattern, file_path, n_flag, r_flag, v_flag, i_flag);
    EXPECT_EQ(expected, actual);
}
TEST(GrepLinesTest, PatternFound)
{
    std::string pattern = "line";
    std::string file_path = "testfile.txt";
    bool n_flag = false;
    bool r_flag = false;
    bool v_flag = false;
    bool i_flag = false;
    std::vector<std::string> expected = {"line"};
    std::vector<std::string> actual =
        grep_lines(pattern, file_path, n_flag, r_flag, v_flag, i_flag);
    EXPECT_EQ(expected, actual);
}
TEST(GrepLinesTest, PatternFoundWithNFlag)
{
    std::string pattern = "line";
    std::string file_path = "testfile.txt";
    bool n_flag = true;
    bool r_flag = false;
    bool v_flag = false;
    bool i_flag = false;
    std::vector<std::string> expected = {"1:line"};
    std::vector<std::string> actual =
        grep_lines(pattern, file_path, n_flag, r_flag, v_flag, i_flag);
    EXPECT_EQ(expected, actual);
}
TEST(GrepLinesTest, PatternFoundWithRFlag)
{
    std::string pattern = "line";
    std::string file_path = "testfile.txt";
    bool n_flag = false;
    bool r_flag = true;
    bool v_flag = false;
    bool i_flag = false;
    std::vector<std::string> expected = {"testfile.txt:line"};
    std::vector<std::string> actual =
        grep_lines(pattern, file_path, n_flag, r_flag, v_flag, i_flag);
    EXPECT_EQ(expected, actual);
}
TEST(GrepLinesTest, PatternFoundWithVFlag)
{
    std::string pattern = "test";
    std::string file_path = "testfile.txt";
    bool n_flag = false;
    bool r_flag = false;
    bool v_flag = true;
    bool i_flag = false;
    std::vector<std::string> expected = {"line"};
    std::vector<std::string> actual =
        grep_lines(pattern, file_path, n_flag, r_flag, v_flag, i_flag);
    EXPECT_EQ(expected, actual);
}
TEST(GrepLinesTest, PatternFoundWithIFlag)
{
    std::string pattern = "LiNe";
    std::string file_path = "testfile.txt";
    bool n_flag = false;
    bool r_flag = false;
    bool v_flag = false;
    bool i_flag = true;
    std::vector<std::string> expected = {"line"};
    std::vector<std::string> actual =
        grep_lines(pattern, file_path, n_flag, r_flag, v_flag, i_flag);
    EXPECT_EQ(expected, actual);
}
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}