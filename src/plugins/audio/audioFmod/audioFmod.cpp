////////////////////////////////////////////////////////////////////////////////
#include "audioFmod.hpp"
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "audioFmod",
                          "audioFmod",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
PluginAudioFmod* lib = nullptr;
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
        lib = new PluginAudioFmod(*engine);
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
PluginAudioFmod::PluginAudioFmod(Engine &engine)
    : Library(engine)
{
}
////////////////////////////////////////////////////////////////////////////////
PluginAudioFmod::~PluginAudioFmod()
{
}
////////////////////////////////////////////////////////////////////////////////