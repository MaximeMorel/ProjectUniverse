////////////////////////////////////////////////////////////////////////////////
#include "engine.hpp"
#include <unistd.h>
////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
Engine::Engine()
{
    gEngine = this;
    m_logManager.log() << FILEINFO << "Engine init..." << std::endl;

    char buf[256];
    m_logManager.log() << getcwd(buf, 256) << std::endl;

    Plugin pluginApp("../app/AppNull/libAppNull.so");
    m_logManager.log() << pluginApp << std::endl;

    PFNrunPlugin r = (PFNrunPlugin)(pluginApp.getSymbol("runPlugin"));
    if (r)
    {
        r(this);
    }

    // AppTest
    pluginApp = Plugin("../app/AppTest/libAppTest.so");
    m_logManager.log() << pluginApp  << std::endl;

    PFNgetAppInstance getAppInstance = (PFNgetAppInstance)(pluginApp.getSymbol("getAppInstance"));
    Application* appTest = getAppInstance(this);
    PFNcloseAppInstance closeAppInstance = (PFNcloseAppInstance)(pluginApp.getSymbol("closeAppInstance"));
    closeAppInstance();
}
////////////////////////////////////////////////////////////////////////////////
Engine::~Engine()
{
    m_logManager.log() << "Engine close..." << std::endl;
}
////////////////////////////////////////////////////////////////////////////////
LogManager& Engine::log()
{
    return m_logManager;
}
////////////////////////////////////////////////////////////////////////////////
Engine* getEngine()
{
    return gEngine;
}
