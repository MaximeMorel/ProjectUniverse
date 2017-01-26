////////////////////////////////////////////////////////////////////////////////
#include "engine.hpp"
#include <map>
#include <cstring>
#include <unistd.h>
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
    m_logManager.log() << "cwd: " << getcwd(buf, 256) << "\n";
}
////////////////////////////////////////////////////////////////////////////////
Engine::~Engine()
{
    m_logManager.log() << "Engine " << m_name << " close...\n";
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
ThreadManager& Engine::thread()
{
    return m_threadManager;
}
////////////////////////////////////////////////////////////////////////////////
Config& Engine::config()
{
    return m_config;
}
////////////////////////////////////////////////////////////////////////////////
void Engine::parseArgs(int argc, char** argv)
{
    // bin/engine --set resolution=1280x720 --set app=Example
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
        ConfigEntry* ce = m_config.getC(arg.first);
        if (ce)
        {
            //ce->set(arg.second);
        }
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
void setGlobalEngine(Engine& engine)
{
    gEngine = &engine;
    setGlobalCodecs(engine.codecs());
    setGlobalLogger(engine.log());
    setGlobalRender(engine.render());
    setGlobalResourceManager(engine.res());
    setGlobalInput(engine.input());
}
////////////////////////////////////////////////////////////////////////////////
Engine& getEngine()
{
    return *gEngine;
}
////////////////////////////////////////////////////////////////////////////////
