#ifndef __PLUGINAPP_HPP__
#define __PLUGINAPP_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "plugin.hpp"
////////////////////////////////////////////////////////////////////////////////
class Engine;
class Application;
////////////////////////////////////////////////////////////////////////////////
/// \brief The PluginApp class, helper to load an application library
////////////////////////////////////////////////////////////////////////////////
class PluginApp : public Plugin
{
public:
    /// Load library
    /// \param filename dynamic library path
    PluginApp(const std::string& filename);
    virtual ~PluginApp() override;

    virtual bool isValid() const;

    Application *getAppInstance(Engine* engine);
    void closeAppInstance();

private:
    using PFNgetAppInstance = Application* (*)(Engine*);
    PFNgetAppInstance m_pGetAppInstance;

    using PFNcloseAppInstance = void (*)();
    PFNcloseAppInstance m_pCloseAppInstance;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __PLUGINAPP_HPP__
