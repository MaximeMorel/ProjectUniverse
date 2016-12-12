////////////////////////////////////////////////////////////////////////////////
#include "imageCodecSDL.hpp"
#include "core/log/logManager.hpp"
#include "core/engine.hpp"
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
        if (lib)
        {
            engine->addCodec(lib);
        }
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
    : ImageCodec(engine)
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

    log().log() << "flags " << surface->flags << "\n";
    log().log() << "pitch " << surface->pitch << "\n";
    log().log() << "offset " << surface->offset << "\n";
    log().log() << "resolution: " << surface->w << "x" << surface->h << "\n";

    log().log() << "BitsPerPixel: " << surface->format->BitsPerPixel << "\n";
    log().log() << "BytesPerPixel: " << surface->format->BytesPerPixel << "\n";
    //log().log() << "Rloss: " << surface->format->Rloss << "\n";
    //log().log() << "Gloss: " << surface->format->Gloss << "\n";
    //log().log() << "Bloss: " << surface->format->Bloss << "\n";
    //log().log() << "Aloss: " << surface->format->Aloss << "\n";
    //log().log() << "Rshift: " << surface->format->Rshift << "\n";
    //log().log() << "Gshift: " << surface->format->Gshift << "\n";
    //log().log() << "Bshift: " << surface->format->Bshift << "\n";
    //log().log() << "Ashift: " << surface->format->Ashift << "\n";
    //log().log() << "Rmask: " << surface->format->Rmask << "\n";
    //log().log() << "Gmask: " << surface->format->Gmask << "\n";
    //log().log() << "Bmask: " << surface->format->Bmask << "\n";
    //log().log() << "Amask: " << surface->format->Amask << "\n";

    // put data in ImagePtr

    SDL_FreeSurface(surface);

    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
