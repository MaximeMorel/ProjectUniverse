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
protected:
    /// Load library
    /// \param filename dynamic library path
    Plugin(const std::string& name, const std::string& fileName);

public:
    virtual ~Plugin() override;

    static std::shared_ptr<Plugin<T>> create(const std::string& name, const std::string& fileName);

    /// Get the sub search path for this resource
    static const char* getSearchPath();

    virtual bool isValid() const override;

    T* getLibInstance(Engine* engine);
    void closeLibInstance();

private:
    using PFNgetLibInstance = T* (*)(Engine*);
    using PFNcloseLibInstance = void (*)();

    PFNgetLibInstance m_pGetLibInstance;
    PFNcloseLibInstance m_pCloseLibInstance;

public:
    virtual ResourceType dyntype() override{ return type; }
    static ResourceType type;
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
