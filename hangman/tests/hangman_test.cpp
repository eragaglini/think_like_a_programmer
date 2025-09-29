#include "project/hangman.hpp" // Include your application's header
#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <unordered_map>

TEST(CheckPatternTest, BasicTest)
{
    ASSERT_TRUE(get_pattern_for_word("paper", 'p', "_____") == "p_p__");
    ASSERT_TRUE(get_pattern_for_word("paper", 'p', "_____") == "p_p__");
    ASSERT_TRUE(get_pattern_for_word("banana", 'a', "______") == "_a_a_a");
    ASSERT_TRUE(get_pattern_for_word("hello", 'l', "_____") == "__ll_");
    ASSERT_TRUE(get_pattern_for_word("test", 'z', "____") == "____");
}

TEST(CheckPatternTest, OldPatternTest)
{
    ASSERT_TRUE(get_pattern_for_word("banana", 'a', "______") == "_a_a_a");
    ASSERT_TRUE(get_pattern_for_word("banana", 'b', "_a_a_a") == "ba_a_a");
    ASSERT_TRUE(get_pattern_for_word("test", 'z', "_es_") == "_es_");
}

// Utility for comparing two maps with sorted vector values
bool compareGroupMaps(
    const std::unordered_map<std::string, std::vector<std::string>>& a,
    const std::unordered_map<std::string, std::vector<std::string>>& b)
{
    if (a.size() != b.size())
        return false;
    for (const auto& pair : a)
    {
        auto it = b.find(pair.first);
        if (it == b.end())
            return false;

        std::vector<std::string> v1 = pair.second;
        std::vector<std::string> v2 = it->second;

        std::sort(v1.begin(), v1.end());
        std::sort(v2.begin(), v2.end());

        if (v1 != v2)
            return false;
    }
    return true;
}

TEST(GroupWordsByPatternTest, BasicTest)
{
    std::vector<std::string> input = {"paper", "piper", "apple", "pizza",
                                      "level"};
    char ch = 'p';

    std::unordered_map<std::string, std::vector<std::string>> expected = {
        {"p_p__", {"paper", "piper"}},
        {"_pp__", {"apple"}},
        {"p____", {"pizza"}},
        {"_____", {"level"}}};

    auto result = group_words_by_pattern(input, ch, "_____");
    EXPECT_TRUE(compareGroupMaps(result, expected));
}

TEST(GroupWordsByPatternTest, AllSamePattern)
{
    std::vector<std::string> input = {"gap", "gag", "gas"};
    char ch = 'g';

    std::unordered_map<std::string, std::vector<std::string>> expected = {
        {"g__", {"gap", "gas"}}, {"g_g", {"gag"}}};

    auto result = group_words_by_pattern(input, ch, "___");
    EXPECT_TRUE(compareGroupMaps(result, expected));
}

TEST(GroupWordsByPatternTest, NoCharacterMatch)
{
    std::vector<std::string> input = {"hello", "world"};
    char ch = 'z';

    std::unordered_map<std::string, std::vector<std::string>> expected = {
        {"_____", {"hello"}},
        {"_____", {"world"}} // This will overwrite the previous entry!
    };

    auto result = group_words_by_pattern(input, ch, "_____");

    // The expected map must group both words under the same key
    std::unordered_map<std::string, std::vector<std::string>>
        correctedExpected = {{"_____", {"hello", "world"}}};

    EXPECT_TRUE(compareGroupMaps(result, correctedExpected));
}

TEST(GetBestOptionTest, BasicTest)
{
    std::vector<std::string> input = {"paper", "piper", "apple", "pizza",
                                      "level"};
    char ch = 'p';

    std::pair<std::string, std::vector<std::string>> expected = {
        "p_p__", {"paper", "piper"}};

    auto result = group_words_by_pattern(input, ch, "_____");
    EXPECT_TRUE(get_best_option_pair(result) == expected);

    input = {"gap", "gag", "gas"};
    ch = 'g';

    expected = {"g__", {"gap", "gas"}};

    result = group_words_by_pattern(input, ch, "___");
    EXPECT_TRUE(get_best_option_pair(result) == expected);
}

TEST(IsInVectorTest, BasicTest)
{
    std::vector<std::string> input = {};
    std::string ch = "p";
    EXPECT_FALSE(is_in_vector(input, ch));
    input = {"p", "i", "a", "z", "l"};
    ch = "p";
    EXPECT_TRUE(is_in_vector(input, ch));

    input = {"p", "g", "s"};
    ch = "i";
    EXPECT_FALSE(is_in_vector(input, ch));
}

TEST(MatechesPatternTest, BasicTest)
{
    std::vector<std::string> found_letters = {"p"};
    std::vector<std::string> input = {"paper", "piper", "apple", "pizza",
                                      "level"};
    std::string pattern = "p_p__";
    std::string word = "paper";
    EXPECT_TRUE(matches_pattern(pattern, word));
    pattern = "pape_";
    EXPECT_TRUE(matches_pattern(pattern, word));
    pattern = "p___";
    EXPECT_FALSE(matches_pattern(pattern, word));

    pattern = "p_p_";
    EXPECT_FALSE(matches_pattern(pattern, "pizza"));
    EXPECT_TRUE(matches_pattern("_____", word));

}

TEST(GetBestGuessTest, BasicTest)
{
    std::vector<std::string> guessed_letters = {"p", "q", "g"};
    std::vector<std::string> input = {"paper", "piper", "apple", "pizza",
                                      "level"};
    std::string pattern = "p_p__";
    std::string word = "paper";
    std::string result =
        get_best_guess(input, guessed_letters, pattern);
    EXPECT_TRUE(result == "a");
    pattern = "pap__";
    guessed_letters = {"p", "q", "g", "a"};
    result = get_best_guess(input, guessed_letters, pattern);
    EXPECT_TRUE(result == "e");

    pattern = "pape_";
    guessed_letters = {"p", "q", "g", "a", "e"};
    result = get_best_guess(input, guessed_letters, pattern);
    EXPECT_TRUE(result == "r");
}

TEST(UpdateWordVectorTest, BasicTest)
{
    std::vector<std::string> found_letters = {"p"};
    std::vector<std::string> guessed_letters = {"p", "q", "g"};
    std::vector<std::string> input = {"paper", "piper", "apple", "pizza",
                                      "level"};
    std::string pattern = "p_p__";
    
    std::vector<std::string> expected = {"paper", "piper"};
    std::vector<std::string> result = update_word_vector(input, pattern, guessed_letters);
    
    EXPECT_TRUE(result == expected);
}

// You'll need a main function to run the tests.
// Google Test provides a default main function for convenience.
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}