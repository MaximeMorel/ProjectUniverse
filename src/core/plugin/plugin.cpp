////////////////////////////////////////////////////////////////////////////////
#include "plugin.hpp"
#ifdef __unix__
#include <dlfcn.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif
#include "../engine.hpp"
////////////////////////////////////////////////////////////////////////////////
Plugin::Plugin(const std::string& filename)
    : Resource(filename)
    , m_handle(nullptr)
    , m_pluginInfo{"null", "null", 0, 0}
{
    // find real path (using resource manager tools and going through the registered paths)
#ifdef __unix__
    m_handle = dlopen(filename.c_str(), RTLD_LAZY);
    if (m_handle == nullptr)
    {
        getEngine().log().log() << "dlopen(" << filename << ") failed" << std::endl;
    }
#endif
#ifdef _WIN32
    // need backslashes
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ms684175%28v=vs.85%29.aspx
    HMODULE module = LoadLibrary(filename.c_str());
    m_handle = module;
    if (m_handle == nullptr)
    {
        getEngine().log().log() << "loadLibrary(" << filename << ") failed" << std::endl;
    }
#endif

    if (m_handle != nullptr)
    {
        getPluginInfo = (PFNgetPluginInfo)(getSymbol("getPluginInfo"));
        if (getPluginInfo)
        {
            PluginInfo* p = getPluginInfo();
            if (p)
            {
                m_pluginInfo = *p;
            }
        }
    }
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
            getEngine().log().log() << "dlclose(" << getName() << ") failed" << std::endl;
        }
#endif
#ifdef _WIN32
        BOOL ret = FreeLibrary(static_cast<HMODULE>(m_handle));
        if (ret != 0)
        {
            getEngine().log().log() << "FreeLibrary(" << getName() << ") failed" << std::endl;
        }
#endif
    }
}
////////////////////////////////////////////////////////////////////////////////
void* Plugin::getSymbol(const std::string& symbolname) const
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
        getEngine().log().log() << "getSymbol(" << getName() << ", " << symbolname << ") failed" << std::endl;
    }

    return symbol;
}
////////////////////////////////////////////////////////////////////////////////
const PluginInfo& Plugin::getInfo() const
{
    return m_pluginInfo;
}
////////////////////////////////////////////////////////////////////////////////
void Plugin::printOn(Logger& o) const
{
    o << getName() << ": " << m_pluginInfo.name << " " << m_pluginInfo.major << "." << m_pluginInfo.minor << "\n";
    o << m_pluginInfo.info;
}
////////////////////////////////////////////////////////////////////////////////
