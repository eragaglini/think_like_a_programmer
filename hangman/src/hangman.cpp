#include "project/hangman.hpp"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif

#ifdef __linux__
#include <unistd.h>
#endif

#ifdef __FreeBSD__
#include <sys/sysctl.h>
#endif

#ifdef __NetBSD__
#include <unistd.h>
#endif

#ifdef __DragonFly__
#include <unistd.h>
#endif

std::string get_module_file_path()
{
    std::string path;

#ifdef _WIN32
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    path = buffer;
#endif

#ifdef __APPLE__
    uint32_t size = 1024;
    char buffer[size];
    if (_NSGetExecutablePath(buffer, &size) == 0)
    {
        path = buffer;
    }
    else
    {
        throw std::runtime_error("Failed to get executable path");
    }
#endif

#ifdef __linux__
    ssize_t len = readlink("/proc/self/exe", buffer, size);
    if (len != -1)
    {
        path = buffer;
    }
    else
    {
        throw std::runtime_error("Failed to get executable path");
    }
#endif

#ifdef __FreeBSD__
    int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, -1};
    size_t size = 1024;
    char buffer[size];
    if (sysctl(mib, 4, buffer, &size, NULL, 0) == 0)
    {
        path = buffer;
    }
    else
    {
        throw std::runtime_error("Failed to get executable path");
    }
#endif

#ifdef __NetBSD__
    ssize_t len = readlink("/proc/curproc/exe", buffer, size);
    if (len != -1)
    {
        path = buffer;
    }
    else
    {
        throw std::runtime_error("Failed to get executable path");
    }
#endif

#ifdef __DragonFly__
    ssize_t len = readlink("/proc/curproc/file", buffer, size);
    if (len != -1)
    {
        path = buffer;
    }
    else
    {
        throw std::runtime_error("Failed to get executable path");
    }
#endif

    return path;
}

std::string get_executable_parent_path()
{
    std::string executablePath = get_module_file_path();
    std::filesystem::path path(executablePath);
    return path.parent_path();
}

std::filesystem::path get_words_file_path()
{
    return get_executable_parent_path().append("/words.txt");
}

std::vector<std::string> get_word_vector_from_file(std::ifstream& fs,
                                                   size_t length)
{
    // Creating a vector of strings
    std::vector<std::string> wordVector;
    fs.seekg(0, std::ios::beg);
    std::string line;
    while (std::getline(fs, line))
    {
        std::istringstream ss(line);
        if (length == line.size())
            wordVector.push_back(line);
    }
    return wordVector;
}

// std::string get_word_from_file(std::ifstream& fs, size_t line_num)
// {
//     std::vector<std::string> wordVector = get_word_vector_from_file(fs);
//     return wordVector[line_num % wordVector.size()];
// }

std::string get_pattern_for_word(std::string word, char ch, std::string pattern)
{
    for (size_t i = 0; i < word.length(); i++)
    {
        /* code */
        if (word[i] == ch)
        {
            pattern[i] = ch;
        }
    }
    return pattern;
}

std::unordered_map<std::string, std::vector<std::string>>
group_words_by_pattern(const std::vector<std::string>& wordVector, char ch,
                       std::string old_pattern)
{
    std::unordered_map<std::string, std::vector<std::string>> grouped;

    for (const std::string& word : wordVector)
    {
        std::string pattern = get_pattern_for_word(word, ch, old_pattern);
        grouped[pattern].push_back(word);
    }

    return grouped;
}

std::pair<std::string, std::vector<std::string>> get_best_option_pair(
    const std::unordered_map<std::string, std::vector<std::string>>&
        pattern_map)
{
    std::pair<std::string, std::vector<std::string>> best_option =
        *(pattern_map.begin());

    for (auto& it : pattern_map)
    {
        // Do stuff
        if (it.second.size() > best_option.second.size())
        {
            best_option = it;
        }
    }
    return best_option;
}

bool is_in_vector(std::vector<std::string>& vectr, std::string ch)
{
    for (auto i : vectr)
    {

        // If the target element found set the
        // flag value 1 and break
        if (i == ch)
        {
            return true;
        }
    }
    return false;
}

bool matches_pattern(std::string pattern, std::string word)
{
    for (size_t i = 0; i < word.size(); i++)
    {
        /* code */
        if ((pattern[i] != '_') && (word[i] != pattern[i]))
        {
            /* code */
            return false;
        }
        
    }
    return true;
}

std::string get_best_guess(std::vector<std::string>& wordVector,
                           std::vector<std::string>& guessed_letters,
                           std::string& pattern)
{
    for (size_t i = 0; i < wordVector.size(); i++)
    {
        /* code */
        std::string word = wordVector[i];
        if (matches_pattern(pattern, word))
        {
            for (size_t j = 0; j < word.size(); j++)
            {
                /* code */
                std::string letter = std::string(1, word[j]);
                if (!is_in_vector(guessed_letters, letter))
                {
                    /* code */
                    return letter;
                }
            }
        }
    }
    return "";
}

std::vector<std::string>
update_word_vector(std::vector<std::string>& wordVector, std::string& pattern,
                   std::vector<std::string>& guessed_letters)
{
    std::vector<std::string> new_word_vector;
    for (size_t i = 0; i < wordVector.size(); i++)
    {
        /* code */
        std::string word = wordVector[i];
        if (matches_pattern(pattern, word))
        {
            new_word_vector.push_back(word);
        }
    }
    return new_word_vector;
}