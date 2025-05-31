#include <filesystem>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

std::string get_module_file_path();

std::string get_executable_parent_path();

std::filesystem::path get_words_file_path();

std::vector<std::string> get_word_vector_from_file(std::ifstream& fs,
                                                   size_t length);
std::string get_word_from_file(std::ifstream& fs, size_t line_num);

std::string get_pattern_for_word(std::string word, char ch,
                                 std::string old_pattern);

std::unordered_map<std::string, std::vector<std::string>>
group_words_by_pattern(const std::vector<std::string>& wordVector, char ch,
                       std::string old_pattern);

std::pair<std::string, std::vector<std::string>> get_best_option_pair(
    const std::unordered_map<std::string, std::vector<std::string>>& map);
bool is_in_vector(std::vector<std::string>& vctr, std::string ch);

bool matches_pattern(std::string pattern, std::string word);

std::string get_best_guess(std::vector<std::string>& wordVector,
                           std::vector<std::string>& guessed_letters,
                           std::string& pattern);

std::vector<std::string>
update_word_vector(std::vector<std::string>& wordVector, 
    std::string& pattern,
                   std::vector<std::string>& guessed_letters);
