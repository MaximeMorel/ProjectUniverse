////////////////////////////////////////////////////////////////////////////////
#include "OpenDD.hpp"
#include "core/log/logManager.hpp"
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "OpenDD",
                          "OpenDD",
                          "app",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
ApplicationOpenDD* app = nullptr;
////////////////////////////////////////////////////////////////////////////////
const PluginInfo* getPluginInfo()
{
    return &pluginInfo;
}
////////////////////////////////////////////////////////////////////////////////
Application* getAppInstance(Engine* engine)
{
    if (app == nullptr)
    {
        app = new ApplicationOpenDD(*engine);
    }
    return app;
}
////////////////////////////////////////////////////////////////////////////////
void closeAppInstance()
{
    delete app;
    app = nullptr;
}
////////////////////////////////////////////////////////////////////////////////
ApplicationOpenDD::ApplicationOpenDD(Engine& engine)
    : Application(engine)
{
    log().log() << "ApplicationOpenDD start...\n";
}
////////////////////////////////////////////////////////////////////////////////
ApplicationOpenDD::~ApplicationOpenDD()
{
    log().log() << "ApplicationOpenDD start...\n";
}
////////////////////////////////////////////////////////////////////////////////
