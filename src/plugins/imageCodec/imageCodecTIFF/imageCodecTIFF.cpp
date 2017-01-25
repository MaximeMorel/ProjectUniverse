////////////////////////////////////////////////////////////////////////////////
#include "imageCodecTIFF.hpp"
#include "core/log/logManager.hpp"
#include "core/codecs/codecManager.hpp"
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
    class TIFFreader
    {
    public:
        TIFFreader()
            : file(nullptr)
            , buf(nullptr)
        {}
        ~TIFFreader()
        {
            if (buf)
            {
                _TIFFfree(buf);
                buf = nullptr;
            }
            if (file)
            {
                TIFFClose(file);
                file = nullptr;
            }
        }

        TIFF* file;
        tdata_t buf;
    };

    if (!image)
        return false;

    size_t pos = image->getFileName().rfind('.');
    if (pos != std::string::npos)
    {
        if (image->getFileName().substr(pos) != ".tiff" && image->getFileName().substr(pos) != ".tif")
        {
            return false;
        }
    }

    TIFFreader tiffReader;

    tiffReader.file = TIFFOpen(image->getFileName().c_str(), "r");
    if (tiffReader.file == nullptr)
        return false;

    int ret = 0;
    uint16_t bitspersample = 0;
    ret = TIFFGetField(tiffReader.file, TIFFTAG_BITSPERSAMPLE, &bitspersample);
    if (ret != 1)
    {
        log().log() << image->getFileName() << ": cannot read TIFFTAG_BITSPERSAMPLE\n";
    }
    uint16_t samplesperpixel = 0;
    ret = TIFFGetField(tiffReader.file, TIFFTAG_SAMPLESPERPIXEL, &samplesperpixel);
    if (ret != 1)
    {
        log().log() << image->getFileName() << ": cannot read TIFFTAG_SAMPLESPERPIXEL\n";
    }
    uint32_t imagelength = 0;
    ret = TIFFGetField(tiffReader.file, TIFFTAG_IMAGELENGTH, &imagelength);
    if (ret != 1)
    {
        log().log() << image->getFileName() << ": cannot read TIFFTAG_IMAGELENGTH\n";
    }
    uint32_t imagewidth = 0;
    ret = TIFFGetField(tiffReader.file, TIFFTAG_IMAGEWIDTH, &imagewidth);
    if (ret != 1)
    {
        log().log() << image->getFileName() << ": cannot read TIFFTAG_IMAGEWIDTH\n";
    }

    Image::Type imageType = Image::Type::RGBA8;
    if (samplesperpixel == 3)
    {
        switch (bitspersample)
        {
        case 8:
            imageType = Image::Type::RGB8;
            break;
        default:
            log().log() << image->getFileName() << ": TIFFTAG_SAMPLESPERPIXEL (" << samplesperpixel << "), TIFFTAG_BITSPERSAMPLE (" << bitspersample << ") not supported\n";
            return false;
        }
    }
    else if (samplesperpixel == 4)
    {
        switch (bitspersample)
        {
        case 8:
            imageType = Image::Type::RGBA8;
            break;
        default:
            log().log() << image->getFileName() << ": TIFFTAG_SAMPLESPERPIXEL (" << samplesperpixel << "), TIFFTAG_BITSPERSAMPLE (" << bitspersample << ") not supported\n";
            return false;
        }
    }
    else
    {
        log().log() << image->getFileName() << ": TIFFTAG_SAMPLESPERPIXEL (" << samplesperpixel << "), TIFFTAG_BITSPERSAMPLE (" << bitspersample << ") not supported\n";
        return false;
    }
    image->setImageType(imageType);

    image->resize(imagewidth, imagelength);
    tmsize_t scanlineSize = TIFFScanlineSize(tiffReader.file);
    tiffReader.buf = _TIFFmalloc(scanlineSize);
    uint8_t* pixels = reinterpret_cast<uint8_t*>(tiffReader.buf);
    if (tiffReader.buf == nullptr)
    {
        log().log() << image->getFileName() << ": cannot allocate TIFF memory\n";
        return false;
    }
    int readStatus = 1;
    for (uint16_t row = 0; row < imagelength && readStatus == 1; ++row)
    {
        readStatus = TIFFReadScanline(tiffReader.file, tiffReader.buf, row);
        std::copy(pixels, pixels + scanlineSize, image->getui8(0, row));
    }

    if (readStatus != 1)
    {
        log().log() << image->getFileName() << ": TIFF decoding error\n";
        return false;
    }

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
