#ifndef __PLUGIN_HPP__
#define __PLUGIN_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "iplugin.hpp"
////////////////////////////////////////////////////////////////////////////////
class Engine;
////////////////////////////////////////////////////////////////////////////////
/// \brief The Plugin class, helper to load a plugin library
////////////////////////////////////////////////////////////////////////////////
template <class T>
class Plugin : public IPlugin
{
public:
    /// Load library
    /// \param filename dynamic library path
    Plugin(const std::string& filename);
    virtual ~Plugin() override;

    static std::shared_ptr<Plugin> create(const std::string& filename);

    virtual bool isValid() const override;

    T* getLibInstance(Engine* engine);
    void closeLibInstance();

private:
    using PFNgetLibInstance = T* (*)(Engine*);
    using PFNcloseLibInstance = void (*)();

    PFNgetLibInstance m_pGetLibInstance;
    PFNcloseLibInstance m_pCloseLibInstance;
};
////////////////////////////////////////////////////////////////////////////////
class Library;
using PluginLib = Plugin<Library>;
using PluginLibPtr = std::shared_ptr<PluginLib>;

class Application;
using PluginApp = Plugin<Application>;
using PluginAppPtr = std::shared_ptr<PluginApp>;
////////////////////////////////////////////////////////////////////////////////
//template <>
//Plugin<Application>::Plugin(const std::string& filename);
////////////////////////////////////////////////////////////////////////////////
#endif // __PLUGINLIB_HPP__
