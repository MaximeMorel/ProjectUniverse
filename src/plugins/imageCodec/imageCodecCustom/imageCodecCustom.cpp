////////////////////////////////////////////////////////////////////////////////
#include "imageCodecCustom.hpp"
#include "core/log/logManager.hpp"
#include "core/engine.hpp"
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "imageCodecCustom",
                          "imageCodecCustom",
                          "imagecodec",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
PluginImageCodecCustom* lib = nullptr;
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
        lib = new PluginImageCodecCustom(*engine);
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
PluginImageCodecCustom::PluginImageCodecCustom(Engine &engine)
    : ImageCodec(engine)
{
    log().log() << "PluginImageCodecCustom start...\n";
}
////////////////////////////////////////////////////////////////////////////////
PluginImageCodecCustom::~PluginImageCodecCustom()
{
    log().log() << "PluginImageCodecCustom stop...\n";
}
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecCustom::load(ImagePtr image)
{
    return load(image.get());
}
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecCustom::load(Image* image)
{
    if (!image)
        return false;

    size_t pos = image->getFileName().rfind('.');
    if (pos != std::string::npos)
    {
        if (image->getFileName().substr(pos) == ".dds")
        {
            return loadDDS(image);
        }
    }

    return false;
}
////////////////////////////////////////////////////////////////////////////////
struct DDS_PIXELFORMAT
{
    uint32_t dwSize;
    uint32_t dwFlags;
    uint32_t dwFourCC;
    uint32_t dwRGBBitCount;
    uint32_t dwRBitMask;
    uint32_t dwGBitMask;
    uint32_t dwBBitMask;
    uint32_t dwABitMask;
};
typedef struct
{
    uint32_t           dwSize;
    uint32_t           dwFlags;
    uint32_t           dwHeight;
    uint32_t           dwWidth;
    uint32_t           dwPitchOrLinearSize;
    uint32_t           dwDepth;
    uint32_t           dwMipMapCount;
    uint32_t           dwReserved1[11];
    DDS_PIXELFORMAT    ddspf;
    uint32_t           dwCaps;
    uint32_t           dwCaps2;
    uint32_t           dwCaps3;
    uint32_t           dwCaps4;
    uint32_t           dwReserved2;
} DDS_HEADER;
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecCustom::loadDDS(Image* image)
{
    std::ifstream file(image->getFileName(), std::ios::in | std::ios::binary);

    uint32_t dwMagic;
    char* s = reinterpret_cast<char*>(&dwMagic);
    file.read(s, sizeof(dwMagic));
    if (dwMagic != 0x20534444)
    {
        log().log() << image->getFileName() << ": not a DDS file\n";
        return false;
    }
    DDS_HEADER ddsHeader;
    s = reinterpret_cast<char*>(&ddsHeader);
    file.read(s, sizeof(ddsHeader));

    return false;
}
////////////////////////////////////////////////////////////////////////////////
