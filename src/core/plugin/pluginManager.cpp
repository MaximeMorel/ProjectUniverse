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
void PluginManager::loadPlugins()
{
    loadCodecPlugins();
    loadWindowContextPlugin();
    loadRenderPlugin();
    loadAudioPlugin();
}
////////////////////////////////////////////////////////////////////////////////
void PluginManager::loadCodecPlugins()
{
    //std::string plugins = config().codecplugins->get();
    std::string plugins = config().get<std::string>("codecplugins");
    size_t pos = 0;
    size_t offset = 0;
    do
    {
        pos = plugins.find(',', offset);
        std::string pluginName = plugins.substr(offset, pos - offset);
        //log().log() << plugins.substr(offset, pos - offset) << "\n";
        bool isDuplicate = false;
        addPlugin(pluginName, isDuplicate);
        offset = pos + 1;
    } while (pos != std::string::npos);
}
////////////////////////////////////////////////////////////////////////////////
PluginLibPtr PluginManager::loadRenderPlugin()
{
    std::string param = "renderplugin";
    std::string pluginName = config().get<std::string>(param);
    bool isDuplicate = false;
    PluginLibPtr plugin = addPlugin(pluginName, isDuplicate);

    return plugin;
}
////////////////////////////////////////////////////////////////////////////////
PluginLibPtr PluginManager::loadInputPlugin()
{
    std::string param = "inputplugin";
    std::string pluginName = config().get<std::string>(param);
    bool isDuplicate = false;
    PluginLibPtr plugin = addPlugin(pluginName, isDuplicate);

    return plugin;
}
////////////////////////////////////////////////////////////////////////////////
PluginLibPtr PluginManager::loadAudioPlugin()
{
    std::string param = "audioplugin";
    std::string pluginName = config().get<std::string>(param);
    bool isDuplicate = false;
    PluginLibPtr plugin = addPlugin(pluginName, isDuplicate);

    return plugin;
}
////////////////////////////////////////////////////////////////////////////////
PluginLibPtr PluginManager::loadWindowContextPlugin()
{
    std::string param = "windowplugin";
    std::string pluginName = config().get<std::string>(param);
    bool isDuplicate = false;
    PluginLibPtr plugin = addPlugin(pluginName, isDuplicate);

    return plugin;
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
PluginLibPtr PluginManager::addPlugin(const std::string& pluginName, bool& isDuplicate)
{
    isDuplicate = false;
    if (m_plugins.find(pluginName) != m_plugins.end())
        isDuplicate = true;

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
