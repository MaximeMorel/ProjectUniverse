////////////////////////////////////////////////////////////////////////////////
#include "appNull.hpp"
#include "core/plugin/plugin.hpp"
#include "core/log/logManager.hpp"
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "appNull",
                          "appNull",
                          "app",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
ApplicationAppNull* app = nullptr;
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
        app = new ApplicationAppNull(*engine);
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
ApplicationAppNull::ApplicationAppNull(Engine& engine)
    : Application(engine)
{
    log().log() << "ApplicationAppNull start...\n";
}
////////////////////////////////////////////////////////////////////////////////
ApplicationAppNull::~ApplicationAppNull()
{
    log().log() << "ApplicationAppNull stop...\n";
}
////////////////////////////////////////////////////////////////////////////////
