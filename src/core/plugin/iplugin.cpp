////////////////////////////////////////////////////////////////////////////////
#include "iplugin.hpp"
#ifdef __unix__
#include <dlfcn.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif
#include "../engine.hpp"
////////////////////////////////////////////////////////////////////////////////
IPlugin::IPlugin(const std::string& name, const std::string& fileName)
    : Resource(name)
    , m_handle(nullptr)
    , m_pluginInfo{"null", "null", 0, 0}
    , m_pGetPluginInfo(nullptr)
{
    // find real path (using resource manager tools and going through the registered paths)
#ifdef __unix__
    m_handle = dlopen(fileName.c_str(), RTLD_LAZY);
    if (m_handle == nullptr)
    {
        getEngine().log().log() << "dlopen(" << fileName << ") failed\n";
        getEngine().log().log() << dlerror() << std::endl;
    }
#endif
#ifdef _WIN32
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
IPlugin::~IPlugin()
{
    if (m_handle != nullptr)
    {
#ifdef __unix__
        int ret = dlclose(m_handle);
        if (ret != 0)
        {
            getEngine().log().log() << "dlclose(" << getName() << ") failed\n";
        }
#endif
#ifdef _WIN32
        BOOL ret = FreeLibrary(static_cast<HMODULE>(m_handle));
        if (ret != 0)
        {
            getEngine().log().log() << "FreeLibrary(" << getName() << ") failed\n";
        }
#endif
    }
}
////////////////////////////////////////////////////////////////////////////////
void* IPlugin::getSymbol(const std::string& symbolname) const
{
    void* symbol = nullptr;
#ifdef __unix__
    dlerror();
    symbol = dlsym(m_handle, symbolname.c_str());
    const char* error = dlerror();
    if (error)
    {
        getEngine().log().log() << "dlsym(" << getName() << ", " << symbolname << ") failed\n";
        getEngine().log().log() << error << "\n";
    }
#endif
#ifdef _WIN32
    FARPROC proc = GetProcAddress(static_cast<HMODULE>(m_handle), symbolname.c_str());
    symbol = reinterpret_cast<void*>(proc);
    if (symbol == nullptr)
    {
        getEngine().log().log() << "GetProcAddress(" << getName() << ", " << symbolname << ") failed\n";
    }
#endif

    return symbol;
}
////////////////////////////////////////////////////////////////////////////////
const PluginInfo& IPlugin::getInfo() const
{
    return m_pluginInfo;
}
////////////////////////////////////////////////////////////////////////////////
bool IPlugin::isValid() const
{
    return (m_handle != nullptr) && (m_pGetPluginInfo != nullptr);
}
////////////////////////////////////////////////////////////////////////////////
void IPlugin::printOn(Logger& o) const
{
    o << getName() << ": " << m_pluginInfo.name << " " << m_pluginInfo.major << "." << m_pluginInfo.minor << "\n";
    o << m_pluginInfo.info;
}
////////////////////////////////////////////////////////////////////////////////
