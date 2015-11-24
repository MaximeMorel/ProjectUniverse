////////////////////////////////////////////////////////////////////////////////
#include "plugin.hpp"
#ifdef __unix__
#include <dlfcn.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif
////////////////////////////////////////////////////////////////////////////////
Plugin::Plugin(const std::string& filename)
    : Resource(filename)
    , m_handle(nullptr)
{
    // find real path (using resource manager tools and going through the registered paths)
#ifdef __unix__
    m_handle = dlopen(filename.c_str(), RTLD_LAZY);
    if (m_handle == nullptr)
    {
        // log dlopen error
    }
#endif
#ifdef _WIN32
    // need backslashes
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ms684175%28v=vs.85%29.aspx
    HMODULE module = LoadLibrary(filename.c_str());
    if (module == nullptr)
    {
        // log LoadLibrary error
    }
    m_handle = module;
#endif
}
////////////////////////////////////////////////////////////////////////////////
void* Plugin::getSymbol(const std::string& symbolname)
{
    void* symbol = nullptr;
#ifdef __unix__
    symbol = dlsym(m_handle, symbolname.c_str());
#endif
#ifdef _WIN32
    FARPROC proc = GetProcAddress(static_cast<HMODULE>(m_handle), symbolname.c_str());
    symbol = reinterpret_cast<void*>(proc);
#endif

    if (symbol == nullptr)
    {
        // log getSymbol error
    }

    return symbol;
}
////////////////////////////////////////////////////////////////////////////////
Plugin::~Plugin()
{
    if (m_handle != nullptr)
    {
#ifdef __unix__
        int ret = dlclose(m_handle);
        if (ret != 0)
        {
            // log dlclose error
        }
#endif
#ifdef _WIN32
        BOOL ret = FreeLibrary(static_cast<HMODULE>(m_handle));
        if (ret != 0)
        {
            // log FreeLibrary error
        }
#endif
    }
}
////////////////////////////////////////////////////////////////////////////////
