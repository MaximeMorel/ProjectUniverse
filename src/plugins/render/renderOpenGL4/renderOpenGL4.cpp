////////////////////////////////////////////////////////////////////////////////
#include "renderOpenGL4.hpp"
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "renderNull",
                          "renderNull",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
PluginRenderNull* lib = nullptr;
////////////////////////////////////////////////////////////////////////////////
PluginInfo* getPluginInfo()
{
    return &pluginInfo;
}
////////////////////////////////////////////////////////////////////////////////
Library* getLibInstance(Engine* engine)
{
    if (lib == nullptr)
    {
        lib = new PluginRenderNull(*engine);
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
PluginRenderNull::PluginRenderNull(Engine &engine)
    : Library(engine)
{
}
////////////////////////////////////////////////////////////////////////////////
PluginRenderNull::~PluginRenderNull()
{
}
////////////////////////////////////////////////////////////////////////////////