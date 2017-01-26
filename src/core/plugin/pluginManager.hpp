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

    /// Load plugins from engine config
    void loadPlugins();

    /// Load codec plugins from engine config
    void loadCodecPlugins();
    PluginLibPtr loadRenderPlugin();
    PluginLibPtr loadInputPlugin();
    PluginLibPtr loadAudioPlugin();
    PluginLibPtr loadWindowContextPlugin();

    void flushPlugins();
    void discoverPlugins();

private:
    PluginLibPtr addPlugin(const std::string& name, bool& isDuplicate);

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

