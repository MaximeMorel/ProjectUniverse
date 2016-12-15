////////////////////////////////////////////////////////////////////////////////
#include "imageCodecJPEG.hpp"
#include "core/log/logManager.hpp"
#include "core/engine.hpp"
#include <jpeglib.h>
#include <setjmp.h>
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "imageCodecJPEG",
                          "imageCodecJPEG",
                          "imagecodec",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
PluginImageCodecJPEG* lib = nullptr;
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
        lib = new PluginImageCodecJPEG(*engine);
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
PluginImageCodecJPEG::PluginImageCodecJPEG(Engine &engine)
    : ImageCodec(engine)
{
    log().log() << "PluginImageCodecJPEG start...\n";
}
////////////////////////////////////////////////////////////////////////////////
PluginImageCodecJPEG::~PluginImageCodecJPEG()
{
    log().log() << "PluginImageCodecJPEG stop...\n";
}
////////////////////////////////////////////////////////////////////////////////
struct my_error_mgr
{
    struct jpeg_error_mgr pub;    /* "public" fields */
    jmp_buf setjmp_buffer;        /* for return to caller */
};
typedef struct my_error_mgr *my_error_ptr;
////////////////////////////////////////////////////////////////////////////////
void JPEGerrorExit(j_common_ptr cinfo)
{
    /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
    if (cinfo)
    {
        my_error_ptr myerr = (my_error_ptr)cinfo->err;
        if (myerr)
        {
            /* Always display the message. */
            /* We could postpone this until after returning, if we chose. */
            (*cinfo->err->output_message) (cinfo);

            char jpegLastErrorMsg[JMSG_LENGTH_MAX];
            /* Create the message */
            (*cinfo->err->format_message) (cinfo, jpegLastErrorMsg);
            log().log() << "jpeg error: " << jpegLastErrorMsg << "\n";

            (*cinfo->err->output_message) (cinfo);

            /* Return control to the setjmp point */
            //longjmp(myerr->setjmp_buffer, 1);
            jpeg_abort(cinfo);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecJPEG::load(ImageRGBAPtr image)
{
    class JPEGreader
    {
    public:
        JPEGreader()
            : fp(nullptr)
        {
            cinfo.err = jpeg_std_error(&jerr.pub);
            jerr.pub.error_exit = JPEGerrorExit;
        }
        ~JPEGreader()
        {
            jpeg_finish_decompress(&cinfo);
            jpeg_destroy_decompress(&cinfo);
            fclose(fp);
        }

        struct jpeg_decompress_struct cinfo;
        struct my_error_mgr jerr;
        FILE *fp;
    };

    const char* file_name = image->getFileName().c_str();
    if (!file_name || image->getFileName().length() < 5) // min 5 chars to have something like x.png
    {
        log().log() << "image resource is not a file\n";
        return false;
    }

    /* Step 1: allocate and initialize JPEG decompression object */
    JPEGreader jpegReader;

    jpegReader.fp = fopen(file_name, "rb");
    if (!jpegReader.fp)
    {
        log().log() << file_name << "cannot be opened for reading\n";
        return false;
    }

    /* Establish the setjmp return context for my_error_exit to use. */
    if (setjmp(jpegReader.jerr.setjmp_buffer))
    {
        log().log() << file_name << ": Error jpeg init\n";
        return false;
    }

    /* Now we can initialize the JPEG decompression object. */
    jpeg_create_decompress(&jpegReader.cinfo);

    /* Step 2: specify data source (eg, a file) */
    jpeg_stdio_src(&jpegReader.cinfo, jpegReader.fp);

    /* Step 3: read file parameters with jpeg_read_header() */
    int res = jpeg_read_header(&jpegReader.cinfo, TRUE);
    if (res != JPEG_HEADER_OK)
    {
        log().log() << file_name << ": not a jpeg file\n";
        return false;
    }

    /* Step 5: Start decompressor */
    bool status = jpeg_start_decompress(&jpegReader.cinfo);
    if (status == false)
    {
        log().log() << file_name << ": jpeg decompression failed\n";
        return false;
    }

    if (jpegReader.cinfo.output_components != 3)
    {
        log().log() << file_name << ": " << jpegReader.cinfo.output_components << " not supported\n";
        return false;
    }

    /* JSAMPLEs per row in output buffer */
    int row_stride = jpegReader.cinfo.output_width * jpegReader.cinfo.output_components;
    std::vector<JSAMPLE> buf(row_stride);
    JSAMPROW rowbuffer = &buf.front();
    JSAMPARRAY buffer = &rowbuffer;
    image->resize(jpegReader.cinfo.output_width, jpegReader.cinfo.output_height);

    /* Step 6: Process scanlines */
    uint32_t y = 0;
    while (jpegReader.cinfo.output_scanline < jpegReader.cinfo.output_height)
    {
        JDIMENSION dim = jpeg_read_scanlines(&jpegReader.cinfo, buffer, 1);
        if (dim > 0)
        {
            for (uint32_t x = 0; x < jpegReader.cinfo.output_width; ++x)
            {
                (*image)(x, y) = Vec4ui8(rowbuffer[x*3 + 0], rowbuffer[x*3 + 1], rowbuffer[x*3 + 2], 255);
            }
        }
        ++y;
    }

    /* At this point you may want to check to see whether any corrupt-data
     * warnings occurred (test whether jerr.pub.num_warnings is nonzero).
     */
    if (jpegReader.jerr.pub.num_warnings != 0)
    {
        log().log() << file_name << ": jpeg warnings: " << jpegReader.jerr.pub.num_warnings << "\n";
    }

    /* Step 7: Finish decompression */
    /* Step 8: Release JPEG decompression object */

    return true;
}
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecJPEG::save(ImageRGBAPtr image, const std::string& filePath)
{
    return save(image.get(), filePath);
}
////////////////////////////////////////////////////////////////////////////////
bool PluginImageCodecJPEG::save(ImageRGBA* image, const std::string& filePath)
{
    class JPEGwriter
    {
    public:
        JPEGwriter()
            : fp(nullptr)
        {
            cinfo.err = jpeg_std_error(&jerr.pub);
            jerr.pub.error_exit = JPEGerrorExit;
        }
        ~JPEGwriter()
        {
            jpeg_finish_compress(&cinfo);
            fclose(fp);
            jpeg_destroy_compress(&cinfo);
        }

        struct jpeg_compress_struct cinfo;
        struct my_error_mgr jerr;
        FILE *fp;
    };

    const char* file_name = filePath.c_str();
    if (!file_name || filePath.length() < 5) // min 5 chars to have something like x.png
    {
        log().log() << "image resource is not a file\n";
        return false;
    }

    JPEGwriter jpegWriter;

    /* Step 1: allocate and initialize JPEG compression object */
    jpeg_create_compress(&jpegWriter.cinfo);

    /* Step 2: specify data destination (eg, a file) */
    /* Note: steps 2 and 3 can be done in either order. */
    jpegWriter.fp = fopen(file_name, "wb");
    if (!jpegWriter.fp)
    {
        log().log() << file_name << "cannot be opened for writing\n";
        return false;
    }
    jpeg_stdio_dest(&jpegWriter.cinfo, jpegWriter.fp);

    /* Step 3: set parameters for compression */
    Vec2ui r = image->resolution();
    jpegWriter.cinfo.image_width = r.x;              /* image width and height, in pixels */
    jpegWriter.cinfo.image_height = r.y;
    jpegWriter.cinfo.input_components = 3;           /* # of color components per pixel */
    jpegWriter.cinfo.in_color_space = JCS_RGB;       /* colorspace of input image */
    /* Now use the library's routine to set default compression parameters.
     * (You must set at least cinfo.in_color_space before calling this,
     * since the defaults depend on the source color space.)
     */
    jpeg_set_defaults(&jpegWriter.cinfo);
    /* Now you can set any non-default parameters you wish to.
     * Here we just illustrate the use of quality (quantization table) scaling:
     */
    jpeg_set_quality(&jpegWriter.cinfo, 85, TRUE /* limit to baseline-JPEG values */);

    /* Step 4: Start compressor */
    jpeg_start_compress(&jpegWriter.cinfo, TRUE);

    /* Step 5: Process scanlines */

    /* Here we use the library's state variable cinfo.next_scanline as the
     * loop counter, so that we don't have to keep track ourselves.
     * To keep things simple, we pass one scanline per call; you can pass
     * more if you wish, though.
     */
    int row_stride = r.x * 3; /* JSAMPLEs per row in image_buffer */
    std::vector<JSAMPLE> buf(row_stride);
    JSAMPROW rowbuffer = &buf.front();
    JSAMPARRAY buffer = &rowbuffer;
    uint32_t y = 0;
    while (jpegWriter.cinfo.next_scanline < jpegWriter.cinfo.image_height)
    {
        for (uint32_t x = 0; x < jpegWriter.cinfo.image_width; ++x)
        {
            Vec4ui8 v = (*image)(x, y);
            rowbuffer[x*3 + 0] = v.x;
            rowbuffer[x*3 + 1] = v.y;
            rowbuffer[x*3 + 2] = v.z;
        }
        jpeg_write_scanlines(&jpegWriter.cinfo, buffer, 1);
        ++y;
    }

    /* Step 6: Finish compression */
    /* Step 7: release JPEG compression object */

    return true;
}
////////////////////////////////////////////////////////////////////////////////
