#ifndef __TPLUGIN_HPP__
#define __TPLUGIN_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "iplugin.hpp"
////////////////////////////////////////////////////////////////////////////////
class Engine;
////////////////////////////////////////////////////////////////////////////////
/// \brief The Plugin class, helper to load a plugin library
////////////////////////////////////////////////////////////////////////////////
template <class T>
class TPlugin : public Plugin
{
public:
    /// Load library
    /// \param filename dynamic library path
    TPlugin(const std::string& name, const std::string& fileName);
    virtual ~TPlugin() override;

    static std::shared_ptr<TPlugin<T>> create(const std::string& name, const std::string& fileName);

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
    virtual ResourceType& dyntype() override { return type; }
    virtual const ResourceType& dyntype() const override { return type; }
    static ResourceType type;
};
////////////////////////////////////////////////////////////////////////////////
class Library;
using PluginLib = TPlugin<Library>;
using PluginLibPtr = std::shared_ptr<PluginLib>;

class Application;
using PluginApp = TPlugin<Application>;
using PluginAppPtr = std::shared_ptr<PluginApp>;
////////////////////////////////////////////////////////////////////////////////
//template <>
//Plugin<Application>::Plugin(const std::string& filename);
////////////////////////////////////////////////////////////////////////////////
#endif // __TPLUGIN_HPP__
