#include <filesystem>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

std::string get_module_file_path();
std::string get_executable_parent_path();
std::filesystem::path get_words_file_path(int length);
std::vector<std::string> get_word_vector_from_file(std::ifstream& fs);
std::string get_word_from_file(std::ifstream& fs, size_t line_num);
std::string get_pattern_for_word(std::string word, char ch,
                                 std::string old_pattern);
std::unordered_map<std::string, std::vector<std::string>>
group_words_by_pattern(const std::vector<std::string>& wordVector, char ch,
                       std::string old_pattern);
std::pair<std::string, std::vector<std::string>> get_best_option_pair(
    const std::unordered_map<std::string, std::vector<std::string>> map);