#ifndef __PLUGINMANAGER_HPP__
#define __PLUGINMANAGER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "plugin.hpp"
#include <map>
////////////////////////////////////////////////////////////////////////////////
class PluginManager
{
public:
    PluginManager();
    ~PluginManager();

    PluginAppPtr loadApp(const std::string& appName = "");
    PluginLibPtr loadLib(const std::string& libName);

    /// Load codec plugins from engine config
    void loadCodecPlugins();

    /// load and add a plugin to the manager
    /// \param pluginName plugin name (ex: "RenderOpenGL33")
    PluginLibPtr addPlugin(const std::string& pluginName);

    /// load and add a plugin to the manager
    /// \param paramName config parameter name storing the name of the plugin (ex: "renderplugin")
    PluginLibPtr addPluginFromConfig(const std::string& paramName);

    void flushPlugins();
    void discoverPlugins();

private:
    const char* m_prefix;
    const char* m_suffix;
    const char* m_separator;

    std::map<std::string, PluginLibPtr> m_plugins;
};
////////////////////////////////////////////////////////////////////////////////
/// Global plugins access
void setGlobalPlugins(PluginManager& plugins);
PluginManager& plugins();
////////////////////////////////////////////////////////////////////////////////
#endif // __PLUGINMANAGER_HPP__

