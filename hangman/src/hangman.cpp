#include "project/hangman.hpp"
#include <filesystem>
#include <fstream>
#include <string>
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

std::string getModuleFilePath()
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

std::string getExecutableParentPath()
{
    std::string executablePath = getModuleFilePath();
    std::filesystem::path path(executablePath);
    return path.parent_path();
}

std::filesystem::path getWordsFilePath()
{
    return getExecutableParentPath().append("/words.txt");
}

std::string get_word_from_file(std::ifstream& fs, size_t line_num)
{
    fs.seekg(0, std::ios::beg);
    std::string word;
    for (size_t i = 0; i <= line_num; ++i)
    {
        if (!std::getline(fs, word))
        {
            break; // If the file has fewer lines than line_num, break early
        }
    }
    return word;
}