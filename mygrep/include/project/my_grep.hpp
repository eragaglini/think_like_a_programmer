#ifndef MY_GREP_HPP
#define MY_GREP_HPP

#include <string>
#include <vector>
#include <regex> // For std::regex
#include <istream> // For std::istream&
#include <filesystem> // For fs::path

namespace fs = std::filesystem;

// REF_CHANGE: New struct to hold command-line options
struct GrepOptions {
    bool r_flag = false; // REF_CHANGE: Added r_flag for recursive search
    bool n_flag = false; // Line number
    bool v_flag = false; // Invert match
    bool i_flag = false; // Case-insensitive
    // Add other flags here as you implement them (e.g., bool count_flag = false;)
};

// REF_CHANGE: get_regex_pattern now creates the regex once
std::regex get_regex_pattern(const std::string& pattern, bool i_flag);

// REF_CHANGE: matches_pattern now takes a const std::regex&
bool matches_pattern(const std::string& line, const std::regex& pattern_regex, bool v_flag);

std::string get_line_num_str(bool n_flag, int line_num);

// REF_CHANGE: get_line_to_print now takes an explicit file_path_prefix
std::string get_line_to_print(const std::string& line, bool n_flag, int line_num,
                              const std::string& file_path_prefix = "");

// REF_CHANGE: New function to process any input stream (file or stdin)
std::vector<std::string> process_stream_for_matches(
    std::istream& is,
    const std::regex& pattern_regex, // Pre-compiled regex
    const GrepOptions& options,      // All flags bundled
    const std::string& current_file_path = "" // Optional: for printing filename prefix
);

#endif // MY_GREP_HPP