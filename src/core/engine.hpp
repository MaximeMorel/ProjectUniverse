#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "log/logManager.hpp"
#include "resource/resourceManager.hpp"
#include "plugin/pluginManager.hpp"
#include "input/inputManager.hpp"
#include "render/renderManager.hpp"
#include "codecs/codecManager.hpp"
#include "thread/threadManager.hpp"
#include "windowContext/windowManager.hpp"
#include "config/config.hpp"
#include "script/lua/engineLua.hpp"
////////////////////////////////////////////////////////////////////////////////
class Engine
{
public:
    Engine(const std::string& name = "");
    virtual ~Engine();

    bool init(int argc, char **argv);

    LogManager& log();
    ResourceManager& res();
    PluginManager& plugins();
    InputManager& input();
    RenderManager& render();
    CodecManager& codecs();
    ThreadManager& threads();
    WindowManager& window();
    Config& config();

    void parseArgs(int argc, char** argv);

    void setRequestQuit(bool status);

    bool getRequestQuit() const;

    bool loadPlugins();

private:
    Config m_config;
    LogManager m_logManager;
    ResourceManager m_resourceManager;
    PluginManager m_pluginManager;
    InputManager m_inputManager;
    RenderManager m_renderManager;
    CodecManager m_codecManager;
    ThreadManager m_threadManager;
    WindowManager m_windowManager;
    EngineLua m_engineLua;

    std::string m_name;     ///< engine string identifier
    bool m_requestQuit;     ///< flag indicating a request to exit the program
};
////////////////////////////////////////////////////////////////////////////////
void setGlobalEngine(Engine& engine);
Engine& getEngine();
////////////////////////////////////////////////////////////////////////////////
#endif // __ENGINE_HPP__
