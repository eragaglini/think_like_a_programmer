#include <string>
#include <vector>
#include <fstream>
#include <regex>

#include "project/my_grep.hpp"


std::vector<std::pair<std::string, std::string>> grep_lines(const std::string& pattern, const std::string& file_path)
{
    std::ifstream ifs(file_path);
    std::vector<std::string> matches;
    if (!ifs.is_open())
    {
        throw std::runtime_error("Failed to open file");
    }
    std::regex regex_pattern{pattern};
    std::string line;
    while (getline(ifs, line))
    {
        if (std::regex_search(line, regex_pattern))
        {
            matches.push_back(line);
        }
    }
    return matches;
}
