////////////////////////////////////////////////////////////////////////////////
#include "pluginManager.hpp"
#include "core/log/logManager.hpp"
#include "core/resource/resourceManager.hpp"
#include "core/config/config.hpp"
#include "core/engineFwd.hpp"
////////////////////////////////////////////////////////////////////////////////
PluginManager* gPlugins = nullptr;
////////////////////////////////////////////////////////////////////////////////
PluginManager::PluginManager()
    : m_prefix(nullptr)
    , m_suffix(nullptr)
    , m_separator(nullptr)
{
    m_prefix = "lib";
    m_suffix = ".so";
    m_separator = "/";
}
////////////////////////////////////////////////////////////////////////////////
PluginManager::~PluginManager()
{
}
////////////////////////////////////////////////////////////////////////////////
PluginAppPtr PluginManager::loadApp(const std::string& appName)
{
    // load main app
    // if no argument is provided, get the app name from engine config "app" entry
    std::string name = appName;
    if (name.length() == 0)
        name = config().get<std::string>("app");
    if (name.length() == 0)
        return nullptr;
    PluginAppPtr app = res().createFromFile<PluginApp>(name + m_separator + m_prefix + name + m_suffix);
    return app;
}
////////////////////////////////////////////////////////////////////////////////
PluginLibPtr PluginManager::loadLib(const std::string& libName)
{
    PluginLibPtr lib = res().createFromFile<PluginLib>(m_prefix + libName + m_suffix);
    return lib;
}
////////////////////////////////////////////////////////////////////////////////
void PluginManager::loadCodecPlugins()
{
    // load codecs from engine config
    // codecplugins config entry can hold a list a strings, separated by ','
    // the code below will split and aload each plugin

    std::string plugins = config().codecplugins->get();
    size_t pos = 0;
    size_t offset = 0;
    do
    {
        pos = plugins.find(',', offset);
        std::string pluginName = plugins.substr(offset, pos - offset);
        addPlugin(pluginName);
        offset = pos + 1;
    } while (pos != std::string::npos);
}
////////////////////////////////////////////////////////////////////////////////
void PluginManager::flushPlugins()
{
    m_plugins.clear();
}
////////////////////////////////////////////////////////////////////////////////
void PluginManager::discoverPlugins()
{
    // get config paths
    // scan folders non recursively
}
////////////////////////////////////////////////////////////////////////////////
PluginLibPtr PluginManager::addPlugin(const std::string& pluginName)
{
    // try to load a plugin by name
    // if the plugin is already in the manager, return it
    // is the plugin is not valid, it won't be added to the manager

    if (pluginName.length() == 0)
        return nullptr;

    auto it = m_plugins.find(pluginName);
    if (it != m_plugins.end())
        return it->second;

    PluginLibPtr pluginLib = loadLib(pluginName);
    if (pluginLib && pluginLib->isValid())
    {
        log().log() << pluginLib << "\n";
        Library* lib = pluginLib->getLibInstance(&getEngine());
        if (lib)
        {
            // plugin ok, add it
            m_plugins[pluginName] = pluginLib;
            return pluginLib;
        }
    }
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
PluginLibPtr PluginManager::addPluginFromConfig(const std::string& paramName)
{
    // try to load a plugin from engine config
    // plugin name is retrieved from paramName config entry

    std::string pluginName = config().get<std::string>(paramName);
    return addPlugin(pluginName);
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
void setGlobalPlugins(PluginManager& plugins)
{
    gPlugins = &plugins;
}
////////////////////////////////////////////////////////////////////////////////
PluginManager& plugins()
{
    return *gPlugins;
}
////////////////////////////////////////////////////////////////////////////////
