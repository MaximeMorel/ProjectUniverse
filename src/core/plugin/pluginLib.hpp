#ifndef __PLUGINLIB_HPP__
#define __PLUGINLIB_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "plugin.hpp"
////////////////////////////////////////////////////////////////////////////////
class Engine;
class Library;
class PluginLib;
typedef std::shared_ptr<PluginLib> PluginLibPtr;
////////////////////////////////////////////////////////////////////////////////
/// \brief The PluginLib class, helper to load a plugin library
////////////////////////////////////////////////////////////////////////////////
class PluginLib : public Plugin
{
public:
    /// Load library
    /// \param filename dynamic library path
    PluginLib(const std::string& filename);
    virtual ~PluginLib() override;

    static PluginLibPtr create(const std::string& filename);

    virtual bool isValid() const override;

    Library* getLibInstance(Engine* engine);
    void closeLibInstance();

private:
    using PFNgetLibInstance = Library* (*)(Engine*);
    using PFNcloseLibInstance = void (*)();

    PFNgetLibInstance m_pGetLibInstance;
    PFNcloseLibInstance m_pCloseLibInstance;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __PLUGINLIB_HPP__
