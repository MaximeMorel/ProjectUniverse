#ifndef __PLUGIN_HPP__
#define __PLUGIN_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resource.hpp"
////////////////////////////////////////////////////////////////////////////////
/// \brief Plugin information structure
////////////////////////////////////////////////////////////////////////////////
struct PluginInfo
{
    const char* info;           ///< Plugin info string
    const char* name;           ///< Plugin name
    int major;                  ///< Major version number
    int minor;                  ///< Minor version number
};
////////////////////////////////////////////////////////////////////////////////
/// \brief Plugin class, helper to load a shared library
////////////////////////////////////////////////////////////////////////////////
class Plugin : public Resource
{
public:
    /// Load library
    /// \param filename dynamic library path
    Plugin(const std::string& filename);
    virtual ~Plugin() override;

    /// Load a symbol form the dynamic library
    /// \param symbolname Symbol to load from the dynamic library
    /// \return nullptr if symbolname could not be loaded
    void* getSymbol(const std::string& symbolname) const;

    const PluginInfo& getInfo() const;

    virtual bool isValid() const;

    virtual void printOn(Logger& o) const override;

protected:
    void* m_handle;             ///< Handle for the dynamic library
    PluginInfo m_pluginInfo;    ///< Details about the plugin

    using PFNgetPluginInfo = const PluginInfo* (*)();
    PFNgetPluginInfo m_pGetPluginInfo;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __PLUGIN_HPP__
