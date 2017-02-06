////////////////////////////////////////////////////////////////////////////////
#include "iplugin.hpp"
#if defined(__linux__) || defined(__linux) || defined(linux)
#include <dlfcn.h>
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#include <windows.h>
#endif
#include "core/log/logManager.hpp"
#include "../engine.hpp"
////////////////////////////////////////////////////////////////////////////////
Plugin::Plugin(const std::string& name, const std::string& fileName)
    : Resource(name)
    , m_handle(nullptr)
    , m_pluginInfo{"null", "null", 0, 0}
    , m_pGetPluginInfo(nullptr)
{
    // find real path (using resource manager tools and going through the registered paths)
#if defined(__linux__) || defined(__linux) || defined(linux)
    m_handle = dlopen(fileName.c_str(), RTLD_LAZY);
    if (m_handle == nullptr)
    {
        log().log() << "dlopen(" << fileName << ") failed\n";
        log().log() << dlerror() << std::endl;
    }
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    // need backslashes
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ms684175%28v=vs.85%29.aspx
    HMODULE module = LoadLibrary(fileName.c_str());
    m_handle = module;
    if (m_handle == nullptr)
    {
        getEngine().log().log() << "loadLibrary(" << fileName << ") failed\n";
    }
#endif

    if (m_handle != nullptr)
    {
        //m_pGetPluginInfo = (PFNgetPluginInfo)(getSymbol("getPluginInfo"));
        *(void**)(&m_pGetPluginInfo) = getSymbol("getPluginInfo");
        if (m_pGetPluginInfo)
        {
            const PluginInfo* p = m_pGetPluginInfo();
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
#if defined(__linux__) || defined(__linux) || defined(linux)
        int ret = dlclose(m_handle);
        if (ret != 0)
        {
            log().log() << "dlclose(" << getName() << ") failed\n";
        }
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        BOOL ret = FreeLibrary(static_cast<HMODULE>(m_handle));
        if (ret == 0)
        {
            log().log() << "FreeLibrary(" << getName() << ") failed\n";
        }
#endif
    }
}
////////////////////////////////////////////////////////////////////////////////
void* Plugin::getSymbol(const std::string& symbolname) const
{
    void* symbol = nullptr;
#if defined(__linux__) || defined(__linux) || defined(linux)
    dlerror();
    symbol = dlsym(m_handle, symbolname.c_str());
    const char* error = dlerror();
    if (error)
    {
        log().log() << "dlsym(" << getName() << ", " << symbolname << ") failed\n";
        log().log() << error << "\n";
    }
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    FARPROC proc = GetProcAddress(static_cast<HMODULE>(m_handle), symbolname.c_str());
    symbol = reinterpret_cast<void*>(proc);
    if (symbol == nullptr)
    {
        log().log() << "GetProcAddress(" << getName() << ", " << symbolname << ") failed\n";
    }
#endif

    return symbol;
}
////////////////////////////////////////////////////////////////////////////////
const PluginInfo& Plugin::getInfo() const
{
    return m_pluginInfo;
}
////////////////////////////////////////////////////////////////////////////////
bool Plugin::isValid() const
{
    return (m_handle != nullptr) && (m_pGetPluginInfo != nullptr);
}
////////////////////////////////////////////////////////////////////////////////
void Plugin::printOn(Logger& o) const
{
    o << getName() << " ("  << m_pluginInfo.info << ") : " << m_pluginInfo.name << " " << m_pluginInfo.major << "." << m_pluginInfo.minor;
}
////////////////////////////////////////////////////////////////////////////////
