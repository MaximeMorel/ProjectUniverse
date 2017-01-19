#ifndef __PLUGINMANAGER_HPP__
#define __PLUGINMANAGER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "plugin.hpp"
////////////////////////////////////////////////////////////////////////////////
class PluginManager
{
public:
    PluginManager();
    virtual ~PluginManager();

    PluginAppPtr loadApp(const std::string& appName);
    PluginLibPtr loadLib(const std::string& libName);

    void discoverPlugins();

private:
    const char* m_prefix;
    const char* m_suffix;
    const char* m_separator;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __PLUGINMANAGER_HPP__

