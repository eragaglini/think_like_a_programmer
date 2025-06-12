#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex> // REF_CHANGE: Include regex here for pre-compilation
#include <string>
#include <unistd.h> // For getopt, optarg, optind, opterr, optopt
#include <utility>
#include <vector>

#include "project/my_grep.hpp" // Assumed to contain grep_lines function

namespace fs = std::filesystem;

// Main function
int main(int argc, char* argv[])
{
    // --- 1. Initialize flags and variables ---
    // REF_CHANGE: Use GrepOptions struct
    GrepOptions options;

    opterr = 0; // Disable getopt's default error messages

    // --- 2. Parse command-line options using getopt ---
    int c;
    while ((c = getopt(argc, argv, "rvni")) != -1)
    {
        switch (c)
        {
            case 'r':
                options.r_flag = true; // Still need a specific r_flag here for
                                       // recursive logic
                break;
            case 'v':
                options.v_flag = true;
                break;
            case 'n':
                options.n_flag = true;
                break;
            case 'i':
                options.i_flag = true;
                break;
            case '?':
                if (isprint(optopt))
                {
                    std::cerr << "Unknown option `-"
                              << static_cast<char>(optopt) << "'." << std::endl;
                }
                else
                {
                    std::cerr << "Unknown option character `\\x" << std::hex
                              << static_cast<int>(optopt) << "'." << std::endl;
                }
                return 1; // Indicate error
            default:
                std::cerr << "Unknown error during option parsing."
                          << std::endl;
                return 1; // Indicate error
        }
    }

    // --- 3. Extract pattern and file/directory paths ---
    std::string search_pattern;
    std::vector<std::string> paths_to_search;

    if (optind < argc)
    {
        search_pattern = argv[optind];
        optind++; // Move past the pattern to get to the file/directory
                  // arguments
    }
    else
    {
        std::cerr << "Usage: " << argv[0]
                  << " [options] <pattern> [file/directory...]\n";
        return 2; // Standard exit code for usage errors
    }

    // REF_CHANGE: Pre-compile the regex once
    std::regex compiled_pattern =
        get_regex_pattern(search_pattern, options.i_flag);

    // All remaining non-option arguments are paths to search
    for (int i = optind; i < argc; ++i)
    {
        paths_to_search.emplace_back(argv[i]);
    }

    if (paths_to_search.empty() && options.r_flag)
    { // If recursive and no paths given, search current dir
        paths_to_search.push_back(".");
    }

    // --- 4. Store all found matches ---
    std::vector<std::string> all_matches;

    // --- 5. Process each specified path ---
    // REF_CHANGE: Only iterate if paths_to_search is not empty.
    // If it's empty, we'll process stdin later.
    if (!paths_to_search.empty())
    {
        // REF_CHANGE: Determine if filename prefix should be printed
        bool print_filename_prefix_for_this_match =
            paths_to_search.size() > 1 || options.r_flag;

        for (const std::string& current_path_str : paths_to_search)
        {
            const fs::path path = fs::path(current_path_str);
            std::error_code ec; // For non-throwing filesystem operations

            // Check path status and existence
            fs::file_status status = fs::status(path, ec);

            if (ec)
            {
                // Error getting status (e.g., path doesn't exist, permissions
                // issue)
                std::cerr << "mygrep: " << path.string() << ": " << ec.message()
                          << std::endl;
                ec.clear(); // Clear the error code for subsequent checks
                continue;   // Move to the next path
            }

            if (fs::is_regular_file(status))
            {
                std::ifstream file_stream(path); // Open the file stream
                if (file_stream.is_open())
                {
                    std::string prefix = print_filename_prefix_for_this_match
                                             ? path.string()
                                             : "";
                    // REF_CHANGE: Use process_stream_for_matches
                    std::vector<std::string> file_matches =
                        process_stream_for_matches(
                            file_stream, compiled_pattern, options, prefix);
                    all_matches.insert(all_matches.end(), file_matches.begin(),
                                       file_matches.end());
                }
                else
                {
                    std::cerr << "mygrep: " << path.string()
                              << ": Permission denied" << std::endl;
                }
            }
            else if (fs::is_directory(status))
            {
                if (!options.r_flag) // REF_CHANGE: Use options.r_flag
                {
                    // If not recursive, treat directories as an error (like
                    // grep)
                    std::cerr << "mygrep: " << path.string()
                              << ": Is a directory" << std::endl;
                }
                else
                {
                    for (const auto& dir_entry :
                         fs::recursive_directory_iterator(path, ec))
                    {
                        if (ec)
                        {
                            std::cerr << "Error iterating into "
                                      << dir_entry.path().string() << ": "
                                      << ec.message() << std::endl;
                            ec.clear();
                            continue;
                        }
                        if (fs::is_regular_file(dir_entry.path()))
                        {
                            std::ifstream file_stream(dir_entry.path());
                            if (file_stream.is_open())
                            {
                                // REF_CHANGE: Use process_stream_for_matches
                                std::vector<std::string> file_matches =
                                    process_stream_for_matches(
                                        file_stream, compiled_pattern, options,
                                        dir_entry.path().string());
                                all_matches.insert(all_matches.end(),
                                                   file_matches.begin(),
                                                   file_matches.end());
                            }
                            else
                            {
                                std::cerr
                                    << "mygrep: " << dir_entry.path().string()
                                    << ": Permission denied" << std::endl;
                            }
                        }
                    }
                }
            }
            else
            {
                std::cerr
                    << "mygrep: " << path.string()
                    << ": Not a regular file or directory (or unhandled type)"
                    << std::endl;
            }
        }
    }

    // -- 6. Process data read from standard input ----
    // REF_CHANGE: Only process stdin if no paths were provided at all.
    if (paths_to_search.empty())
    {
        // REF_CHANGE: Use process_stream_for_matches for stdin
        std::vector<std::string> stdin_matches = process_stream_for_matches(
            std::cin, compiled_pattern, options,
            ""); // Provide an empty string for file_path_prefix
        all_matches.insert(all_matches.end(), stdin_matches.begin(),
                           stdin_matches.end());
    }

    // --- 7. Print all collected matches to standard output ---
    for (const std::string& match_line : all_matches)
    {
        std::cout << match_line << std::endl;
    }

    // --- 8. Return appropriate exit code ---
    return (all_matches.empty() ? 1 : 0);
}