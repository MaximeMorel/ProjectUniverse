////////////////////////////////////////////////////////////////////////////////
#include "filetools.hpp"
////////////////////////////////////////////////////////////////////////////////
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
# include <direct.h>
#elif defined(__linux__) || defined(__linux) || defined(linux)
#include <unistd.h>
#include <sys/stat.h>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <string>
#endif
////////////////////////////////////////////////////////////////////////////////
char* FileTools::getcwd(char* buf, size_t size)
{
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    return _getcwd(buf, size);
#elif defined(__linux__) || defined(__linux) || defined(linux)
    return ::getcwd(buf, size);
#endif
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
bool FileTools::mkdir(const char* path)
{
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    return (_mkdir(path) == 0);
#elif defined(__linux__) || defined(__linux) || defined(linux)
    return (::mkdir(path, S_IRWXU | S_IRGRP | S_IROTH | S_IXGRP | S_IXOTH) == 0);
#endif
    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool FileTools::mkdirGame(const char* app)
{
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

#elif defined(__linux__) || defined(__linux) || defined(linux)
    char* home = getenv("HOME");
    std::string path(home);
    path += "/.config";
    mkdir(path.c_str());
    path += "/ProjectUniverse/";
    mkdir(path.c_str());
    if (strlen(app) > 0)
    {
        path += "app/";
        mkdir(path.c_str());
        path += app;
        mkdir(path.c_str());
    }
    return true;
#endif
    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool FileTools::chdirGame()
{
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    return false;
#elif defined(__linux__) || defined(__linux) || defined(linux)
    char buf[PATH_MAX];
    readlink("/proc/self/exe", buf, sizeof(buf));
    int count = 0;
    int i = strlen(buf) - 1;
    while (count < 2 && i >= 0)
    {
        if (buf[i] == '/')
            ++count;
        --i;
    }
    if (count == 2)
    {
        buf[i + 1] = '\0';
        return (chdir(buf) == 0);
    }
#endif
    return false;
}
////////////////////////////////////////////////////////////////////////////////
std::string FileTools::getdirGame(const char* app)
{
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

#elif defined(__linux__) || defined(__linux) || defined(linux)
    char* home = getenv("HOME");
    std::string res(home);
    res += "/.config/ProjectUniverse/";
    if (strlen(app) > 0)
    {
        res += "app/";
        res += app;
    }
    res += "/";
    return res;
#endif
    return std::string();
}
////////////////////////////////////////////////////////////////////////////////
