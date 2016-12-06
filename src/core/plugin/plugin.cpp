////////////////////////////////////////////////////////////////////////////////
#include "plugin.hpp"
////////////////////////////////////////////////////////////////////////////////
template <class T>
Plugin<T>::Plugin(const std::string& filename)
    : IPlugin(filename)
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
Plugin<Application>::Plugin(const std::string& filename)
    : IPlugin(filename)
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
Plugin<T>::~Plugin()
{
    closeLibInstance();
}
////////////////////////////////////////////////////////////////////////////////
template <class T>
std::shared_ptr<Plugin<T>> Plugin<T>::create(const std::string& filename)
{
    struct MakeSharedEnabler : public Plugin<T>
    {
        MakeSharedEnabler(const std::string& filename)
            : Plugin<T>(filename) {}
    };
    return std::make_shared<MakeSharedEnabler>(filename);
}
////////////////////////////////////////////////////////////////////////////////
template <class T>
bool Plugin<T>::isValid() const
{
    return IPlugin::isValid() &&
           (m_pGetLibInstance != nullptr) &&
           (m_pCloseLibInstance != nullptr);
}
////////////////////////////////////////////////////////////////////////////////
template <class T>
T* Plugin<T>::getLibInstance(Engine* engine)
{
    if (m_pGetLibInstance)
    {
        return m_pGetLibInstance(engine);
    }
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
template <class T>
void Plugin<T>::closeLibInstance()
{
    if (m_pCloseLibInstance)
    {
        m_pCloseLibInstance();
    }
}
////////////////////////////////////////////////////////////////////////////////
template class Plugin<Library>;
template class Plugin<Application>;
////////////////////////////////////////////////////////////////////////////////
