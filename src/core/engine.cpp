////////////////////////////////////////////////////////////////////////////////
#include "engine.hpp"
#include "core/tools/filetools.hpp"
#include <map>
#include <cstring>
////////////////////////////////////////////////////////////////////////////////
// Run main
// Start engine
// Process command line parameters (ex: app, resolution)
// Load config (hardcoded in engine, default engine config, app config)
// First create loggers
// Load res manager
// Load default config
// Load global config
// Get application name: --app param ?
// Load app specific config
// Load plugins
// Exec app
////////////////////////////////////////////////////////////////////////////////
Engine* gEngine = nullptr;
extern LogManager* gLog;
////////////////////////////////////////////////////////////////////////////////
Engine::Engine(const std::string& name)
    : m_config()
    , m_logManager()
    , m_resourceManager(m_logManager)
    , m_pluginManager()
    , m_name(name)
    , m_requestQuit(false)
{
    setGlobalEngine(*this);
    m_logManager.log() << FILEINFO << "Engine " << m_name << " init...\n";
    m_logManager.log() << (LogLine() << FILEINFO << "Engine " << m_name << " init...\n");

    char buf[256];
    m_logManager.log() << "cwd: " << FileTools::getcwd(buf, sizeof(buf)) << "\n";

    FileTools::mkdirGame("");

    m_config.initDefaultConfig();

    m_engineLua.registerEngineLua();
    m_engineLua.executeFile("config.lua");
    m_engineLua.executeFile(FileTools::getdirGame("") + "config.lua");
}
////////////////////////////////////////////////////////////////////////////////
Engine::~Engine()
{
    m_logManager.log() << "Engine " << m_name << " close...\n";

    // correct deallocation order should be handled here
    // to prevent render resources being deallocatted after render plugin
    // it will cause a crash, because code related to these resource is unloaded

    // release resources allocated by plugins
    //m_pluginManager.flushPlugins();
}
////////////////////////////////////////////////////////////////////////////////
bool Engine::init(int argc, char **argv)
{
    // load current app config
    std::string appConfigPath = "app/" + m_config.app->get() + "/config.lua";
    m_engineLua.executeFile(appConfigPath);
    m_engineLua.executeFile(FileTools::getdirGame(m_config.app->get().c_str()) + "config.lua");

    // reapply command line arguments as they have highest priority
    parseArgs(argc, argv);

    FileTools::mkdirGame(m_config.app->get().c_str());

    if (!loadPlugins())
    {
        m_logManager.log() << "Error loading plugins.\n";
        return false;
    }

    m_inputManager.discoverDevices();
    m_inputManager.listDevices(m_logManager.log());

    return true;
}
////////////////////////////////////////////////////////////////////////////////
LogManager& Engine::log()
{
    return m_logManager;
}
////////////////////////////////////////////////////////////////////////////////
ResourceManager& Engine::res()
{
    return m_resourceManager;
}
////////////////////////////////////////////////////////////////////////////////
PluginManager& Engine::plugins()
{
    return m_pluginManager;
}
////////////////////////////////////////////////////////////////////////////////
InputManager& Engine::input()
{
    return m_inputManager;
}
////////////////////////////////////////////////////////////////////////////////
RenderManager& Engine::render()
{
    return m_renderManager;
}
////////////////////////////////////////////////////////////////////////////////
CodecManager& Engine::codecs()
{
    return m_codecManager;
}
////////////////////////////////////////////////////////////////////////////////
ThreadManager& Engine::threads()
{
    return m_threadManager;
}
////////////////////////////////////////////////////////////////////////////////
WindowManager& Engine::window()
{
    return m_windowManager;
}
////////////////////////////////////////////////////////////////////////////////
Config& Engine::config()
{
    return m_config;
}
////////////////////////////////////////////////////////////////////////////////
void Engine::parseArgs(int argc, char** argv)
{
    // parse command line arguments
    // then add them to the engine config
    // should be done after loading main config file, so command line paramters have higher priority
    // ex: bin/engine --set resolution=1280x720 --set app=Example
    std::map<std::string, std::string> args;
    std::string arg;
    for (int i = 0; i < argc; ++i)
    {
        if (strncmp(argv[i], "--set", 5) == 0)
        {
            ++i;
            if (i < argc)
            {
                arg = argv[i];
                size_t pos = arg.find('=');
                if (pos != std::string::npos)
                {
                    args[arg.substr(0, pos)] = arg.substr(pos + 1);
                }
            }
        }
    }

    for (auto arg : args)
    {
        m_logManager.log() << arg.first << " = " << arg.second << "\n";
        m_config.setFromString(arg.first, arg.second);
    }
}
////////////////////////////////////////////////////////////////////////////////
void Engine::setRequestQuit(bool status)
{
    m_requestQuit = status;
}
////////////////////////////////////////////////////////////////////////////////
bool Engine::getRequestQuit() const
{
    return m_requestQuit;
}
////////////////////////////////////////////////////////////////////////////////
bool Engine::loadPlugins()
{
    // load all requested plugins
    // graphic context must be ready before loading render plugin
    // context version is chosen from the render plugin name
    // once loaded, the plugins are managed by the plugin manager
    // engine resource manager also hold a weak pointer to them

    plugins().loadCodecPlugins();

    PluginLibPtr windowPlugin = plugins().addPluginFromConfig("windowplugin");
    if (!windowPlugin)
        return false;
    if (!m_windowManager.setPlugin(windowPlugin))
        return false;
    if (!m_windowManager.createContext(m_config.renderplugin->get()))
        return false;

    PluginLibPtr renderPlugin = plugins().addPluginFromConfig("renderplugin");
    if (!renderPlugin)
        return false;
    if (!m_renderManager.setPlugin(renderPlugin))
        return false;

    PluginLibPtr inputPlugin = plugins().addPluginFromConfig("inputplugin");
    if (!inputPlugin)
        return false;
    if (!m_inputManager.setPlugin(inputPlugin))
        return false;

    PluginLibPtr audioPlugin = plugins().addPluginFromConfig("audioplugin");
    if (!audioPlugin)
        return false;

    return true;
}
////////////////////////////////////////////////////////////////////////////////
void setGlobalEngine(Engine& engine)
{
    gEngine = &engine;
    setGlobalConfig(engine.config());
    setGlobalCodecs(engine.codecs());
    setGlobalLogger(engine.log());
    setGlobalRender(engine.render());
    setGlobalResourceManager(engine.res());
    setGlobalInput(engine.input());
    setGlobalThreads(engine.threads());
    setGlobalPlugins(engine.plugins());
    setGlobalWindow(engine.window());
}
////////////////////////////////////////////////////////////////////////////////
Engine& getEngine()
{
    return *gEngine;
}
////////////////////////////////////////////////////////////////////////////////
