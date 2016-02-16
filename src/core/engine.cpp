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
///
Engine::Engine()
{
    m_logManager.log() << "Engine init..." << std::endl;

    char buf[256];
    m_logManager.log() << getcwd(buf, 256) << std::endl;

    Plugin pluginApp("../app/AppNull/libAppNull.so");
    PFNgetPluginInfo f = (PFNgetPluginInfo)(pluginApp.getSymbol("getPluginInfo"));
    if (f)
    {
        PluginInfo* p = f();
        m_logManager.log() << p->name << " " << p->major << "." << p->minor << "\n";
        m_logManager.log() << p->info << std::endl;
    }

    PFNrunPlugin r = (PFNrunPlugin)(pluginApp.getSymbol("runPlugin"));
    if (r)
    {
        r(this);
    }
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
