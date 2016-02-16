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
    PFNgetPluginInfo* f = static_cast<PFNgetPluginInfo*>(pluginApp.getSymbol("getPluginInfo"));
    PluginInfo* p = (f)();
    m_logManager.log() << p->name << std::endl;
    m_logManager.log() << p->info << std::endl;
    m_logManager.log() << p->major << std::endl;
    m_logManager.log() << p->minor << std::endl;
}
////////////////////////////////////////////////////////////////////////////////
Engine::~Engine()
{
    m_logManager.log() << "Engine close..." << std::endl;
}
////////////////////////////////////////////////////////////////////////////////
