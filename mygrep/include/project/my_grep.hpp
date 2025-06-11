#include <string>
#include <utility>
#include <vector>

std::vector<std::pair<std::string, std::string>>
grep_lines(const std::string& pattern, const std::string& file_path, bool n_flag);
