#include <string>
#include <vector>
bool matches_pattern(const std::string& line, const std::string& pattern, bool v_flag, bool i_flag);
std::string get_line_num_str(bool n_flag, int line_num);
std::string get_line_to_print(const std::string& line, bool n_flag,bool r_flag,
                              int line_num = 0, 
                              std::string file_path = "");

std::vector<std::string> grep_lines(const std::string& pattern,
                                    const std::string& file_path, bool n_flag,
                                    bool r_flag, bool v_flag, bool i_flag);
