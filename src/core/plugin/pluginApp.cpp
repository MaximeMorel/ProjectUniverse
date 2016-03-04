////////////////////////////////////////////////////////////////////////////////
#include "pluginApp.hpp"
////////////////////////////////////////////////////////////////////////////////
PluginApp::PluginApp(const std::string& filename)
    : Plugin(filename)
    , m_pGetAppInstance(nullptr)
    , m_pCloseAppInstance(nullptr)
{
    if (m_handle != nullptr)
    {
        m_pGetAppInstance = (PFNgetAppInstance)(getSymbol("getAppInstance"));
        m_pCloseAppInstance = (PFNcloseAppInstance)(getSymbol("closeAppInstance"));
    }
}
////////////////////////////////////////////////////////////////////////////////
PluginApp::~PluginApp()
{
    closeAppInstance();
}
////////////////////////////////////////////////////////////////////////////////
bool PluginApp::isValid() const
{
    return Plugin::isValid() &&
           (m_pGetAppInstance != nullptr) &&
           (m_pCloseAppInstance != nullptr);
}
////////////////////////////////////////////////////////////////////////////////
Application* PluginApp::getAppInstance(Engine* engine)
{
    if (m_pGetAppInstance)
    {
        return m_pGetAppInstance(engine);
    }
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
void PluginApp::closeAppInstance()
{
    if (m_pCloseAppInstance)
    {
        m_pCloseAppInstance();
    }
}
////////////////////////////////////////////////////////////////////////////////
