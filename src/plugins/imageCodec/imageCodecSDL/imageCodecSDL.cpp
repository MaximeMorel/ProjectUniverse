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
    if (lib)
    {

    }
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
bool PluginImageCodecSDL::load(ImageRGBAPtr image)
{
    SDL_Surface* surface = IMG_Load(image->getFileName().c_str());
    if (surface == nullptr)
    {
        log().log() << "Image load " << image->getFileName() << " failed: " << IMG_GetError() << "\n";
        return false;
    }

    log().log() << "flags " << surface->flags << "\n";
    log().log() << "pitch " << surface->pitch << "\n";
    log().log() << "offset " << surface->offset << "\n";
    log().log() << "resolution: " << surface->w << "x" << surface->h << "\n";

    log().log() << "BitsPerPixel: " << surface->format->BitsPerPixel << "\n";
    log().log() << "BytesPerPixel: " << surface->format->BytesPerPixel << "\n";
    log().log() << "Rloss: " << surface->format->Rloss << "\n";
    log().log() << "Gloss: " << surface->format->Gloss << "\n";
    log().log() << "Bloss: " << surface->format->Bloss << "\n";
    log().log() << "Aloss: " << surface->format->Aloss << "\n";
    log().log() << "Rshift: " << surface->format->Rshift << "\n";
    log().log() << "Gshift: " << surface->format->Gshift << "\n";
    log().log() << "Bshift: " << surface->format->Bshift << "\n";
    log().log() << "Ashift: " << surface->format->Ashift << "\n";
    log().log() << "Rmask: " << surface->format->Rmask << "\n";
    log().log() << "Gmask: " << surface->format->Gmask << "\n";
    log().log() << "Bmask: " << surface->format->Bmask << "\n";
    log().log() << "Amask: " << surface->format->Amask << "\n";

    if (surface->format->Rmask == 0 &&
        surface->format->Gmask == 0 &&
        surface->format->Bmask == 0 &&
        surface->format->Amask == 0)
    {
        log().log() << "Image " << image->getFileName() << " is using palette.\n";
        return false;
    }

    // put data in ImagePtr
    image->resize(surface->w, surface->h);
    uint8_t* pixels = static_cast<uint8_t*>(surface->pixels);
    for (int h = 0; h < surface->h; ++h)
    {
        for (int w = 0 ; w < surface->w; ++w, pixels += surface->format->BytesPerPixel)
        {
            uint32_t v = 0;
            Vec4ui8 p;
            uint32_t pixel = 0;
            for (uint8_t i = 0; i < surface->format->BytesPerPixel; ++i)
            {
                pixel |= pixels[i] << (8*i);
            }
            if (surface->format->Rmask)
            {
                v = pixel & surface->format->Rmask;
                v >>= surface->format->Rshift;
                v <<= surface->format->Rloss;
                p.x = v;
            }

            if (surface->format->Gmask)
            {
                v = pixel & surface->format->Gmask;
                v >>= surface->format->Gshift;
                v <<= surface->format->Gloss;
                p.y = v;
            }

            if (surface->format->Bmask)
            {
                v = pixel & surface->format->Bmask;
                v >>= surface->format->Bshift;
                v <<= surface->format->Bloss;
                p.z = v;
            }

            if (surface->format->Amask)
            {
                v = pixel & surface->format->Amask;
                v >>= surface->format->Ashift;
                v <<= surface->format->Aloss;
                p.w = v;
            }

            image->operator()(w, h) = p;
        }
    }

    SDL_FreeSurface(surface);

    return true;
}
////////////////////////////////////////////////////////////////////////////////
