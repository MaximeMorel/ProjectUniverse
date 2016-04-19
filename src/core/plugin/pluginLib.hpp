#ifndef __PLUGINLIB_HPP__
#define __PLUGINLIB_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "plugin.hpp"
////////////////////////////////////////////////////////////////////////////////
class Engine;
class Library;
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

    virtual bool isValid() const override;

    Library* getLibInstance(Engine* engine);
    void closeLibInstance();

private:
    using PFNgetLibInstance = Library* (*)(Engine*);
    PFNgetLibInstance m_pGetLibInstance;

    using PFNcloseLibInstance = void (*)();
    PFNcloseLibInstance m_pCloseLibInstance;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __PLUGINLIB_HPP__
