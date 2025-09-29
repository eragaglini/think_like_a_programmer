#include <fstream>
// #include <regex> // Already included in .hpp
// #include <string> // Already included in .hpp
// #include <vector> // Already included in .hpp
// #include <istream> // Already included in .hpp

#include "project/my_grep.hpp"

// REF_CHANGE: Simplified return for get_regex_pattern
std::regex get_regex_pattern(const std::string& pattern, bool i_flag)
{
    return i_flag ? std::regex(pattern, std::regex_constants::icase) : std::regex(pattern);
}

// REF_CHANGE: matches_pattern now takes a const std::regex&
bool matches_pattern(const std::string& line, const std::regex& pattern_regex, bool v_flag)
{
    return v_flag ? !std::regex_search(line, pattern_regex)
                  : std::regex_search(line, pattern_regex);
}

std::string get_line_num_str(bool n_flag, int line_num)
{
    return n_flag ? (std::to_string(line_num) + ":") : "";
}

// REF_CHANGE: get_line_to_print now uses file_path_prefix directly
std::string get_line_to_print(const std::string& line, bool n_flag, int line_num,
                              const std::string& file_path_prefix)
{
    std::string prefix = "";
    if (!file_path_prefix.empty()) {
        prefix = file_path_prefix + ":";
    }
    return prefix + get_line_num_str(n_flag, line_num) + line;
}

// REF_CHANGE: New function to process any input stream
std::vector<std::string> process_stream_for_matches(
    std::istream& is,
    const std::regex& pattern_regex,
    const GrepOptions& options,
    const std::string& current_file_path)
{
    std::vector<std::string> matches;
    std::string line;
    int line_num = 1;
    while (std::getline(is, line))
    {
        // REF_CHANGE: Pass compiled regex and options
        if (matches_pattern(line, pattern_regex, options.v_flag))
        {
            // REF_CHANGE: Determine if filename prefix is needed based on current_file_path
            matches.push_back(
                get_line_to_print(line, options.n_flag, line_num, current_file_path));
        }
        line_num++;
    }
    return matches;
}

// REF_CHANGE: Removed the old grep_lines function as its functionality is now
// handled by process_stream_for_matches in conjunction with main.cpp's file opening logic.