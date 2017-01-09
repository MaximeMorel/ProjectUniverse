////////////////////////////////////////////////////////////////////////////////
#include "audioCodecOggVorbis.hpp"
#include "core/log/logManager.hpp"
#include "core/engine.hpp"
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "audioCodecOggVorbis",
                          "audioCodecOggVorbis",
                          "audiocodec",
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
        if (lib)
        {
            engine->codecs().addAudioCodec(lib);
        }
    }
    return lib;
}
////////////////////////////////////////////////////////////////////////////////
void closeLibInstance()
{
    if (lib)
    {
        lib->getEngine().codecs().removeAudioCodec(lib);
    }
    delete lib;
    lib = nullptr;
}
////////////////////////////////////////////////////////////////////////////////
PluginAudioCodecOggVorbis::PluginAudioCodecOggVorbis(Engine &engine)
    : AudioCodec(engine)
{
    log().log() << "PluginAudioCodecOggVorbis start...\n";
}
////////////////////////////////////////////////////////////////////////////////
PluginAudioCodecOggVorbis::~PluginAudioCodecOggVorbis()
{
    log().log() << "PluginAudioCodecOggVorbis stop...\n";
}
////////////////////////////////////////////////////////////////////////////////
