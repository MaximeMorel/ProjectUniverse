////////////////////////////////////////////////////////////////////////////////
#include "imageCodecSDL.hpp"
#include <SDL_image.h>
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "imageCodecSDL",
                          "imageCodecSDL",
                          "imagecodec",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
PluginImageCodecSDL* lib = nullptr;
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
        lib = new PluginImageCodecSDL(*engine);
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
PluginImageCodecSDL::PluginImageCodecSDL(Engine &engine)
    : Library(engine)
{
    log().log() << "PluginImageCodecSDL start...\n";

    const SDL_version* v = IMG_Linked_Version();
    if (v)
    {
        log().log() << "SDL_image " << v->major << "." << v->minor << "." << v->patch << "\n";
    }

    int initFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    int ret = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    if (ret != 0 && ret != initFlags)
    {
        log().log() << "IMG_Init(" << initFlags << ") error: " << ret << "\n";
        log().log() << IMG_GetError() << ret << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////
PluginImageCodecSDL::~PluginImageCodecSDL()
{
    log().log() << "PluginImageCodecSDL stop...\n";
    IMG_Quit();
}
////////////////////////////////////////////////////////////////////////////////
ImagePtr PluginImageCodecSDL::load(const std::string& fileName)
{
    SDL_Surface* surface = IMG_Load(fileName.c_str());
    if (surface == nullptr)
    {
        log().log() << "Image load " << fileName << " failed: " << IMG_GetError() << "\n";
        return nullptr;
    }

    // put data in ImagePtr

    SDL_FreeSurface(surface);

    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
