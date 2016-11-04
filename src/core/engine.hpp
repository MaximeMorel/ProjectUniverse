#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "log/logManager.hpp"
#include "resource/resourceManager.hpp"
#include "plugin/pluginManager.hpp"
#include "input/inputManager.hpp"
//#include "config.hpp"
////////////////////////////////////////////////////////////////////////////////
class Engine
{
public:
    Engine(const std::string& name = "");
    virtual ~Engine();

    LogManager& log();
    ResourceManager& res();
    PluginManager& plugins();
    InputManager& input();

private:
    //Config m_config;
    int m_config;
    LogManager m_logManager;
    ResourceManager m_resourecManager;
    PluginManager m_pluginManager;
    InputManager m_inputManager;

    std::string m_name;     ///< engine string identifier
};
////////////////////////////////////////////////////////////////////////////////
void setGlobalEngine(Engine& engine);
Engine& getEngine();
////////////////////////////////////////////////////////////////////////////////
#endif // __ENGINE_HPP__
