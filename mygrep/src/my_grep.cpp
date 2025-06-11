#include <fstream>
#include <regex>
#include <string>
#include <vector>

#include "project/my_grep.hpp"

std::vector<std::pair<std::string, std::string>>
grep_lines(const std::string& pattern, const std::string& file_path,
           bool n_flag)
{
    std::ifstream ifs(file_path);
    std::vector<std::pair<std::string, std::string>> matches;
    if (!ifs.is_open())
    {
        throw std::runtime_error("Failed to open file");
    }
    std::regex regex_pattern{pattern};
    std::string line;
    int line_num = 1;
    while (getline(ifs, line))
    {
        if (std::regex_search(line, regex_pattern))
        {
            std::string line_num_str = n_flag ? (std::to_string(line_num) + ":") : "";
            matches.push_back({file_path + ":" + line_num_str, line});
        }
        line_num++;
    }
    return matches;
}
