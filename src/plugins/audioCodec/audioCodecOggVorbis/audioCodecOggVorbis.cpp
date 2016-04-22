////////////////////////////////////////////////////////////////////////////////
#include "audioCodecOggVorbis.hpp"
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "audioCodecOggVorbis",
                          "audioCodecOggVorbis",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
PluginAudioCodecOggVorbis* lib = nullptr;
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
        lib = new PluginAudioCodecOggVorbis(*engine);
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
PluginAudioCodecOggVorbis::PluginAudioCodecOggVorbis(Engine &engine)
    : Library(engine)
{
}
////////////////////////////////////////////////////////////////////////////////
PluginAudioCodecOggVorbis::~PluginAudioCodecOggVorbis()
{
}
////////////////////////////////////////////////////////////////////////////////
