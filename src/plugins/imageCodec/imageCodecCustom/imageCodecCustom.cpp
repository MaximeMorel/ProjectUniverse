////////////////////////////////////////////////////////////////////////////////
#include "imageCodecCustom.hpp"
#include "core/log/logManager.hpp"
#include "core/codecs/codecManager.hpp"
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
            codecs().addImageCodec(lib);
        }
    }
    return lib;
}
////////////////////////////////////////////////////////////////////////////////
void closeLibInstance()
{
    if (lib)
    {
        codecs().removeImageCodec(lib);
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
bool PluginImageCodecCustom::load(Image* image)
{
    if (!image)
        return false;

    size_t pos = image->getFileName().rfind('.');
    if (pos != std::string::npos)
    {
        if (image->getFileName().substr(pos) == ".bmp")
        {
            return loadBMP(image);
        }
        else if (image->getFileName().substr(pos) == ".pbm")
        {
            return loadPBM(image);
        }
        else if (image->getFileName().substr(pos) == ".pgm")
        {
            return loadPGM(image);
        }
        else if (image->getFileName().substr(pos) == ".ppm")
        {
            return loadPPM(image);
        }
        else if (image->getFileName().substr(pos) == ".dds")
        {
            return loadDDS(image);
        }
    }

    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecCustom::loadBMP(Image* image)
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecCustom::loadPBM(Image* image)
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecCustom::loadPGM(Image* image)
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecCustom::loadPPM(Image* image)
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////
#define DDPF_ALPHAPIXELS    0x1
#define DDPF_ALPHA          0x2
#define DDPF_FOURCC         0x4
#define DDPF_RGB            0x40
#define DDPF_YUV            0x200
#define DDPF_LUMINANCE      0x20000
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
typedef enum DXGI_FORMAT {
    DXGI_FORMAT_UNKNOWN                     = 0,
    DXGI_FORMAT_R32G32B32A32_TYPELESS       = 1,
    DXGI_FORMAT_R32G32B32A32_FLOAT          = 2,
    DXGI_FORMAT_R32G32B32A32_UINT           = 3,
    DXGI_FORMAT_R32G32B32A32_SINT           = 4,
    DXGI_FORMAT_R32G32B32_TYPELESS          = 5,
    DXGI_FORMAT_R32G32B32_FLOAT             = 6,
    DXGI_FORMAT_R32G32B32_UINT              = 7,
    DXGI_FORMAT_R32G32B32_SINT              = 8,
    DXGI_FORMAT_R16G16B16A16_TYPELESS       = 9,
    DXGI_FORMAT_R16G16B16A16_FLOAT          = 10,
    DXGI_FORMAT_R16G16B16A16_UNORM          = 11,
    DXGI_FORMAT_R16G16B16A16_UINT           = 12,
    DXGI_FORMAT_R16G16B16A16_SNORM          = 13,
    DXGI_FORMAT_R16G16B16A16_SINT           = 14,
    DXGI_FORMAT_R32G32_TYPELESS             = 15,
    DXGI_FORMAT_R32G32_FLOAT                = 16,
    DXGI_FORMAT_R32G32_UINT                 = 17,
    DXGI_FORMAT_R32G32_SINT                 = 18,
    DXGI_FORMAT_R32G8X24_TYPELESS           = 19,
    DXGI_FORMAT_D32_FLOAT_S8X24_UINT        = 20,
    DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS    = 21,
    DXGI_FORMAT_X32_TYPELESS_G8X24_UINT     = 22,
    DXGI_FORMAT_R10G10B10A2_TYPELESS        = 23,
    DXGI_FORMAT_R10G10B10A2_UNORM           = 24,
    DXGI_FORMAT_R10G10B10A2_UINT            = 25,
    DXGI_FORMAT_R11G11B10_FLOAT             = 26,
    DXGI_FORMAT_R8G8B8A8_TYPELESS           = 27,
    DXGI_FORMAT_R8G8B8A8_UNORM              = 28,
    DXGI_FORMAT_R8G8B8A8_UNORM_SRGB         = 29,
    DXGI_FORMAT_R8G8B8A8_UINT               = 30,
    DXGI_FORMAT_R8G8B8A8_SNORM              = 31,
    DXGI_FORMAT_R8G8B8A8_SINT               = 32,
    DXGI_FORMAT_R16G16_TYPELESS             = 33,
    DXGI_FORMAT_R16G16_FLOAT                = 34,
    DXGI_FORMAT_R16G16_UNORM                = 35,
    DXGI_FORMAT_R16G16_UINT                 = 36,
    DXGI_FORMAT_R16G16_SNORM                = 37,
    DXGI_FORMAT_R16G16_SINT                 = 38,
    DXGI_FORMAT_R32_TYPELESS                = 39,
    DXGI_FORMAT_D32_FLOAT                   = 40,
    DXGI_FORMAT_R32_FLOAT                   = 41,
    DXGI_FORMAT_R32_UINT                    = 42,
    DXGI_FORMAT_R32_SINT                    = 43,
    DXGI_FORMAT_R24G8_TYPELESS              = 44,
    DXGI_FORMAT_D24_UNORM_S8_UINT           = 45,
    DXGI_FORMAT_R24_UNORM_X8_TYPELESS       = 46,
    DXGI_FORMAT_X24_TYPELESS_G8_UINT        = 47,
    DXGI_FORMAT_R8G8_TYPELESS               = 48,
    DXGI_FORMAT_R8G8_UNORM                  = 49,
    DXGI_FORMAT_R8G8_UINT                   = 50,
    DXGI_FORMAT_R8G8_SNORM                  = 51,
    DXGI_FORMAT_R8G8_SINT                   = 52,
    DXGI_FORMAT_R16_TYPELESS                = 53,
    DXGI_FORMAT_R16_FLOAT                   = 54,
    DXGI_FORMAT_D16_UNORM                   = 55,
    DXGI_FORMAT_R16_UNORM                   = 56,
    DXGI_FORMAT_R16_UINT                    = 57,
    DXGI_FORMAT_R16_SNORM                   = 58,
    DXGI_FORMAT_R16_SINT                    = 59,
    DXGI_FORMAT_R8_TYPELESS                 = 60,
    DXGI_FORMAT_R8_UNORM                    = 61,
    DXGI_FORMAT_R8_UINT                     = 62,
    DXGI_FORMAT_R8_SNORM                    = 63,
    DXGI_FORMAT_R8_SINT                     = 64,
    DXGI_FORMAT_A8_UNORM                    = 65,
    DXGI_FORMAT_R1_UNORM                    = 66,
    DXGI_FORMAT_R9G9B9E5_SHAREDEXP          = 67,
    DXGI_FORMAT_R8G8_B8G8_UNORM             = 68,
    DXGI_FORMAT_G8R8_G8B8_UNORM             = 69,
    DXGI_FORMAT_BC1_TYPELESS                = 70,
    DXGI_FORMAT_BC1_UNORM                   = 71,
    DXGI_FORMAT_BC1_UNORM_SRGB              = 72,
    DXGI_FORMAT_BC2_TYPELESS                = 73,
    DXGI_FORMAT_BC2_UNORM                   = 74,
    DXGI_FORMAT_BC2_UNORM_SRGB              = 75,
    DXGI_FORMAT_BC3_TYPELESS                = 76,
    DXGI_FORMAT_BC3_UNORM                   = 77,
    DXGI_FORMAT_BC3_UNORM_SRGB              = 78,
    DXGI_FORMAT_BC4_TYPELESS                = 79,
    DXGI_FORMAT_BC4_UNORM                   = 80,
    DXGI_FORMAT_BC4_SNORM                   = 81,
    DXGI_FORMAT_BC5_TYPELESS                = 82,
    DXGI_FORMAT_BC5_UNORM                   = 83,
    DXGI_FORMAT_BC5_SNORM                   = 84,
    DXGI_FORMAT_B5G6R5_UNORM                = 85,
    DXGI_FORMAT_B5G5R5A1_UNORM              = 86,
    DXGI_FORMAT_B8G8R8A8_UNORM              = 87,
    DXGI_FORMAT_B8G8R8X8_UNORM              = 88,
    DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM  = 89,
    DXGI_FORMAT_B8G8R8A8_TYPELESS           = 90,
    DXGI_FORMAT_B8G8R8A8_UNORM_SRGB         = 91,
    DXGI_FORMAT_B8G8R8X8_TYPELESS           = 92,
    DXGI_FORMAT_B8G8R8X8_UNORM_SRGB         = 93,
    DXGI_FORMAT_BC6H_TYPELESS               = 94,
    DXGI_FORMAT_BC6H_UF16                   = 95,
    DXGI_FORMAT_BC6H_SF16                   = 96,
    DXGI_FORMAT_BC7_TYPELESS                = 97,
    DXGI_FORMAT_BC7_UNORM                   = 98,
    DXGI_FORMAT_BC7_UNORM_SRGB              = 99,
    DXGI_FORMAT_AYUV                        = 100,
    DXGI_FORMAT_Y410                        = 101,
    DXGI_FORMAT_Y416                        = 102,
    DXGI_FORMAT_NV12                        = 103,
    DXGI_FORMAT_P010                        = 104,
    DXGI_FORMAT_P016                        = 105,
    DXGI_FORMAT_420_OPAQUE                  = 106,
    DXGI_FORMAT_YUY2                        = 107,
    DXGI_FORMAT_Y210                        = 108,
    DXGI_FORMAT_Y216                        = 109,
    DXGI_FORMAT_NV11                        = 110,
    DXGI_FORMAT_AI44                        = 111,
    DXGI_FORMAT_IA44                        = 112,
    DXGI_FORMAT_P8                          = 113,
    DXGI_FORMAT_A8P8                        = 114,
    DXGI_FORMAT_B4G4R4A4_UNORM              = 115,
    DXGI_FORMAT_P208                        = 130,
    DXGI_FORMAT_V208                        = 131,
    DXGI_FORMAT_V408                        = 132,
    DXGI_FORMAT_FORCE_UINT                  = 0xffffffff
} DXGI_FORMAT;
typedef enum D3D10_RESOURCE_DIMENSION
{
    D3D10_RESOURCE_DIMENSION_UNKNOWN    = 0,
    D3D10_RESOURCE_DIMENSION_BUFFER     = 1,
    D3D10_RESOURCE_DIMENSION_TEXTURE1D  = 2,
    D3D10_RESOURCE_DIMENSION_TEXTURE2D  = 3,
    D3D10_RESOURCE_DIMENSION_TEXTURE3D  = 4
} D3D10_RESOURCE_DIMENSION;
typedef struct
{
    DXGI_FORMAT              dxgiFormat;
    D3D10_RESOURCE_DIMENSION resourceDimension;
    uint32_t                 miscFlag;
    uint32_t                 arraySize;
    uint32_t                 miscFlags2;
} DDS_HEADER_DXT10;
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecCustom::loadDDS(Image* image)
{
    std::ifstream file(image->getFileName(), std::ios::in | std::ios::binary);

    uint32_t dwMagic;
    char* s = reinterpret_cast<char*>(&dwMagic);
    file.read(s, sizeof(dwMagic));
    if (dwMagic != 0x20534444) // 0x20534444 = "DDS "
    {
        log().log() << image->getFileName() << ": not a DDS file\n";
        return false;
    }
    DDS_HEADER ddsHeader;
    s = reinterpret_cast<char*>(&ddsHeader);
    file.read(s, sizeof(ddsHeader));
    if (ddsHeader.ddspf.dwFlags == DDPF_FOURCC && ddsHeader.ddspf.dwFourCC == 0x30315844) // 0x30315844 = DX10
    {
        DDS_HEADER_DXT10 ddsHeaderDXT10;
        s = reinterpret_cast<char*>(&ddsHeaderDXT10);
        file.read(s, sizeof(ddsHeader));

        log().log() << image->getFileName() << ": DX10 not supported\n";
        return false;
    }

    if (ddsHeader.ddspf.dwFlags != DDPF_FOURCC)
    {
        log().log() << image->getFileName() << ": only compressed dds is supported (DDPF_FOURCC)\n";
        return false;
    }

    // 0x31545844 = "DXT1"
    // 0x32545844 = "DXT2"
    // 0x33545844 = "DXT3"
    // 0x34545844 = "DXT4"
    // 0x35545844 = "DXT5"

    int blocksize = 16;
    Image::Type imageType = Image::Type::RGBA8;
    if (ddsHeader.ddspf.dwFourCC == 0x31545844)
    {
        imageType = Image::Type::RGBADXT1;
        blocksize = 8;
    }
    image->setImageType(imageType);

    image->resize(ddsHeader.dwWidth, ddsHeader.dwHeight);

    unsigned int size = ((ddsHeader.dwWidth+3)/4)*((ddsHeader.dwHeight+3)/4) * blocksize;
    s = reinterpret_cast<char*>(image->getui8(0, 0));
    file.read(s, size);

    return true;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecCustom::save(Image* image, const std::string& filePath)
{
    if (!image)
        return false;

    size_t pos = filePath.rfind('.');
    if (pos != std::string::npos && filePath.length() >= 5) // min 5 chars to have something like x.ppm
    {
        if (filePath.substr(pos) == ".bmp")
        {
            return saveBMP(image, filePath);
        }
        else if (filePath.substr(pos) == ".pbm")
        {
            return savePBM(image, filePath);
        }
        else if (filePath.substr(pos) == ".pgm")
        {
            return savePGM(image, filePath);
        }
        else if (filePath.substr(pos) == ".ppm")
        {
            return savePPM(image, filePath);
        }
        else if (filePath.substr(pos) == ".dds")
        {
            return saveDDS(image, filePath);
        }
    }

    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecCustom::saveBMP(Image* image, const std::string& filePath)
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecCustom::savePBM(Image* image, const std::string& filePath)
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecCustom::savePGM(Image* image, const std::string& filePath)
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecCustom::savePPM(Image* image, const std::string& filePath)
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecCustom::saveDDS(Image* image, const std::string& filePath)
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////
