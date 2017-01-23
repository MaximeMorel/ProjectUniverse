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
    RenderManager& render();
    CodecManager& codecs();
    ThreadManager& thread();

    void setRequestQuit(bool status)
    {
        m_requestQuit = status;
    }

    bool getRequestQuit() const
    {
        return m_requestQuit;
    }

private:
    //Config m_config;
    int m_config;
    LogManager m_logManager;
    ResourceManager m_resourceManager;
    PluginManager m_pluginManager;
    InputManager m_inputManager;
    RenderManager m_renderManager;
    CodecManager m_codecManager;
    ThreadManager m_threadManager;

    std::string m_name;     ///< engine string identifier
    bool m_requestQuit;     ///< flag indicating a request to exit the program
};
////////////////////////////////////////////////////////////////////////////////
void setGlobalEngine(Engine& engine);
Engine& getEngine();
////////////////////////////////////////////////////////////////////////////////
#endif // __ENGINE_HPP__
