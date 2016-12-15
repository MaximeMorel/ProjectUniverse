////////////////////////////////////////////////////////////////////////////////
#include "imageCodecPNG.hpp"
#include "core/log/logManager.hpp"
#include "core/engine.hpp"
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
void abort_(const char * s, ...)
{
        va_list args;
        va_start(args, s);
        vfprintf(stderr, s, args);
        fprintf(stderr, "\n");
        va_end(args);
        abort();
}
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecPNG::load(ImageRGBAPtr image)
{
    class PNGLoader
    {
    public:
        PNGLoader()
            : fp(nullptr)
            , png_ptr(nullptr)
            , info_ptr(nullptr)
        {}
        ~PNGLoader()
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
                fclose(fp);
        }

        png_byte header[8];
        FILE *fp;
        png_structp png_ptr;
        png_infop info_ptr;
    };

    const char* file_name = image->getFileName().c_str();
    if (!file_name)
    {
        log().log() << "image resource is not a file\n";
        return false;
    }

    PNGLoader pngLoader;

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

    if (bit_depth != 8)
    {
        log().log() << file_name << ": bit depth " << bit_depth << " not supported\n";
        return false;
    }

    if (number_of_passes != 1)
    {
        log().log() << file_name << ": number of passes " << number_of_passes << " not supported\n";
        return false;
    }

    image->resize(width, height);
    png_size_t rowbytes = png_get_rowbytes(pngLoader.png_ptr, pngLoader.info_ptr);
    std::vector<png_byte> row(rowbytes);
    for (uint32_t y = 0; y < height; ++y)
    {
        png_read_row(pngLoader.png_ptr, &row.front(), nullptr);

        for (uint32_t x = 0; x < width; ++x)
        {
            if (color_type == PNG_COLOR_TYPE_RGB)
            {
                image->operator ()(x, y) = Vec4ui8(row[x*3 + 0], row[x*3 + 1], row[x*3 + 2], 255);
            }
            else if (color_type == PNG_COLOR_TYPE_RGB_ALPHA)
            {
                image->operator ()(x, y) = Vec4ui8(row[x*4 + 0], row[x*4 + 1], row[x*4 + 2], row[x*4 + 3]);
            }
            else if (color_type == PNG_COLOR_TYPE_GRAY)
            {
                log().log() << file_name << ": PNG_COLOR_TYPE_GRAY not supported\n";
                return false;
            }
            else if (color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
            {
                log().log() << file_name << ": PNG_COLOR_TYPE_GRAY_ALPHA not supported\n";
                return false;
            }
            else if (color_type == PNG_COLOR_TYPE_PALETTE)
            {
                log().log() << file_name << ": PNG_COLOR_TYPE_PALETTE not supported\n";
                return false;
            }
        }
    }

    return true;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecPNG::save(ImageRGBAPtr image, const std::string& filePath)
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////
