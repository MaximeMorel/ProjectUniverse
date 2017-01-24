////////////////////////////////////////////////////////////////////////////////
#include "imageCodecTIFF.hpp"
#include "core/log/logManager.hpp"
#include "core/engine.hpp"
#include <tiffio.h>
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "imageCodecTIFF",
                          "imageCodecTIFF",
                          "imagecodec",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
PluginImageCodecTIFF* lib = nullptr;
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
        lib = new PluginImageCodecTIFF(*engine);
        if (lib)
        {
            engine->codecs().addImageCodec(lib);
        }
    }
    return lib;
}
////////////////////////////////////////////////////////////////////////////////
void closeLibInstance()
{
    if (lib)
    {
        lib->getEngine().codecs().removeImageCodec(lib);
    }
    delete lib;
    lib = nullptr;
}
////////////////////////////////////////////////////////////////////////////////
PluginImageCodecTIFF::PluginImageCodecTIFF(Engine &engine)
    : ImageCodec(engine)
{
    log().log() << "PluginImageCodecTIFF start...\n";
}
////////////////////////////////////////////////////////////////////////////////
PluginImageCodecTIFF::~PluginImageCodecTIFF()
{
    log().log() << "PluginImageCodecTIFF stop...\n";
}
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecTIFF::load(Image* image)
{
    if (!image)
        return false;

    TIFF* file = nullptr;
    file = TIFFOpen(image->getFileName().c_str(), "r");
    if (file == nullptr)
        return false;

    TIFFClose(file);

    return true;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecTIFF::save(Image* image, const std::string& filePath)
{
    if (!image)
        return false;

    return true;
}
////////////////////////////////////////////////////////////////////////////////
