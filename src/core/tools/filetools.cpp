////////////////////////////////////////////////////////////////////////////////
#include "filetools.hpp"
////////////////////////////////////////////////////////////////////////////////
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
# include <direct.h>
#elif defined(__linux__) || defined(__linux) || defined(linux)
#include <unistd.h>
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
