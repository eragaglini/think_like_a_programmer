#include <algorithm> // For std::copy or std::insert (less direct use here but good to include)
#include <cctype>     // For isprint
#include <filesystem> // C++17
#include <iostream>   // For std::cout, std::cerr
#include <string>     // For std::string
#include <unistd.h>   // For getopt, optarg, optind, opterr, optopt
#include <vector>     // For std::vector

#include "project/my_grep.hpp" // Assumed to contain grep_lines function

namespace fs = std::filesystem;

// Main function
int main(int argc, char* argv[])
{
    // --- 1. Initialize flags and variables ---
    bool r_flag = false; // Recursive search
    bool v_flag = false; // Invert match (not implemented in this example)
    bool i_flag = false; // Case-insensitive (not implemented in this example)

    opterr = 0; // Disable getopt's default error messages

    // --- 2. Parse command-line options using getopt ---
    int c;
    while ((c = getopt(argc, argv, "rvi:")) !=
           -1) // -i expects an argument, but your logic treats it as a flag
               // Changed to "rvi:" if 'i' is a flag, or "rv:i:" if 'v' also
               // took an arg
    {
        switch (c)
        {
            case 'r':
                r_flag = true;
                break;
            case 'v': // This would be the invert match flag
                v_flag = true;
                break;
            case 'i': // This would be the case-insensitive flag
                i_flag = true;
                // If -i is meant to take a value (e.g., a path to an ignore
                // list), you would use optarg here: std::string ignore_file =
                // optarg;
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
                // This 'default' case should ideally not be reached if all
                // cases are handled
                std::cerr << "Unknown error during option parsing."
                          << std::endl;
                return 1; // Indicate error
        }
    }

    // --- 3. Extract pattern and file/directory paths ---
    std::string search_pattern;
    std::vector<std::string> paths_to_search;

    // After getopt, optind points to the first non-option argument
    // The first non-option argument is assumed to be the pattern
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

    // All remaining non-option arguments are paths to search
    for (int i = optind; i < argc; ++i)
    {
        paths_to_search.emplace_back(argv[i]);
    }

    // If no paths are specified (e.g., ./mygrep -r pattern), default to current
    // directory
    if (paths_to_search.empty())
    {
        paths_to_search.push_back(".");
    }

    // --- 4. Store all found matches ---
    std::vector<std::string>
        all_matches; // Use a distinct name to avoid confusion with `matches`
                     // inside loops

    // --- 5. Process each specified path ---
    for (const std::string& current_path_str : paths_to_search)
    {
        // std::cerr << "Processing argument: " << current_path_str << std::endl;
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
            // std::cerr << "Searching regular file: " << path.string()
            //           << std::endl;
            std::vector<std::string> file_matches =
                grep_lines(search_pattern, path);
            all_matches.insert(all_matches.end(), file_matches.begin(),
                               file_matches.end());

            // Debugging: Print matches found for this file
            // if (!file_matches.empty())
            // {
            //     std::cerr << "  Matches found in " << path.string() << ":"
            //               << std::endl;
            //     for (const std::string& m : file_matches)
            //     {
            //         std::cerr << "    " << m << std::endl;
            //     }
            // }
        }
        else if (fs::is_directory(status))
        {
            if (!r_flag)
            {
                // If not recursive, treat directories as an error (like grep)
                std::cerr << "mygrep: " << path.string() << ": Is a directory"
                          << std::endl;
            }
            else
            {
                // std::cerr << "Recursively searching directory: "
                //           << path.string() << std::endl;
                // Use std::filesystem::recursive_directory_iterator for
                // recursive search
                for (const auto& dir_entry :
                     fs::recursive_directory_iterator(path, ec))
                {
                    if (ec)
                    {
                        // Handle errors during directory iteration (e.g.,
                        // permission denied to a subdirectory)
                        std::cerr << "Error iterating into "
                                  << dir_entry.path().string() << ": "
                                  << ec.message() << std::endl;
                        ec.clear(); // Clear error for next iteration
                        continue;
                    }

                    // std::cerr << "  Inside: " << dir_entry.path() << std::endl;
                    if (fs::is_regular_file(
                            dir_entry
                                .path())) // Must use .path() for file_status
                                          // and is_regular_file
                    {
                        // std::cerr << "    Searching file in recursion: "
                        //           << dir_entry.path().string() << std::endl;
                        std::vector<std::string> file_matches =
                            grep_lines(search_pattern, dir_entry.path());
                        all_matches.insert(all_matches.end(),
                                           file_matches.begin(),
                                           file_matches.end());

                        // Debugging: Print matches found for this file in
                        // recursion
                        // if (!file_matches.empty())
                        // {
                                // std::cerr << "      Matches found in "
                                //       << dir_entry.path().string() << ":"
                                //       << std::endl;
                        //     for (const std::string& m : file_matches)
                        //     {
                        //         std::cerr << "        " << m << std::endl;
                        //     }
                        // }
                    }
                    // Else: if it's a directory (and
                    // recursive_directory_iterator will handle descending) or
                    // other file type, we just skip it for now.
                }
            }
        }
        else
        {
            // Path is neither a regular file nor a directory (e.g., symlink,
            // pipe, device, or does not exist) Error message already handled by
            // fs::status check if path doesn't exist If it exists but is
            // "other", you might want a specific message.
            std::cerr << "mygrep: " << path.string()
                      << ": Not a regular file or directory (or unhandled type)"
                      << std::endl;
        }
    }

    // --- 6. Print all collected matches to standard output ---
    for (const std::string& match_line : all_matches)
    {
        std::cout << match_line << std::endl;
    }

    // --- 7. Return appropriate exit code ---
    // Return 0 if at least one match was found, 1 if no matches were found.
    return (all_matches.empty() ? 1 : 0);
}