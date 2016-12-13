////////////////////////////////////////////////////////////////////////////////
#include "plugin.hpp"
#include "core/resource/resourceManager.hpp"
#include "core/log/logManager.hpp"
////////////////////////////////////////////////////////////////////////////////
template <> ResourceType TPlugin<Library>::type("PluginLib");
template <> ResourceType TPlugin<Application>::type("PluginApp");
////////////////////////////////////////////////////////////////////////////////
template <class T>
TPlugin<T>::TPlugin(const std::string& name, const std::string& fileName)
    : Plugin(name, fileName)
    , m_pGetLibInstance(nullptr)
    , m_pCloseLibInstance(nullptr)
{
    if (m_handle != nullptr)
    {
        //m_pGetLibInstance = (PFNgetLibInstance)(getSymbol("getLibInstance"));
        //m_pCloseLibInstance = (void (*)())(getSymbol("closeLibInstance"));

        *(void**)(&m_pGetLibInstance) = getSymbol("getLibInstance");
        *(void**)(&m_pCloseLibInstance) = getSymbol("closeLibInstance");
    }
}
////////////////////////////////////////////////////////////////////////////////
template <>
TPlugin<Application>::TPlugin(const std::string& name, const std::string& fileName)
    : Plugin(name, fileName)
    , m_pGetLibInstance(nullptr)
    , m_pCloseLibInstance(nullptr)
{
    if (m_handle != nullptr)
    {
        *(void**)(&m_pGetLibInstance) = getSymbol("getAppInstance");
        *(void**)(&m_pCloseLibInstance) = getSymbol("closeAppInstance");
    }
}
////////////////////////////////////////////////////////////////////////////////
template <class T>
TPlugin<T>::~TPlugin()
{
    closeLibInstance();

    if (isEnginemanaged())
    {
        log().log() << __FUNCTION__ << ": " << *this << std::endl;
        res().delResource(this);
    }
}
////////////////////////////////////////////////////////////////////////////////
template <>
const char* TPlugin<Library>::getSearchPath()
{
    return "lib/";
}
////////////////////////////////////////////////////////////////////////////////
template <>
const char* TPlugin<Application>::getSearchPath()
{
    return "app/";
}
////////////////////////////////////////////////////////////////////////////////
template <class T>
std::shared_ptr<TPlugin<T>> TPlugin<T>::create(const std::string& name, const std::string& fileName)
{
    return std::make_shared<TPlugin<T>>(name, fileName);
}
////////////////////////////////////////////////////////////////////////////////
template <class T>
bool TPlugin<T>::isValid() const
{
    return Plugin::isValid() &&
           (m_pGetLibInstance != nullptr) &&
           (m_pCloseLibInstance != nullptr);
}
////////////////////////////////////////////////////////////////////////////////
template <class T>
T* TPlugin<T>::getLibInstance(Engine* engine)
{
    if (m_pGetLibInstance)
    {
        return m_pGetLibInstance(engine);
    }
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
template <class T>
void TPlugin<T>::closeLibInstance()
{
    if (m_pCloseLibInstance)
    {
        m_pCloseLibInstance();
    }
}
////////////////////////////////////////////////////////////////////////////////
template class TPlugin<Library>;
template class TPlugin<Application>;
////////////////////////////////////////////////////////////////////////////////
