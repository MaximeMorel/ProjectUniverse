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

    using PFNcloseAppInstance = void (*)();
    PFNcloseAppInstance closeAppInstance;

    using PFNgetAppInstance = Application* (*)(Engine*);
    PFNgetAppInstance getAppInstance;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __PLUGINAPP_HPP__
