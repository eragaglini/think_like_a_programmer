#include <string>
#include <filesystem>

std::string getModuleFilePath();
std::string getExecutableParentPath();
std::filesystem::path getWordsFilePath();
std::string get_word_from_file(std::ifstream& fs, size_t line_num);
