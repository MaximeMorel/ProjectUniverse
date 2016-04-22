////////////////////////////////////////////////////////////////////////////////
#include "renderVulkan.hpp"
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "renderVulkan",
                          "renderVulkan",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
PluginRenderVulkan* lib = nullptr;
////////////////////////////////////////////////////////////////////////////////
const PluginInfo* getPluginInfo()
{
    return &pluginInfo;
}
////////////////////////////////////////////////////////////////////////////////
Library* getLibInstance(Engine* engine)
{
    if (lib == nullptr)
    {
        lib = new PluginRenderVulkan(*engine);
    }
    return lib;
}
////////////////////////////////////////////////////////////////////////////////
void closeLibInstance()
{
    delete lib;
    lib = nullptr;
}
////////////////////////////////////////////////////////////////////////////////
PluginRenderVulkan::PluginRenderVulkan(Engine &engine)
    : Library(engine)
{
}
////////////////////////////////////////////////////////////////////////////////
PluginRenderVulkan::~PluginRenderVulkan()
{
}
////////////////////////////////////////////////////////////////////////////////