#include <fstream>
#include <regex>
#include <string>
#include <vector>

#include "project/my_grep.hpp"

bool matches_pattern(const std::string& line, const std::string& pattern)
{

    std::regex regex_pattern{pattern};
    return std::regex_search(line, regex_pattern);
}

std::string get_line_num_str(bool n_flag, int line_num)
{
    return n_flag ? (std::to_string(line_num) + ":") : "";
}

std::string get_line_to_print(const std::string& line, bool n_flag, bool r_flag,
                              int line_num, std::string file_path)
{
    return (r_flag ? (file_path + ":") : "") + get_line_num_str(n_flag, line_num) +
           line;
}

std::vector<std::string> grep_lines(const std::string& pattern,
                                    const std::string& file_path, bool n_flag,
                                    bool r_flag, bool v_flag)
{
    std::ifstream ifs(file_path);
    std::vector<std::string> matches;
    if (!ifs.is_open())
    {
        throw std::runtime_error("Failed to open file");
    }
    // std::regex regex_pattern{pattern};
    std::string line;
    int line_num = 1;
    while (getline(ifs, line))
    {
        if (matches_pattern(line, pattern))
        {
            matches.push_back(get_line_to_print(line, n_flag, r_flag, line_num, file_path));
        }
        line_num++;
    }
    return matches;
}
