#ifndef __PLUGINAPP_HPP__
#define __PLUGINAPP_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "plugin.hpp"
////////////////////////////////////////////////////////////////////////////////
class Engine;
class Application;
class PluginApp;
typedef std::shared_ptr<PluginApp> PluginAppPtr;
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

    static PluginAppPtr create(const std::string& filename);

    virtual bool isValid() const override;

    Application *getAppInstance(Engine* engine);
    void closeAppInstance();

private:
    using PFNgetAppInstance = Application* (*)(Engine*);
    using PFNcloseAppInstance = void (*)();

    PFNgetAppInstance m_pGetAppInstance;
    PFNcloseAppInstance m_pCloseAppInstance;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __PLUGINAPP_HPP__
