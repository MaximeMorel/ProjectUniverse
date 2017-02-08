#ifndef __FILETOOLS_HPP__
#define __FILETOOLS_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/engine_export.h"
#include <string>
#include <cstddef>
////////////////////////////////////////////////////////////////////////////////
class ENGINE_EXPORT FileTools
{
public:
    static char* getcwd(char* buf, size_t size);
    static bool mkdir(const std::string& path);
    static bool mkdirGame(const char* app);
    static bool chdirGame();

    /// Get user writable area, always ends with a folder separator: /
    static std::string getdirGame(const char* app);
};
////////////////////////////////////////////////////////////////////////////////
#endif // __FILETOOLS_HPP__
