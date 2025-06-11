#include <fstream>
#include <gtest/gtest.h>
#include <regex>

#include "project/my_grep.hpp" // your function declaration

TEST(GrepTest, BasicMatch)
{
    std::ofstream ofs("testfile.txt");
    ofs << "hello world\n";
    ofs << "goodbye world\n";
    ofs.close();

    auto result = grep_lines("hello", "testfile.txt");
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "hello world");
}

TEST(GrepTest, NoMatches)
{
    std::ofstream ofs("testfile.txt");
    ofs << "cat\ndog\n";
    ofs.close();

    auto result = grep_lines("fish", "testfile.txt");
    EXPECT_TRUE(result.empty());
}

TEST(GrepTest, SpecialRegexCharacters)
{
    std::ofstream ofs("testfile.txt");
    ofs << "(parentheses)\n[brackets]\n.dot\n";
    ofs.close();

    auto result = grep_lines("\\(parentheses\\)", "testfile.txt");
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "(parentheses)");
}

TEST(GrepTest, InvalidRegexThrows)
{
    std::ofstream ofs("testfile.txt");
    ofs << "line\n";
    ofs.close();

    EXPECT_THROW(
        [] { grep_lines("(", "testfile.txt"); }(),
        std::regex_error
    );
}


TEST(GrepTest, FileNotFoundThrows)
{
    EXPECT_THROW(
        [] { grep_lines("anything", "nonexistent.txt"); }(),
        std::runtime_error
    );
}
