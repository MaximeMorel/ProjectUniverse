////////////////////////////////////////////////////////////////////////////////
#include "pluginLib.hpp"
////////////////////////////////////////////////////////////////////////////////
PluginLib::PluginLib(const std::string& filename)
    : Plugin(filename)
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
PluginLib::~PluginLib()
{
    closeLibInstance();
}
////////////////////////////////////////////////////////////////////////////////
PluginLibPtr PluginLib::create(const std::string& filename)
{
    return std::shared_ptr<PluginLib>(new PluginLib(filename));
}
////////////////////////////////////////////////////////////////////////////////
bool PluginLib::isValid() const
{
    return Plugin::isValid() &&
           (m_pGetLibInstance != nullptr) &&
           (m_pCloseLibInstance != nullptr);
}
////////////////////////////////////////////////////////////////////////////////
Library* PluginLib::getLibInstance(Engine* engine)
{
    if (m_pGetLibInstance)
    {
        return m_pGetLibInstance(engine);
    }
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
void PluginLib::closeLibInstance()
{
    if (m_pCloseLibInstance)
    {
        m_pCloseLibInstance();
    }
}
////////////////////////////////////////////////////////////////////////////////
