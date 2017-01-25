////////////////////////////////////////////////////////////////////////////////
#include "imageCodecPNG.hpp"
#include "core/log/logManager.hpp"
#include "core/codecs/codecManager.hpp"
//#include <functional>
#include <png.h>
#include <zlib.h>
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "imageCodecPNG",
                          "imageCodecPNG",
                          "imagecodec",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
PluginImageCodecPNG* lib = nullptr;
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
        lib = new PluginImageCodecPNG(*engine);
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
PluginImageCodecPNG::PluginImageCodecPNG(Engine &engine)
    : ImageCodec(engine)
{
    log().log() << "PluginImageCodecPNG start...\n";

    log().log() << "Compiled with libpng " << PNG_LIBPNG_VER_STRING << " using libpng " << png_libpng_ver << ".\n";
    log().log() << "Compiled with zlib " << ZLIB_VERSION << " using zlib " << zlib_version << ".\n";
}
////////////////////////////////////////////////////////////////////////////////
PluginImageCodecPNG::~PluginImageCodecPNG()
{
    log().log() << "PluginImageCodecPNG stop...\n";
}
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecPNG::load(Image* image)
{
    class PNGreader
    {
    public:
        PNGreader()
            : fp(nullptr)
            , png_ptr(nullptr)
            , info_ptr(nullptr)
        {}
        ~PNGreader()
        {
            if (png_ptr && info_ptr)
            {
                png_destroy_info_struct(png_ptr, &info_ptr);
                info_ptr = nullptr;
            }
            if (png_ptr)
            {
                png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
                png_ptr = nullptr;
            }
            if (fp)
            {
                fclose(fp);
                fp = nullptr;
            }
        }

        png_byte header[8];
        FILE* fp;
        png_structp png_ptr;
        png_infop info_ptr;
    };

    if (!image)
        return false;

    size_t pos = image->getFileName().rfind('.');
    if (pos != std::string::npos)
    {
        if (image->getFileName().substr(pos) != ".png")
        {
            return false;
        }
    }

    const char* file_name = image->getFileName().c_str();
    if (!file_name || image->getFileName().length() < 5) // min 5 chars to have something like x.png
    {
        log().log() << "image resource is not a file\n";
        return false;
    }

    PNGreader pngLoader;

    /* open file and test for it being a png */
    pngLoader.fp = fopen(file_name, "rb");
    if (!pngLoader.fp)
    {
        log().log() << file_name << "cannot be opened for reading\n";
        return false;
    }
    fread(pngLoader.header, 1, 8, pngLoader.fp);
    if (!png_check_sig(pngLoader.header, 8))
    {
        log().log() << file_name << " is not recognized as a PNG file\n";
        return false;
    }

    /* initialize stuff */
    pngLoader.png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!pngLoader.png_ptr)
    {
        log().log() << file_name << ": png_create_read_struct failed\n";
        return false;
    }

    pngLoader.info_ptr = png_create_info_struct(pngLoader.png_ptr);
    if (!pngLoader.info_ptr)
    {
        log().log() << file_name << ": png_create_info_struct failed\n";
        return false;
    }

    if (setjmp(png_jmpbuf(pngLoader.png_ptr)))
    {
        log().log() << file_name << ": Error during init_io\n";
        return false;
    }

    png_init_io(pngLoader.png_ptr, pngLoader.fp);
    png_set_sig_bytes(pngLoader.png_ptr, 8);

    png_read_info(pngLoader.png_ptr, pngLoader.info_ptr);

    uint32_t width = png_get_image_width(pngLoader.png_ptr, pngLoader.info_ptr);
    uint32_t height = png_get_image_height(pngLoader.png_ptr, pngLoader.info_ptr);
    png_byte color_type = png_get_color_type(pngLoader.png_ptr, pngLoader.info_ptr);
    png_byte bit_depth = png_get_bit_depth(pngLoader.png_ptr, pngLoader.info_ptr);

    int number_of_passes = png_set_interlace_handling(pngLoader.png_ptr);
    png_read_update_info(pngLoader.png_ptr, pngLoader.info_ptr);

    /* read file */
    if (setjmp(png_jmpbuf(pngLoader.png_ptr)))
    {
        log().log() << file_name << ": Error during read_image\n";
        return false;
    }

    if (number_of_passes != 1)
    {
        log().log() << file_name << ": number of passes " << number_of_passes << " not supported\n";
        return false;
    }

    //std::function<void(uint32_t y)> setRow = [&image](uint32_t y){};

    Image::Type imageType = Image::Type::RGBA8;
    if (color_type == PNG_COLOR_TYPE_RGB)
    {
        switch (bit_depth)
        {
        case 8:
            imageType = Image::Type::RGB8;
            break;
        case 16:
        default:
            log().log() << file_name << ": PNG_COLOR_TYPE_RGB (" << bit_depth << ") not supported\n";
            return false;
        }
    }
    else if (color_type == PNG_COLOR_TYPE_RGB_ALPHA)
    {
        switch (bit_depth)
        {
        case 8:
            imageType = Image::Type::RGBA8;
            break;
        case 16:
        default:
            log().log() << file_name << ": PNG_COLOR_TYPE_RGB_ALPHA (" << bit_depth << ") not supported\n";
            return false;
        }
    }
    else if (color_type == PNG_COLOR_TYPE_GRAY)
    {
        switch (bit_depth)
        {
        case 8:
            imageType = Image::Type::GRAY8;
            break;
        case 1:
        case 2:
        case 4:
        case 16:
        default:
            log().log() << file_name << ": PNG_COLOR_TYPE_GRAY (" << bit_depth << ") not supported\n";
            return false;
        }
    }
    else if (color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    {
        switch (bit_depth)
        {
        case 8:
        case 16:
        default:
            log().log() << file_name << ": PNG_COLOR_TYPE_GRAY_ALPHA (" << bit_depth << ") not supported\n";
            return false;
        }
    }
    else if (color_type == PNG_COLOR_TYPE_PALETTE)
    {
        switch (bit_depth)
        {
        case 1:
        case 2:
        case 4:
        case 8:
        default:
            log().log() << file_name << ": PNG_COLOR_TYPE_PALETTE (" << bit_depth << ") not supported\n";
            return false;
        }
    }
    else
    {
        log().log() << file_name << ": PNG_COLOR_TYPE " << color_type << " (" << bit_depth << ") not supported\n";
        return false;
    }
    image->setImageType(imageType);

    image->resize(width, height);
    png_size_t rowbytes = png_get_rowbytes(pngLoader.png_ptr, pngLoader.info_ptr);
    if (rowbytes != (image->bitsPerPixel() / 8) * image->width())
    {
        log().log() << file_name << ": Bad row length\n";
    }
    for (uint32_t y = 0; y < height; ++y)
    {
        png_read_row(pngLoader.png_ptr, image->getui8(0, y), nullptr);
    }

    return true;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecPNG::save(Image* image, const std::string& filePath)
{
    class PNGwriter
    {
    public:
        PNGwriter()
            : fp(nullptr)
            , png_ptr(nullptr)
            , info_ptr(nullptr)
        {}
        ~PNGwriter()
        {
            if (png_ptr && info_ptr)
            {
                png_destroy_info_struct(png_ptr, &info_ptr);
                info_ptr = nullptr;
            }
            if (png_ptr)
            {
                png_destroy_write_struct(&png_ptr, &info_ptr);
                png_ptr = nullptr;
            }
            if (fp)
            {
                fclose(fp);
                fp = nullptr;
            }
        }

        FILE* fp;
        png_structp png_ptr;
        png_infop info_ptr;
    };

    if (!image)
        return false;

    size_t pos = filePath.rfind('.');
    if (pos != std::string::npos)
    {
        if (filePath.substr(pos) != ".png")
        {
            return false;
        }
    }

    const char* file_name = filePath.c_str();
    if (!file_name || filePath.length() < 5) // min 5 chars to have something like x.png
    {
        log().log() << "image resource is not a file\n";
        return false;
    }

    PNGwriter pngWriter;

    pngWriter.fp = fopen(file_name, "wb");
    if (!pngWriter.fp)
    {
        log().log() << file_name << "cannot be opened for writing\n";
        return false;
    }

    /* initialize stuff */
    pngWriter.png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!pngWriter.png_ptr)
    {
        log().log() << file_name << ": png_create_write_struct failed\n";
        return false;
    }

    pngWriter.info_ptr = png_create_info_struct(pngWriter.png_ptr);
    if (!pngWriter.info_ptr)
    {
        log().log() << file_name << ": png_create_info_struct failed\n";
        return false;
    }

    if (setjmp(png_jmpbuf(pngWriter.png_ptr)))
    {
        log().log() << file_name << ": Error during init_io\n";
        return false;
    }

    png_init_io(pngWriter.png_ptr, pngWriter.fp);

    /* write header */
    if (setjmp(png_jmpbuf(pngWriter.png_ptr)))
    {
        log().log() << file_name << ": Error during writing header\n";
        return false;
    }

    int bit_depth = 8;
    int color_type = PNG_COLOR_TYPE_RGB_ALPHA;
    switch (image->imageType())
    {
    case Image::Type::GRAY8:
        bit_depth = 8;
        color_type = PNG_COLOR_TYPE_GRAY;
        break;
    case Image::Type::RGB8:
        bit_depth = 8;
        color_type = PNG_COLOR_TYPE_RGB;
        break;
    case Image::Type::RGBA8:
        bit_depth = 8;
        color_type = PNG_COLOR_TYPE_RGB_ALPHA;
        break;
    case Image::Type::GRAYFP32:
    case Image::Type::RGBFP32:
    case Image::Type::RGBAFP32:
    default:
        log().log() << file_name << ": png write not supported for " << image->channels() << " channels and bit depth " << image->bitsPerComponent() << "\n";
        return false;
    }

    Vec2ui r = image->resolution();
    png_set_IHDR(pngWriter.png_ptr, pngWriter.info_ptr, r.x, r.y,
                 bit_depth, color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(pngWriter.png_ptr, pngWriter.info_ptr);

    /* write bytes */
    if (setjmp(png_jmpbuf(pngWriter.png_ptr)))
    {
        log().log() << file_name << ": Error during writing bytes\n";
        return false;
    }

    for (uint32_t y = 0; y < r.y; ++y)
    {
        png_write_row(pngWriter.png_ptr, image->getui8(0, y));
    }

    /* end write */
    if (setjmp(png_jmpbuf(pngWriter.png_ptr)))
    {
        log().log() << file_name << ": Error during end of write\n";
        return false;
    }

    png_write_end(pngWriter.png_ptr, NULL);

    return true;
}
////////////////////////////////////////////////////////////////////////////////
